'''身份验证的RSA加密
'''
from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_v1_5

# 加密函数
def encrypt(message, public_key):
    cipher = PKCS1_v1_5.new(public_key)     # 不限制明文长度
    ciphertext = cipher.encrypt(message)
    return ciphertext

# 解密函数
def decrypt(ciphertext, private_key):
    cipher = PKCS1_v1_5.new(private_key)
    message = cipher.decrypt(ciphertext, None)
    return message

if __name__ == "__main__":
    # 生成RSA密钥对
    key1 = RSA.generate(1024)   # A的密钥用于认证A
    key2 = RSA.generate(4096)   # B的密钥用于认证B
    # 获取公钥和私钥
    public_key1 = key1.publickey()
    private_key1 = key1
    public_key2 = key2.publickey()
    private_key2 = key2

    # 要加密的明文
    plaintext = b"CQUWATERMASKEXP"
    print("明文：", plaintext)

    # 使用A的公钥加密明文
    ciphertext1 = encrypt(plaintext, public_key1)
    # 使用B的公钥加密明文
    ciphertext2 = encrypt(ciphertext1, public_key2)
    print("密文：", ciphertext2)

    # 使用B的私钥解密密文
    decrypted_text2 = decrypt(ciphertext2, private_key2)
    # 使用A的私钥解密密文
    decrypted_text1 = decrypt(decrypted_text2, private_key1)
    print("解密后的明文：", decrypted_text1)