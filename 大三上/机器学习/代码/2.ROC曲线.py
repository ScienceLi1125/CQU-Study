'''ROC曲线:
    根据学习器的预测结果按正例可能性大小排序,并逐个把样本作为正例阈值进行预测得到的FPR-TPR曲线
    曲线反映了敏感性和特异性的相互关系
    ROC曲线下方面积被定义为AUC值,可以用来评价分类器效果好坏
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

def TPR(label,pred):    #真正类率(灵敏度):正样本中标记为正的样本率
    tp=TP(label,pred)
    fn=FN(label,pred)
    return tp/(tp+fn)
def FNR(label,pred):    #假负类率=1-真正类率
    fn=FN(label,pred)
    tp=TP(label,pred)
    return fn/(tp+fn)
def FPR(label,pred):    #假正类率=1-真负类率:负样本中标记为正的样本率
    fp=FP(label,pred)
    tn=TN(label,pred)
    return fp/(fp+tn)
def TNR(label,pred):    #真负类率(特异性)
    fp=FP(label,pred)
    tn=YN(label,pred)
    return tn/(fp+tn)

def AUC(FPR,TPR):
    auc=0
    for i in range(len(FPR)-1):
        auc+=(FPR[i+1]-FPR[i])*(TPR[i]+TPR[i+1])
    return auc/2

label=[1,1,1,0,1,0,0,0,0,0] #标签值
score=[0.98,0.95,0.91,0.87,0.85,0.7,0.55,0.22,0.13,0.07]    #预测指标
n=len(label)
lstFPR=[]
lstTPR=[]

for i in range(1,n+1):
    if(i==n):   threshold=0     #高于阈值的预测为正例,否则为反例
    else:       threshold=score[i]
    pred=prediction(score,threshold)
    lstFPR.append(FPR(label,pred))
    lstTPR.append(TPR(label,pred))

print('AUC:'+str(AUC(lstFPR,lstTPR)))

plt.figure(figsize=(8,6))
plt.title('R-R Curve')
plt.plot(lstFPR,lstTPR)
plt.xlabel("FPR")
plt.ylabel("TPR")
plt.show()