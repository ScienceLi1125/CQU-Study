from PIL import Image
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

def hide_message(image_path, message):
    """LSB在图像中隐藏信息
        args:
            image_path: 图像文件路径
            message: 待隐藏的加密过的信息(二进制串形式)
        return:
            hidden_image: 隐藏信息后的图像对象
    """
    # 打开图像
    image = Image.open(image_path)
    print("原始信息: ", message)
    hidden_image = image.copy()
    # 确定大小
    width, height = image.size
    total_pixels = width * height
    key = len(message)   # 用于确定隐藏信息量的密钥
    if key > total_pixels:
        raise ValueError("Key is larger than total pixels in the image.")
    # 信息隐藏
    pixels_processed = 0
    message2 = ""
    for x in range(width):
        for y in range(height):
            pixel = list(image.getpixel((x, y)))    # RGB的3个8bit像素
            for i in range(len(pixel)):
                if pixels_processed < key:
                    pixel[i] &= 0xFE                    # 将像素的最低bit置0
                    pixel[i] |= int(message[pixels_processed], 2)    # 将隐藏信息写入像素的最低bit
                    pixels_processed += 1
                    message2+=bin(pixel[i])[-1]
            hidden_image.putpixel((x, y), tuple(pixel)) # 将(x,y)位置的像素值更新:[r,g,b]=tuple(pixel)
    print("隐藏信息: ", message2)
    return hidden_image

def extract_message(hidden_image_path, key):
    """LSB从图像中提取隐藏信息
        args:
            hidden_image_path: 隐藏信息后的图像文件路径
            key: 用于确定隐藏信息量的密钥
        return:
            extracted_message: 提取出的信息
    """
    # 打开图像
    hidden_image = Image.open(hidden_image_path)
    image = hidden_image.copy()
    # 确定大小
    width, height = image.size
    total_pixels = width * height
    if key > total_pixels:
        raise ValueError("Key is larger than total pixels in the image.")
    # 提取信息
    pixels_processed = 0
    binary_message = ""
    for x in range(width):
        for y in range(height):
            pixel = list(image.getpixel((x, y)))
            for i in range(len(pixel)):
                if pixels_processed < key:  # 否则读取字符串过长
                    extracted_bit = pixel[i] & 0x01         # 提取像素的最低1bit
                    binary_message += str(extracted_bit)    # 将提取的bit添加到二进制消息中
                    pixels_processed += 1
    print("提取信息: ", binary_message)
    return binary_message

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
    # 使用B的公钥加密明文,结果形式为字节流
    ciphertext2 = encrypt(ciphertext1, public_key2)
    # ciphertext3 = ciphertext2.decode('utf-8')   # 转换为字符串(无法解析)
    binary_ciphertext2 = ''.join(format(b, '08b') for b in ciphertext2)   # 转换为二进制串
    print("密文：", ciphertext2)

    # 读入图像
    image_path = r"pic\train.png"

    # 调用 hide_message() 函数进行信息隐藏
    hidden_image = hide_message(image_path, binary_ciphertext2)
    # 保存隐藏信息后的图像
    hidden_image_path = r"pic\hidden_train2.png"
    hidden_image.save(hidden_image_path)

    # 调用 extract_message() 函数进行信息提取
    key = len(binary_ciphertext2)
    binary_message = extract_message(hidden_image_path, key)
    integer = int(binary_message, 2)
    extracted_message = integer.to_bytes((integer.bit_length() + 7) // 8, byteorder='big')

    # 使用B的私钥解密密文
    decrypted_text2 = decrypt(extracted_message, private_key2)
    # 使用A的私钥解密密文
    decrypted_text1 = decrypt(decrypted_text2, private_key1)

    print("解密后的明文：", decrypted_text1.decode('utf-8'))