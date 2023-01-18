'''P-R曲线:
    根据学习器的预测结果按正例可能性大小排序,并逐个把样本作为正例阈值进行预测得到的查准率-查全率曲线
    曲线体现了学习器查准率和查全率的制衡关系
'''
import numpy as np
from matplotlib import pyplot as plt

def prediction(score,threshold):    #预测结果:1为正例,0为反例
    pred=[1 if(x>threshold)else 0 for x in score]
    return pred
# def correctness(label,pred):        #预测结果是否正确,返回Bool列表
#     correct=[label[i]==pred[i] for i in range(len(label))]
#     return correct

def TP(label,pred):     #真正例:即真实值为正例,预测值为正例
    cnt=0
    for i in range(len(label)):
        if(label[i]==1 and pred[i]==1): cnt+=1
    return cnt
def FN(label,pred):     #假反例:即真实值为正例,预测值为反例
    cnt=0
    for i in range(len(label)):
        if(label[i]==1 and pred[i]==0): cnt+=1
    return cnt
def FP(label,pred):     #假正例:即真实值为反例,预测值为正例
    cnt=0
    for i in range(len(label)):
        if(label[i]==0 and pred[i]==1): cnt+=1
    return cnt
def TN(label,pred):     #真反例:即真实值为反例,预测值为反例
    cnt=0
    for i in range(len(label)):
        if(label[i]==0 and pred[i]==0): cnt+=1
    return cnt

def P(label,pred):      #查准率(精确率precision)
    tp=TP(label,pred)
    fp=FP(label,pred)
    return tp/(tp+fp)
def R(label,pred):      #查全率(召回率recall)
    tp=TP(label,pred)
    fn=FN(label,pred)
    return tp/(tp+fn)
def ACC(label,pred):    #准确率accuracy
    tp=TP(label,pred)
    tn=YN(label,pred)
    fp=FP(label,pred)
    fn=FN(label,pred)
    return (tp+tn)/(tp+fn+fp+tn)
def F1(label,pred):     #综合考虑查准率和查全率的调和均值
    p=P(label,pred)
    r=R(label,pred)
    return 2/(1/p+1/r)
def Fb(label,pred,b):   #一般形式的Fb
    '''args
        b=1:标准F1
        b>1:偏重查全率
        b<1:偏重查准率
    '''
    p=P(label,pred)
    r=R(label,pred)
    return (1+b*b)*p*r/(b*b*p+r)

label=[1,1,1,0,1,0,0,0,0,0] #标签值
score=[0.98,0.95,0.91,0.87,0.85,0.7,0.55,0.22,0.13,0.07]    #预测指标
n=len(label)
lstP=[]
lstR=[]

for i in range(1,n+1):
    if(i==n):   threshold=0     #高于阈值的预测为正例,否则为反例
    else:       threshold=score[i]
    pred=prediction(score,threshold)
    lstP.append(P(label,pred))
    lstR.append(R(label,pred))

plt.figure(figsize=(8,6))
plt.title('R-R Curve')
plt.plot(lstR,lstP)
plt.xlabel("Recall")
plt.ylabel("Precision")
plt.show()