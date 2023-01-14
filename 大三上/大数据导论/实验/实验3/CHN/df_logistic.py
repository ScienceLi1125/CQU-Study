# author: Marx
# time:2020-11-15
# pyspark 2.4.7
# read image from hadoop-hdfs, hdfs://master:9000/chn/
# make sure that /chn/0/ contains image that label is 0
#                /chn/1/ contains image that label is 1

"""
首先需要将中文数据集进行分类，将类别相同的放进同一个文件夹，类别依次为0,1,2......14
并上传到hdfs的/chn/下面

例如 /chn/0/ 下面全是数字零的图片，/chn/1/下面全是数字一的图片，/chn/14/下面是数字亿的图片

注意DataFrame的操作，不同pyspark版本的接口可能不同
"""

from pyspark import SparkConf, SparkContext
from pyspark.sql import SparkSession
from pyspark.ml.image import ImageSchema
from pyspark.mllib.regression import LabeledPoint
from pyspark.mllib.linalg import Vectors
from pyspark.mllib.classification import SVMWithSGD
from pyspark.mllib.classification import LogisticRegressionModel
from pyspark.mllib.classification import LogisticRegressionWithLBFGS
from pyspark.ml.classification import LogisticRegression
from pyspark.sql.functions import lit
import numpy as np
import time
from skimage.feature import hog

conf = SparkConf().setAppName("projwithsvm").setMaster("spark://master:7077")
sc = SparkContext(conf=conf)
sc.setLogLevel("WARN")   # 设置日志级别
spark = SparkSession(sc)

print("load spark successful")

DATAPATH = "/chn/"

def get_a_df(fpath):
    """将图片文件变成spark的DataFrame模型，该模型可以支持sql操作
    fpath:文件子路径和图片的label，将DATAPATH/fpath 下的图片读出来 并设置Label为fpath值"""
    dftemp = ImageSchema.readImages(DATAPATH+"/"+str(fpath)).withColumn("Label",lit(fpath))
    df_train, df_test = dftemp.randomSplit([.8, .2])
    return df_train, df_test

def load_df():
    """获取所有的图片集合，即依次调用get_a_df(x) for x in 0-14"""
    df_train,df_test = get_a_df(1)
    for i in range(2,16):
        df_temp1,df_temp2 = get_a_df(i)
        df_train = df_train.unionAll(df_temp1)
        df_test = df_test.unionAll(df_temp2)
    return df_train, df_test

def df2labeledrdd(df):
    """数据集处理操作，包括读图片，numpy.reshape，hog计算等等 并最终转换成rdd"""
    lrdd = df.rdd.map(lambda row: LabeledPoint(row[-1], \    # 读一行row
                    Vectors.dense( \ # 将row中的图片变成Vector
                    hog(np.array(row[0].data \ # numpy 转换图片为64*64,row[0].data就是图片的值
                    ).reshape(64,64),cells_per_block=(2, 2))))) # hog计算的参数
    return lrdd

df_train, df_test = load_df()
print("load hdfs data successful",df_train.count(), df_test.count())

## 将数据都转换成处理特征后的rdd
rdd_train = df2labeledrdd(df_train)
rdd_test = df2labeledrdd(df_test)

print("load hdfs data successful")

print("model train start at:", time.strftime('%Y-%m-%d %H:%M:%S'))
model = LogisticRegressionWithLBFGS().train(rdd_train, iterations=100, numClasses=15)
print("model train successful at:", time.strftime('%Y-%m-%d %H:%M:%S'))

## 保存模型
import os, tempfile
path = tempfile.mkdtemp()
model.save(sc, path)
print("Model saved at: ",path)

## 计算准确率
scoreAndLabels = rdd_test.map(lambda point:(model.predict(point.features),point.label))
accuracy = scoreAndLabels.filter(lambda l: l[0]==l[1]).count() / rdd_test.count()
print("accuracy: ",accuracy)
