'''频率分析法解密文本
'''

# 字母出现频率的统计规律排序
freq=['E','T','A','O','N','I','S','R','H','L','D','C','U','P','F','M','W','Y','B','G','V','K','Q','X','J','Z']
# 密文
sentence="UZ QSO VUOHXMOPV GPOZPEVSG ZWSZ OPFPESX UDBMETSX AIZ VUEPHZ HMDZSHZO WSFP APPD TSVP QUZW YMXUZUHSX EPYEPOPDZSZUFPO MB ZWP FUPZ HMDJ UD TMOHMQ"
# 统计sentence中字母频率
dic={}
for c in sentence:
    if(c==' '):
        continue
    else:
        if(c in dic):
            dic[c]+=1
        else:
            dic[c]=1
# 补齐sentence中缺失字母
for x in freq:
    if x not in sentence:
        dic[x]=0
# 对dic中键值对按value降序排列，得到一个元组列表
sorted_dic = sorted(dic.items(), key=lambda x: -x[1])
for x in sorted_dic:
    print("%c: %f%%" % (x[0],x[1]/1.2))

'''
# 构造转换表
transfer_sheet={}
for i in range(26):
    transfer_sheet[sorted_dic[i][0]]=freq[i]

# 解密密文
for c in sentence:
    if(c==' '):
        print(' ',end='')
    else:
        print(transfer_sheet[c],end='')
'''
transfer_sheet={}
C="IT WAS DISCLOSED YESTERDAY THAT SEVERAL INFORMAL BUT DIRECT CONTACTS HAVE BEEN MADE WITH POLITICAL REPRESENTATIVES OF THE VIET CONG IN MOSCOW"
for i in range(len(C)):
    if(C[i]==' '):
        continue
    else:
        if(C[i] not in transfer_sheet):
            transfer_sheet[C[i]]=sentence[i]
for x in transfer_sheet:
    print(x,':',transfer_sheet[x])