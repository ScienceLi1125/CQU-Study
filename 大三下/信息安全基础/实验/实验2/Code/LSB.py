from PIL import Image

def hide_message(image_path, message):
    """LSB在图像中隐藏信息
        args:
            image_path: 图像文件路径
            message: 待隐藏的信息
        return:
            hidden_image: 隐藏信息后的图像对象
    """
    # 打开图像
    image = Image.open(image_path)
    binary_message = ''.join(format(ord(c), '08b') for c in message)
    print("原始信息: ", binary_message)
    hidden_image = image.copy()
    # 确定大小
    width, height = image.size
    total_pixels = width * height
    key = len(binary_message)   # 用于确定隐藏信息量的密钥
    if key > total_pixels:
        raise ValueError("Key is larger than total pixels in the image.")
    # 信息隐藏
    pixels_processed = 0
    binary_message2 = ""
    for x in range(width):
        for y in range(height):
            if pixels_processed < key:
                pixel = list(image.getpixel((x, y)))    # RGB的3个8bit像素
                for i in range(len(pixel)):
                    pixel[i] &= 0xFE                    # 将像素的最低bit置0
                    pixel[i] |= int(binary_message[pixels_processed], 2)    # 将隐藏信息写入像素的最低bit
                    pixels_processed += 1
                    binary_message2+=bin(pixel[i])[-1]
                hidden_image.putpixel((x, y), tuple(pixel)) # 将(x,y)位置的像素值更新:[r,g,b]=tuple(pixel)
    print("隐藏信息: ", binary_message2)
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
    extracted_message = ""
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
    # 将二进制消息转换为ASCII码
    for i in range(0, len(binary_message), 8):
        char = chr(int(binary_message[i:i+8], 2))
        extracted_message += char
    return extracted_message

if __name__ == "__main__":
    # 读入图像（建议png，否则会被计算机压缩而失去隐藏信息）
    image_path = r"pic\train.png"
    # 待隐藏的信息和密钥
    message = "CQUWATERMASKEXP"

    # 调用 hide_message() 函数进行信息隐藏
    hidden_image = hide_message(image_path, message)
    # 保存隐藏信息后的图像
    hidden_image_path = r"pic\hidden_train.png"
    hidden_image.save(hidden_image_path)

    # 调用 extract_message() 函数进行信息提取
    key = len(''.join(format(ord(c), '08b') for c in message))
    extracted_message = extract_message(hidden_image_path, key)

    print("提取字符串: ", extracted_message)
