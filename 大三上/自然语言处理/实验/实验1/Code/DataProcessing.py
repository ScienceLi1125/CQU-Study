'''预处理训练语料并训练HMM模型
数据预处理:
    读取pinyin2hanzi.txt文件,得到所有汉字、拼音各自的列表,并记录其编号(显隐状态都由编号指代)
    为了处理一字多音和一音多字,记录了同一个字对应的不同读音和同一个读音对应的不同字
训练HMM模型:
    读取toutiao_cat_data.txt文件,训练得到状态转移概率矩阵A和初始状态矩阵π
    用预处理得到的汉字——>多个读音取均值近似Pi
'''
import re
import time
import json

def Construct_Dict():
    '''读取pinyin2hanzi.txt文件,构造隐显状态集合,即汉字和拼音的列表并记录其下标
        return: 
            hanzi_list:隐状态的列表
            pinyin_list:显状态的列表
            hanzi_index:隐状态对应的hanzi_list中坐标的字典
            pinyin_index:显状态对应的pinyin_list中坐标的字典
            hanzi2pinyin_dic:隐状态可能对应的显状态集合的字典
            pinyin_dic:显状态可能对应的隐状态集合的字典
    '''
    hanzi_list=[]
    pinyin_list=[]
    hanzi_index={}
    pinyin_index={}
    hanzi2pinyin_dic={}
    pinyin2hanzi_dic={}
    i=0
    j=0
    with open(r'NLP\实验1\data\pinyin2hanzi.txt','r',encoding='UTF-8-sig') as f:
        while True:
            line=f.readline()
            if not line:                #读取结束
                break
            line=line.replace('\n','')  #去掉结尾换行符
            line=line.split(' ')        #分割为拼音和汉字
            pinyin_list.append(line[0])
            pinyin_index[line[0]]=i
            i+=1
            pinyin2hanzi_dic[line[0]]=set()
            for x in line[1]:
                pinyin2hanzi_dic[line[0]].add(x)
                if x not in hanzi_list: #x是第一次出现的汉字
                    hanzi_list.append(x)
                    hanzi_index[x]=j
                    j+=1
                    # hanzi2pinyin_dic[x]=set(line[0])  #字符串line[0]会被拆成多个字符
                    hanzi2pinyin_dic[x]=set()
                    hanzi2pinyin_dic[x].add(line[0])
                else:                   #x是多音字
                    hanzi2pinyin_dic[x].add(line[0])
    return hanzi_list,pinyin_list,hanzi_index,pinyin_index,hanzi2pinyin_dic,pinyin2hanzi_dic

def Train_miu(hanzi_list,pinyin_list,hanzi_index,pinyin_index,hanzi2pinyin_dic,pinyin2hanzi_dic):
    '''读取toutiao_cat_data.txt文件,构造状态转移概率矩阵A,发射概率矩阵B,初始状态概率矩阵Pi
        return: A,B,Pi
    '''
    N=len(hanzi_list)
    M=len(pinyin_list)
    A=[[0]*N for i in range(N)]
    B=[[0]*M for i in range(N)]
    Pi=[0]*N
    sentence=[]                         #语料库,每个元素为一句不含标点的话的汉字列表
    with open(r'NLP\实验1\data\toutiao_cat_data.txt','r',encoding='UTF-8-sig') as f:
        while True:
            line=f.readline()
            if not line:                #读取结束
                break
            line=line.replace('\n','')  #此处line是字符串
            line=line.split('_!_')      #此处line是列表(新闻ID,分类code,分类名称,新闻标题,关键词)
            line=line[3]                #此处line是字符串(只保留了标题)
            sentence.append(re.findall('[\u4e00-\u9fa5]',line))
    # print(sentence)

    for x in sentence:                  #训练A和Pi
        for i in range(len(x)):
            if i==0:                    #语料的第一个字
                if x[0] not in hanzi_list:  
                    continue            #未标注的汉字直接丢弃
                else:
                    Pi[hanzi_index[x[i]]]+=1
            else:                       #x[i-1]->x[i]
                if (x[i-1] not in hanzi_list)or(x[i] not in hanzi_list):
                    continue
                else:
                    A[hanzi_index[x[i-1]]][hanzi_index[x[i]]]+=1
            print(x[i],end=" ")

    for k,v in hanzi2pinyin_dic.items():#训练B
        len_v=len(v)                    #k是汉字,v是对应拼音的集合
        for p in v:
            B[hanzi_index[k]][pinyin_index[p]]=1/len_v

    for i in range(N):                  #对A归一化
        sum=0
        for j in range(N):
            sum+=A[i][j]
        if sum==0:
            continue                    #跳过全0的状态转移
        for j in range(N):
            A[i][j]/=sum

    sum=0
    for i in range(N):                  #对Pi归一化
        sum+=Pi[i]
    for i in range(N):
        Pi[i]/=sum
    return A,B,Pi

# time_start = time.time()
# hanzi_list,pinyin_list,hanzi_index,pinyin_index,hanzi2pinyin_dic,pinyin2hanzi_dic=Construct_Dict()
# A,B,Pi=Train_miu(hanzi_list,pinyin_list,hanzi_index,pinyin_index,hanzi2pinyin_dic,pinyin2hanzi_dic)
# time_end = time.time()
# time_c= time_end - time_start
# print('\nExecution time:', time_c, 's')

# with open(r"NLP\实验1\train_data\A.json","w") as f:
#     json.dump(A,f)
# with open(r"NLP\实验1\train_data\B.json","w") as f:
#     json.dump(B,f)
# with open(r"NLP\实验1\train_data\Pi.json","w") as f:
#     json.dump(Pi,f)
# print("Writing finished!")