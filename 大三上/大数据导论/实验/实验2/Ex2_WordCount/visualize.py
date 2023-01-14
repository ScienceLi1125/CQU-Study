#!/usr/bin/env python3
#coding: UTF-8
"""
@author: huangwanghui
@time: 2020/1/25 22:14
"""

import os
from wordcloud import WordCloud
from pyecharts.render import make_snapshot
from snapshot_selenium import snapshot
from pyecharts import options as opts
from pyecharts.charts import Pie
from pyecharts.charts import Bar
from pyecharts.charts import Line

# 解决错误：Running as root without --no-sandbox is not supported.
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
chrome_options = Options()
chrome_options.add_argument('--headless')
chrome_options.add_argument('--no-sandbox')
chrome_options.add_argument('--disable-dev-shm-usage')

SAVAPATH = '/home/hadoop/Experiment/Ex2_WordCount/results/'

class visualize:

    def rdd2dic(self,resRdd,topK):
        """
        将RDD转换为Dic，并截取指定长度topK
        :param resRdd: 词频统计降序排序结果RDD
        :param topK: 截取的指定长度
        :return:
        """
        # 将RDD转换为Dic
        resDic = resRdd.collectAsMap()
        # 截取字典前K个
        K = 0
        wordDicK = {}
        for key, value in resDic.items():
            if K>=topK:
                break
            wordDicK[key]=value
            K+=1

        return wordDicK

    def drawWorcCloud(self, wordDic):
        """
        根据词频字典，进行词云可视化
        :param wordDic: 词频统计字典
        :return:
        """
        # 生成词云
        wc = WordCloud(font_path='/usr/share/fonts/wqy-microhei/wqy-microhei.ttc',
                       background_color='white',
                       max_words=2000,
                       width=1920, height=1080,
                       margin=5)
        wc.generate_from_frequencies(wordDic)
        # 保存结果
        if not os.path.exists(SAVAPATH):
            os.makedirs(SAVAPATH)
        wc.to_file(os.path.join(SAVAPATH, '词云可视化.png'))

    def drawPie(self, wordDic):
        """
        饼图可视化
        :param wordDic: 词频统计字典
        :return:
        """
        key_list = wordDic.keys()      # wordDic所有key组成list
        value_list= wordDic.values()   # wordDic所有value组成list
        def pie_position() -> Pie:
            c = (
                Pie()
                    .add
                    (
                    "",
                    [list(z) for z in zip(key_list, value_list)], # dic -> list
                    center=["35%", "50%"],
                    )
                    .set_global_opts
                    (
                    title_opts=opts.TitleOpts(title='饼图可视化'), # 设置标题
                    legend_opts=opts.LegendOpts(pos_left="15%"),
                    )
                    .set_series_opts(label_opts=opts.LabelOpts(formatter="{b}: {c}"))
            )
            return c
        # 保存结果
        if not os.path.exists(SAVAPATH):
            os.makedirs(SAVAPATH)
        make_snapshot(snapshot, pie_position().render(), SAVAPATH + '饼图可视化.png')

    def drawBar(self, wordDic):
        """
        柱状图可视化
        :param wordDic: 词频统计字典
        :return:
        """
        key_list = wordDic.keys()      # wordDic所有key组成list
        value_list = wordDic.values()   # wordDic所有value组成list
        def bar_position() -> Bar:
            c = (
                Bar()
                    .add_xaxis(list(key_list))
                    .add_yaxis("频数",list(value_list))
                    .set_global_opts
                    (
                    title_opts=opts.TitleOpts(title='柱状图可视化'), # 设置标题
                    # legend_opts=opts.LegendOpts(pos_right="5%"),
                    )
                    .set_series_opts(itemstyle_opts=opts.ItemStyleOpts(color='#99ccff'))
            )
            return c
        # 保存结果
        if not os.path.exists(SAVAPATH):
            os.makedirs(SAVAPATH)
        make_snapshot(snapshot, bar_position().render(), SAVAPATH + '柱状图可视化.png')

    def drawLine(self, wordDic):
        """
        折线图可视化
        :param wordDic: 词频统计字典
        :return:
        """
        key_list = wordDic.keys()      # wordDic所有key组成list
        value_list = wordDic.values()   # wordDic所有value组成list
        def line_position() -> Line:
            c = (
                Line()
                    .add_xaxis(list(key_list))
                    .add_yaxis("频数",list(value_list))
                    .set_global_opts
                    (
                    title_opts=opts.TitleOpts(title='折线图可视化'), # 设置标题
                    # legend_opts=opts.LegendOpts(pos_right="5%"),
                    )
                    .set_series_opts(label_opts=opts.LabelOpts(color='#99ccff'))
            )
            return c
        # 保存结果
        if not os.path.exists(SAVAPATH):
            os.makedirs(SAVAPATH)
        make_snapshot(snapshot, line_position().render(), SAVAPATH + '折线图可视化.png')