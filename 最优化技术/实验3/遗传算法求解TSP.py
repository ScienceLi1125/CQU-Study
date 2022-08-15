# -*- coding:utf-8 -*-
'''
    用基因表示个体特征,即城市编号;染色体表示一组解,即城市路线编号;一定数量的染色体组成种群,并
通过适应度函数进行评估其存活率。
    算法随机生成初始种群,通过复制、交叉、逆转、变异并进行自然选择,直至符合优解条件满足
'''
import numpy as np
import matplotlib.pyplot as plt
import matplotlib
import math
from random import random,randint,shuffle
import csv
matplotlib.rcParams['font.family']='SimHei'     #设置中文字体

def read_data():        #载入数据
    name=[]             #城市名
    location=[]         #城市坐标
    f=open('OptimizationTechnology\实验3\city.csv')
    reader=csv.reader(f)
    rows=[row for row in reader]
    for i in range(1,len(rows)):
        city=rows[i][0]
        latitude=rows[i][1]
        longitude=rows[i][2]
        name.append(city)
        location.append([float(latitude),float(longitude)])
    location=np.array(location)
    return name,location

class TSP:                          #定义旅行商类
    def __init__(self,org):
        self.origin=org             #起始点
        self.epochTime=20           #进化次数
        self.populationCount=1000   #种群数
        self.retainRate=0.3         #保持率
        self.mutationRate=0.1       #变异率
        self.reverseCount=10        #逆转次数
        self.cityNames,self.location=read_data()
        self.cityCount=len(self.cityNames)
        self.matrix=self.get_distance_matrix() #建立邻接矩阵
        self.cityIndex=[i for i in range(self.cityCount)]#城市索引
        self.cityIndex.remove(org)

    def get_distance_matrix(self):          #建立图的邻接矩阵
        num=self.cityCount
        loc=self.location
        matr=np.zeros([num,num])
        for i in range(num):
            for j in range(i,num):
                if i==j:
                    matr[i][j]=0
                else:
                    x2=(loc[i][0]-loc[j][0])**2
                    y2=(loc[i][1]-loc[j][1])**2
                    matr[j][i]=matr[i][j]=math.sqrt(x2+y2)
        return matr
 
    def get_total_distance(self,path):      #求路径path长度
        matr=self.matrix
        org=self.origin
        dis=0                               #记录路径长度
        dis+=matr[org][path[0]]
        for i in range(len(path)):
            if i==len(path)-1:
                dis+=matr[org][path[i]]
            else:
                dis+=matr[path[i]][path[i+1]]
        return dis
 
    def Reverse(self,path):                 #逆转操作,改善局部搜索能力
        rcnt=self.reverseCount
        dis=self.get_total_distance(path)
        for i in range(rcnt):               #逆转次数
            u=randint(0,len(path)-1)
            v=randint(0,len(path)-1)
            if u!=v:
                new_path=path.copy()        #拷贝path对其副本进行操作
                t=new_path[u]               #swap(path,u,v)
                new_path[u]=new_path[v]
                new_path[v]=t
                new_distance=self.get_total_distance(new_path)
                if new_distance<dis:
                    dis=new_distance
                    path=new_path.copy()
            else:
                continue
        return path
    
    def selection(self,population):         #对新种群的自然选择
        retain_rate=self.retainRate         #保持率
        #对总距离从小到大进行排序
        graded=[[self.get_total_distance(path),path] for path in population]#[距离,路径]
        graded=[path[1] for path in sorted(graded)] #路径
        retain_length=int(len(graded)*retain_rate)
        new_pop=graded[:retain_length]      #选出适应性强的len(graded)*retain_rate条染色体
        random_select_rate=0.2              #弱者存活率
        for chromosome in graded[retain_length:]:
            if random() < random_select_rate:
                new_pop.append(chromosome)
        return new_pop
    
    def crossover(self,parents):            #交叉
        # 生成子代的个数,保证种群数目稳定
        target_count=self.populationCount-len(parents)
        # 孩子列表
        cs=[]
        while len(cs)<target_count:
            male_index=randint(0,len(parents)-1)
            female_index=randint(0,len(parents)-1)
            if male_index!=female_index:    #保证不和自己交配
                male=parents[male_index]
                female=parents[female_index]
                left=randint(0,len(male)-2) #随机生成两点交叉点位
                right=randint(left+1,len(male)-1)

                gene1=male[left:right]      #待交叉片段
                gene2=female[left:right]
                miss1=[]
                miss2=[]
                for item in gene1:
                    if item not in gene2:
                        miss1.append(item)          #交换后male缺失的部分(female多余的部分)
                for item in gene2:
                    if item not in gene1:
                        miss2.append(item)          #交换后female缺失的部分(male多余的部分)
                child1_tmp=male[:left]+male[right:] #不包含交换部分的基因
                child2_tmp=female[:left]+female[right:]
                for i in range(len(miss1)):
                    for j in range(len(child1_tmp)):
                        if child1_tmp[j]==miss2[i]:
                            child1_tmp[j]=miss1[i]
                for i in range(len(miss2)):
                    for j in range(len(child2_tmp)):
                        if child2_tmp[j]==miss1[i]:
                            child2_tmp[j]=miss2[i]
                child1=child1_tmp[:left]
                child1_r=child1_tmp[left:]
                child1.extend(gene2)
                child1.extend(child1_r)
                child2=child2_tmp[:left]
                child2_r=child2_tmp[left:]
                child2.extend(gene1)
                child2.extend(child2_r)
                cs.append(child1) 
                cs.append(child2)
        return cs
    
    def mutation(self,cs):                  #变异
        mutation_rate=self.mutationRate
        new_cs=[]                           #生成变异后结果
        for i in range(len(cs)):
            child=cs[i]
            if random()<mutation_rate:
                u=randint(1,len(child)-4)
                v=randint(u+1,len(child)-3)
                w=randint(v+1,len(child)-2)
                child=child[0:u]+child[v:w]+child[u:v]+child[w:]
            new_cs.append(child)
        return new_cs
    
    def get_best_result(self,population):   #得到最佳结果
        graded=[[self.get_total_distance(path), path] for path in population]
        graded=sorted(graded)
        return graded[0][0],graded[0][1]
    
    def evolution(self):                    #进化
        org=self.origin
        population=[]
        for i in range(self.populationCount):
            x=self.cityIndex.copy()         #随机生成个体
            shuffle(x)
            x=self.Reverse(x)               #优化个体
            population.append(x)
        #遗传优化
        ans=[]
        i=0
        distance,result_path=self.get_best_result(population)
        while i<self.epochTime:
            #选择繁殖个体群
            parents=self.selection(population)
            #交叉繁殖
            cs=self.crossover(parents)
            #变异操作
            cs=self.mutation(cs)
            #更新种群
            population=parents+cs
            distance,result_path=self.get_best_result(population)
            ans.append(distance)
            i+=1
        result_path=[org]+result_path+[org]
        #输出
        print(distance)
        print(result_path)
        for i in range(len(result_path)):
            if i!=0:
                print("——>",end='')
            print(self.cityNames[result_path[i]],end='')
        #绘图
        xs=list()
        ys=list()
        nam=self.cityNames
        loc=self.location
        for j in result_path:
            # 画注解
            plt.annotate(nam[j],[loc[j, 0],loc[j, 1]])
            xs.append(loc[j,0])
            ys.append(loc[j,1])
        #绘图
        plt.xlabel('X')
        plt.ylabel('Y')
        plt.plot(xs,ys,'-o')
        plt.show()
        plt.xlabel('训练次数')
        plt.ylabel('距离')
        plt.title('Evolution of Fitness function')
        plt.plot(list(range(len(ans))),ans)
        plt.show()


if __name__ == '__main__':
    t1=TSP(8)
    t1.evolution()