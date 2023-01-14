'''Viterbi搜索算法
    delta[t][i]表示时间t时状态为Si且观测序列为O1O2...Ot的最大概率
    fai[t][j]表示t时的状态Si的前驱节点
初始状态: 
    delta[1][i]=Pi[i]*B[i][O1]
    fai[1][j]=-1
状态转移:
    delta[t][j]=max{delta[t-1][i]*A[i][j]}*B[j][Ot]
    fai[t][j]=argmax(i){delta[t-1][i]*A[i][j]}*B[j][Ot]
最终结果:
    QT=argmax{delta[T][i]}
回溯:
    q[t]=fai[t+1][q[t+1]]
'''
import json
import time
from DataProcessing import Construct_Dict

# with open(r"NLP\实验1\train_data\A.json") as f:
#     A=json.load(f)
# with open(r"NLP\实验1\train_data\B.json") as f:
#     B=json.load(f)
# with open(r"NLP\实验1\train_data\Pi.json") as f:
#     Pi=json.load(f)

# hanzi_list,pinyin_list,hanzi_index,pinyin_index,hanzi2pinyin_dic,pinyin2hanzi_dic=Construct_Dict()

def translate(pinyin,hanzi_list,pinyin_list,hanzi_index,pinyin_index,hanzi2pinyin_dic,pinyin2hanzi_dic,A,B,Pi):
    '''将拼音翻译成汉字
        args: pinyin(格式为:["shen","du","xue","xi","ji","shu"])
            hanzi_list,pinyin_list,hanzi_index,pinyin_index,hanzi2pinyin_dic,pinyin2hanzi_dic
        return: hanzi
    '''
    N=len(A)
    M=len(B[0])
    len_p=len(pinyin)
    delta=[[0]*N for i in range(len_p)]
    fai=[[0]*N for i in range(len_p)]
    for i in range(N):                  #初始化
        delta[0][i]=Pi[i]*B[i][pinyin_index[pinyin[0]]]
        fai[0][i]=-1
    
    # for t in range(1,len_p):          #动态规划(复杂度太高)
    #     for j in range(N):
    #         max_tmp=0
    #         index=-1
    #         for i in range(N):
    #             tmp=delta[t-1][i]*A[i][j]
    #             if tmp>max_tmp:
    #                 max_tmp=tmp
    #                 index=i
    #         delta[t][j]=max_tmp*B[j][pinyin_index[pinyin[t]]]
    #         fai[t][j]=index
    words_pre=pinyin2hanzi_dic[pinyin[0]]       #前一个拼音可能的隐状态
    for t in range(1,len_p):            #只对可能的拼音->汉字进行查找
        words_cur=pinyin2hanzi_dic[pinyin[t]]   #当前拼音可能的隐状态
        for word_cur in words_cur:
            j=hanzi_index[word_cur]     #汉字对应的序号
            max_tmp=0
            index=-1
            for word_pre in words_pre:
                i=hanzi_index[word_pre]
                tmp=delta[t-1][i]*A[i][j]
                if tmp>=max_tmp:
                    max_tmp=tmp
                    index=i
            delta[t][j]=max_tmp*B[j][pinyin_index[pinyin[t]]]
            fai[t][j]=index
            # print("p(%s->%s)=%f"%(hanzi_list[index],word_cur,delta[t][j]),end=" ")
        words_pre=words_cur
    
    max_p=0                             #最终结果
    index=-1
    words=pinyin2hanzi_dic[pinyin[len_p-1]]
    for x in words:                     #只在可能的结果中搜索
        i=hanzi_index[x]
        tmp=delta[len_p-1][i]
        if tmp>=max_p:
            max_p=tmp
            index=i
    
    Q=[0]*len_p                         #回溯汉字
    Q[len_p-1]=index
    t=len_p-2
    while(t>=0):
        Q[t]=fai[t+1][Q[t+1]]
        t-=1
    hanzi=""
    for n in Q:
        hanzi+=hanzi_list[n]
    # print(hanzi)
    return hanzi

# time_start = time.time()
# print(translate(["shen","du","xue","xi","ji","shu"],hanzi_list,pinyin_list,hanzi_index,pinyin_index,hanzi2pinyin_dic,pinyin2hanzi_dic,A,B,Pi))
# time_end = time.time()
# time_c= time_end - time_start
# print('Execution time:', time_c, 's')