'''基于HMM的拼音转汉字程序
    预处理训练语料
    训练HMM模型
    维特比算法实现从任意拼音到汉字的自动转换
    测试集评价程序的转换准确率
'''
import json
from DataProcessing import Construct_Dict
from Viterbi import translate

def Correct(s1,s2):                     #比较正确/错误字符数以及字符串是否相同
    n=len(s1)
    right=0
    wrong=0
    for i in range(n):
        if(s1[i]==s2[i]):
            right+=1
        else:
            wrong+=1
    return right,wrong,wrong==0

with open(r"NLP\实验1\train_data\A.json") as f:
    A=json.load(f)
with open(r"NLP\实验1\train_data\B.json") as f:
    B=json.load(f)
with open(r"NLP\实验1\train_data\Pi.json") as f:
    Pi=json.load(f)

hanzi_list,pinyin_list,hanzi_index,pinyin_index,hanzi2pinyin_dic,pinyin2hanzi_dic=Construct_Dict()
# print(translate(["shen","du","xue","xi","ji","shu"],hanzi_list,pinyin_list,hanzi_index,pinyin_index,hanzi2pinyin_dic,pinyin2hanzi_dic,A,B,Pi))

with open(r'NLP\实验1\data\测试集.txt','r',encoding='UTF-8-sig') as f:
    cnt=0
    right=0
    wrong=0
    Accurate=0
    tmp=""
    while True:
        line=f.readline()
        if not line:
            break
        line=line.replace('\n','')
        if(cnt%2==0):
            line=line.casefold()            #全部转成小写
            print(line)
            line=line.split(' ')
            tmp=translate(line,hanzi_list,pinyin_list,hanzi_index,pinyin_index,hanzi2pinyin_dic,pinyin2hanzi_dic,A,B,Pi)
            # print(tmp)
        else:
            r,w,b=Correct(tmp,line)
            print("标签值:",line)
            print("预测值:",tmp)
            print("单句识别准确率:%f"%(r/(r+w)))
            right+=r
            wrong+=w
            Accurate+=b
        cnt+=1
print("测试集汉字预测准确率:",right/(right+wrong))
print("测试集整句预测准确率:",Accurate*2/cnt)