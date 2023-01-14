'''基于字的Bigram语言模型
    功能要求:当用户输入某个字序列,程序可以自动推荐该序列的后一个字(依次列出概率最大的5个可能字选项),
根据提示用户选择某个字后,程序可以继续推荐下一个字的列表。例如:输入"长江大"，程序猜测下一个可能的字为
"桥"、"河"、"学"、"道"等。要求至少使用一种平滑方法。
    训练集: 'data\news.txt'
    分析:此模型不同于实验1的HMM,已经不存在隐状态,直接统计词频即可
    思路:统计词频->循环推荐汉字
'''
import re
import heapq

def Construct_Dict():
    '''读取pinyin2hanzi.txt文件,得到所有汉字的列表+汉字在列表中的索引
       读取news.txt文件,统计词频,计算转移概率,加入数据平滑,返回概率矩阵
        return: 
            trans_list:汉字之间的转移概率
            hanzi_list:汉字的列表
            hanzi_index:汉字在列表中的索引
    '''
    #统计汉字
    hanzi_list=[]                       #汉字的列表
    hanzi_index={}                      #汉字在列表中的索引
    i=0
    with open(r'data\pinyin2hanzi.txt','r',encoding='UTF-8-sig') as f:
        while True:
            line=f.readline()
            if not line:                #读取结束
                break
            line=line.replace('\n','')  #去掉结尾换行符
            line=line.split(' ')        #分割为拼音和汉字
            for x in line[1]:
                if x not in hanzi_list: #x是第一次出现的汉字
                    hanzi_list.append(x)
                    hanzi_index[x]=i
                    i+=1

    #语料分句
    N=len(hanzi_list)
    trans_list=[[0]*N for i in range(N)]
    sentence=[]                         #语料库,每个元素为一句不含标点的话的汉字列表
    with open(r'data\news.txt','r',encoding='UTF-8-sig') as f:
        while True:
            line=f.readline()
            if not line:                #读取结束
                break
            line=line.replace('\n','')  #此处line是字符串
            tmp=re.findall('[\u4e00-\u9fa5]+',line)
            if len(tmp):                #对于空行或无中文字符的行不予添加
                sentence.extend(tmp)

    #统计二元词频
    for x in sentence:
        for i in range(len(x)):
            if i==0:                    #语料的第一个字直接跳过
                continue
            else:                       #x[i-1]->x[i]
                if (x[i-1] not in hanzi_list)or(x[i] not in hanzi_list):
                    continue
                else:
                    trans_list[hanzi_index[x[i-1]]][hanzi_index[x[i]]]+=1

    #加一法进行数据平滑
    for i in range(N):
        sum=0
        for j in range(N):
            sum+=(trans_list[i][j]+1)
        for j in range(N):
            trans_list[i][j]=(trans_list[i][j]+1)/sum

    return trans_list,hanzi_list,hanzi_index

if __name__ == '__main__':
    trans_list,hanzi_list,hanzi_index=Construct_Dict()
    N=len(trans_list)
    sentence=''
    print("Please input a Chinese character:")
    while(True):
        word=str(input())
        #提取输入的汉字并作判断
        chn=re.findall('[\u4e00-\u9fa5]',word)
        if len(chn)==0:                 #输入不符合规则
            print('Unallowed input!')
            break
        if word not in hanzi_list:      #字典无法识别输入汉字或输入字数超过1
            print('Unknowed Chinese character!')
            print(sentence,end=' ')
            continue
        sentence+=word
        #预测下一个字
        tmp=trans_list[hanzi_index[word]].copy()    #tmp存储当前汉字转移到下一个汉字的概率
        lst=[]                          #lst存储下一个汉字和其对应的概率
        for i in range(len(tmp)):
            st={}
            st['char']=hanzi_list[i]
            st['p']=tmp[i]
            lst.append(st)
        top5=heapq.nlargest(5,lst,lambda x:x['p'])
        for i in range(5):
            print(top5[i]['char'],end=' ')
        print("\n"+sentence,end=' ')