'''Feistel网络加密解密文本
    Feistel加密：先将输入明文字符串M编码为二进制形式(str类型)，然后循环加密，最后输出密文C；
    Feistel解密：先将密文C分解为两段，解密后将得到的二进制串还原为字符串；
    因为python中没有二进制数据类型，二进制只能通过字符串形式存储；
    为了轮中运算方便，在运算中统一使用 int(bin_s,2)将二进制串转换成十进制整数进行存储。
'''
import random
import hashlib

def Get_Key(K,n):
    '''密钥生成函数
        args:
            K: 密钥(int)
            n: 生成密钥数，即加密轮数(int)
        return:
            Kis: 每轮的密钥(list[str])
    '''
    # 将int转换为二进制编码，去掉开头0b
    K=bin(K)[2:]
    # 计算Ki大小
    K_size = len(K)//n
    # 将原始密钥分成多个块
    blocks = [K[K_size*j : K_size*(j+1)] for j in range(n)]
    Kis = []
    for block in blocks:
        Kis.append(block)
    return Kis


def F(R,K):
    '''对R加密的F函数，这里使用SHA256，得到256位的二进制数
        args:
            R: 密文(int)
            K: 密钥(int)
        return:
            bin_R_hashed: 加密后的二进制形式R值(str)
    '''
    # 调用hashlib模块中的SHA256算法，输入需要转换为字节串，得到一个sha256哈希对象
    hash_object = hashlib.sha256(str(K).encode('utf-8')+str(R).encode('utf-8'))
    # 哈希摘要将哈希对象压缩为固定长度的字节串
    R_hashed = hash_object.digest()
    # 将字节串转换为二进制串输出
    bin_R_hashed = bin(int.from_bytes(R_hashed, byteorder='big'))
    return bin_R_hashed


def str2bin(message):
    '''将字符串转换为对应的二进制编码(str类型)
        args:
            message: 明文字符串(str)
        return:
            bin_M: 明文字符串的二进制编码(str)
    '''
    # 将输入消息转换为16位二进制格式(1byte=8bit，为了L0和R0能均分，故编码时保留16位整数倍)，不足16位的在前面补0
    bin_M = ''.join(format(ord(c), '016b') for c in message)
    # 此处返回的还是str类型
    return bin_M


def bin2str(bin_M):
    '''将二进制编码(str类型)转换为字符串
        args:
            bin_M: 二进制编码(str)
        return:
            message: 明文(str)
    '''
    bin_M=bin_M[2:]                        # 去掉二进制串开头的0b
    bin_M=bin_M.zfill((len(bin_M)+7)//8*8) # 按8位补齐
    message=''
    for i in range(0,len(bin_M),8):
        bin_substr = bin_M[i:i+8]
        n = int(bin_substr,2)
        char = chr(n)
        message += char
    return message


def Feistel_encode(M,K,round=16):
    '''菲斯特尔加密网络
        args:
            M: 明文字符串(str)
            K: 密钥(str型)
            round: 加密轮数(int)
        return:
            C: 十进制数表示的密文(str)
    '''
    # 将输入消息字符串转换为二进制串
    bin_M = str2bin(M)
    # 分割出L0和R0
    L0,R0 = bin_M[:len(bin_M)//2], bin_M[len(bin_M)//2:]
    # print(len(L0),L0)
    # print(R0)
    # 加密
    L=[int(L0,2)]       # 二进制串转换成数字类型会以十进制int形式存储
    R=[int(R0,2)]
    Kis=Get_Key(K,round)
    for i in range(round):
        preR=R[-1]
        preL=L[-1]
        curL=preR
        curR=preL^int(F(preR,Kis[i]),2)
        L.append(curL)
        R.append(curR)
    # print(L,'\n',R)
    C=str(L[-1])+str(R[-1])
    return C


def Feistel_decode(C,K,round=16):
    '''菲斯特尔解密网络
        args:
            C: 十进制数表示的密文(str)
            K: 密钥(int)
            round: 加密轮数(int)
        return:
            result: 明文字符串(str)
    '''
    # 将密文十进制字符串转换为二进制串
    Ln,Rn = C[:len(C)//2], C[len(C)//2:]
    # 解密
    L=[int(Ln,10)]
    R=[int(Rn,10)]
    Kis=Get_Key(K,round)
    for i in range(round):
        preR=R[-1]
        preL=L[-1]
        curR=preL
        curL=preR^int(F(preL,Kis[round-i-1]),2)
        L.append(curL)
        R.append(curR)
    # 将二进制明文还原为明文字符串
    M=bin2str(bin(int(L[-1])))+bin2str(bin(int(R[-1])))
    return M


if __name__ == '__main__':
    print('M:',end=' ')
    M=input()
    round=16
    K=random.randint(10000000,99999999)
    C_encode=Feistel_encode(M,K,round)
    print('Encoded M:',C_encode)
    M_decode=Feistel_decode(str(C_encode),K,round)
    print('Decoded M:',M_decode)