'''RSA加密
`pip install pycrypto` 后无法导入模块，需要在 python 的安装目录下，找到 \Lib\site-packages\crypto 文件夹，将其更名为 Crypto 即可
'''
from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP

# 加密函数
def encrypt(message, public_key):
    cipher = PKCS1_OAEP.new(public_key)     # 明文长度有限制
    ciphertext = cipher.encrypt(message)
    return ciphertext

# 解密函数
def decrypt(ciphertext, private_key):
    cipher = PKCS1_OAEP.new(private_key)
    message = cipher.decrypt(ciphertext)
    return message

if __name__ == "__main__":
    # 生成RSA密钥对
    key = RSA.generate(2048)
    # 获取公钥和私钥
    public_key = key.publickey()
    private_key = key
    # 要加密的明文
    plaintext = b"CQUWATERMASKEXP"
    # 加密明文
    ciphertext = encrypt(plaintext, public_key)

    print("明文：", plaintext)
    print("密文：", ciphertext)

    # 解密密文
    decrypted_text = decrypt(ciphertext, private_key)
    print("解密后的明文：", decrypted_text)