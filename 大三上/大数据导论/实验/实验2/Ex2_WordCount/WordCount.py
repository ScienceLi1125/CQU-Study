#!/usr/bin/env python3
#coding: UTF-8
"""
@author: huangwanghui
@time: 2020/1/25 22:12
"""
from pyspark import SparkConf, SparkContext
from visualize import visualize
import jieba

SRCPATH = '/home/hadoop/Experiment/Ex2_WordCount/src/'

# conf = SparkConf().setAppName("ex2").setMaster("spark://master:7077")
conf = SparkConf().setAppName("ex2").setMaster("local")
sc = SparkContext(conf=conf)

def getStopWords(stopWords_filePath):
    stopwords = [line.strip() for line in open(stopWords_filePath, 'r', encoding='utf-8').readlines()]
    return stopwords

def jiebaCut(answers_filePath):
    """
    结巴分词
    :param answers_filePath: answers.txt路径
    :return:
    """
    # 读取answers.txt
    answersRdd = sc.textFile(answers_filePath) # answersRdd每一个元素对应answers.txt每一行

    # 利用SpardRDD reduce()函数,合并所有回答
    # 【现在你应该完成下面函数编码】

    str = answersRdd.reduce(lambda x, y: x + y )

    # jieba分词
    words_list = jieba.lcut(str)
    return words_list

def wordcount(isvisualize=False):
    """
    对所有答案进行
    :param visualize: 是否进行可视化
    :return: 将序排序结果RDD
    """
    # 读取停用词表
    stopwords = getStopWords(SRCPATH + 'stop_words.txt')

    # 结巴分词
    words_list = jiebaCut("file://" + SRCPATH + "answers.txt")

    # 词频统计
    wordsRdd = sc.parallelize(words_list)

    # wordcount：去除停用词等同时对最后结果按词频进行排序
    # 完成SparkRDD操作进行词频统计
    # 提示：你应该依次使用
    #      1.filter函数分别进行停用词过滤、去除长度<=1的词汇
    #      2.map进行映射，如['a','b','a'] --> [('a',1),('b',1),('a',1)]
    #      3.reduceByKey相同key进行合并 [('a',2),('b',1)]
    #      4.sortBy进行排序，注意应该是降序排序
    #【现在你应该完成下面函数编码】
    resRdd = wordsRdd.filter(lambda word: word not in stopwords) \
                     .filter(lambda word: len(word)>1 )\
                     .map(lambda word:(word,1)) \
                     .reduceByKey(lambda a, b: a + b) \
                     .sortBy(ascending=False, numPartitions=None, keyfunc=lambda x: x[1]) \

    

    # 可视化展示
    if isvisualize:
        v = visualize()
        # 饼状图可视化
        pieDic = v.rdd2dic(resRdd,10)
        v.drawPie(pieDic)
        # 词云可视化
        wwDic = v.rdd2dic(resRdd,50)
        v.drawWorcCloud(wwDic)
        # 柱状图可视化
        barDic = v.rdd2dic(resRdd,12)
        v.drawBar(barDic)
        # 折线图可视化
        lineDic = v.rdd2dic(resRdd,15)
        v.drawLine(lineDic)
    return  resRdd

if __name__ == '__main__':

    # 进行词频统计并可视化
    resRdd = wordcount(isvisualize=True)
    print(resRdd.take(10))  # 查看前10个

