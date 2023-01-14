'''逆向最大匹配FMM实现中文分词
    语料库: 'data\SogouLabDic.dic'
    算法: 设最长词条长度为I,查找语料库中是否含有测试样本后I个字组成的词:
            若有:将该词作为匹配字段,从第n-I个继续向前划分
            若无:I++,继续查找语料库中是否含有测试样本后I个字组成的词
    思路: 读取语料库->循环切分语句
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

    s_out=''                            #分词后语句,'/'间隔
    for i in range(len(splt_sent)):
        if i>0:
            s_out+='/'
        s_out+=splt_sent[i]
    return s_out

if __name__ == '__main__':
    lexicon,I=getLexicon()              #该词库中最长词条长度为14
    while(True):
        print("Please input a Chinese sentence:")
        sentence=str(input())
        print("分词结果:")
        print(BMM(lexicon,I,sentence))