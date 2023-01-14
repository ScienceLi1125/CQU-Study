'''双向最大匹配BiDMM实现中文分词
    语料库: 'data\SogouLabDic.dic'
    算法: 正向匹配算法->逆向匹配算法->选取分词数量较少的作为结果->分词数相同时选择单字较少的作为结果
    思路: 读取语料库->FMM->BMM->BiDMM
'''

def getLexicon():
    '''读取SogouLabDic.dic文件,得到词库和最长词条长度'''
    lexicon=set()                       #词库
    path=r'data\SogouLabDic.dic'
    I=0                                 #最长词条所含汉字数
    with open(path,'r') as f:
        while True:
            line=f.readline()
            if not line:                #读取结束
                break
            line=line.split('	')      #分割为词组、频数和词性
            word=line[0]                #词组
            I=max(I,len(word))
            lexicon.add(word)
    return lexicon,I

def FMM(lexicon,I,sentence):
    '''使用FMM算法对样本sentence进行分词'''
    splt_sent=[]                        #存储划分成词的句子
    ptr1=0                              #指向sentence正在查找字段的指针
    ptr2=min(I,len(sentence))
    while(ptr1<len(sentence)):
        if((ptr1+1)==ptr2):             #只剩一个字
            splt_sent.append(sentence[ptr1])
            ptr1=ptr2
            ptr2=min(ptr1+I,len(sentence))
            continue
        word=sentence[ptr1:ptr2]
        if word in lexicon:             #匹配成功
            splt_sent.append(word)
            ptr1=ptr2                   #更新指针
            ptr2=min(ptr1+I,len(sentence))
        else:                           #匹配失败
            ptr2-=1
    return splt_sent

def BMM(lexicon,I,sentence):
    '''使用BMM算法对样本sentence进行分词'''
    splt_sent=[]                        #存储划分成词的句子
    ptr1=len(sentence)-1                #指向sentence正在查找字段的指针
    ptr2=max(len(sentence)-I,-1)
    while(ptr1>-1):
        if((ptr1-1)==ptr2):             #只剩一个字
            splt_sent.insert(0,sentence[ptr1])
            ptr1=ptr2
            ptr2=max(ptr1-I,-1)
            continue
        word=sentence[ptr2+1:ptr1+1]
        if word in lexicon:             #匹配成功
            splt_sent.insert(0,word)
            ptr1=ptr2                   #更新指针
            ptr2=max(ptr1-I,-1)
        else:                           #匹配失败
            ptr2+=1
    return splt_sent

def Lst2Str(lst):
    '''将列表分词转换成"/"间隔的字符串'''
    s_out=''                            #分词后语句,'/'间隔
    for i in range(len(lst)):
        if i>0:
            s_out+='/'
        s_out+=lst[i]
    return s_out

def Disambiguate(lst1,lst2):
    '''分词消歧启发式规则,选择分词数量较少的作为结果;如果一样,选择单字较少的作为结果'''
    if(len(lst1)>len(lst2)):
        return lst2
    elif(len(lst1)<len(lst2)):
        return lst1
    else:
        cnt1=0
        cnt2=0
        for i in range(len(lst1)):
            if(len(lst1[i])==1):
                cnt1+=1
            if(len(lst2[i])==1):
                cnt2+=1
        if(cnt1<cnt2):
            return lst1
        else:
            return lst2

if __name__ == '__main__':
    lexicon,I=getLexicon()              #该词库中最长词条长度为14
    while(True):
        print("Please input a Chinese sentence:")
        sentence=str(input())
        print("分词结果:")
        fmm=FMM(lexicon,I,sentence)
        bmm=BMM(lexicon,I,sentence)
        print(Lst2Str(Disambiguate(fmm,bmm)))
