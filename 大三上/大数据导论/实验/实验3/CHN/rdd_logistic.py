# author: Marx
# time:2020-11-15
# pyspark 2.4.7

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

conf = SparkConf().setAppName("ChineseHandwrittingNumber").setMaster("spark://master:7077")
sc = SparkContext(conf=conf)
sc.setLogLevel("WARN")   # 设置日志级别
spark = SparkSession(sc)

print("load spark successful")

TRAINPATH = "/chn/train.csv"
TESTPATH = "/chn/test.csv"

def GetParts(line):
    """将一行不定长的数字数据转换成LabeledPoint，便于pyspark.mllib中的各种库调用
    其中最后一个数字是label，前面的都是feature
    例如 1,2,3,4,5,6,7,8 转换成[8, Vector[1,2,3,4,5,6,7]]
        9,10,11,12 转换成 [12, Vector[9,10,11]]
    """
    parts = line.split(',')
    return LabeledPoint(float(parts[-1]),Vectors.dense(parts[:-1]))

rdd_train = sc.textFile(TRAINPATH)  #训练集
rdd_test = sc.textFile(TESTPATH)    #测试集

rdd_train = rdd_train.map(lambda line:GetParts(line))
rdd_test = rdd_test.map(lambda line:GetParts(line))

print("load hdfs data successful")
# ~ rdd_train.cache()
# ~ rdd_test.cache()

## 训练逻辑回归多分类器
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
