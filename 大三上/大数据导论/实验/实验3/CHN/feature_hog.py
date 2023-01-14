import numpy as np
import matplotlib.pyplot as plt
import os
from sklearn.model_selection import train_test_split

# 使用skimage库来处理hog特征,这个库的效果不如opencv,但是opencv在centos上可能安装出错
# 如果你知道如何解决opencv-python的编译问题,可以使用opencv
from skimage.feature import hog


data_dir = "RawDataset"

def _get_label(pic_name):
    set_str = pic_name.strip("Locate{}.jpg")  # cut paddings
    label = set_str[-set_str[::-1].index(","):] # get label after the last ','
    return int(label)-1

def _get_pic_data(dir_name):
    pic_names = os.listdir(dir_name)
    img_arrs, labels = [], []
    for pic_name in pic_names:
        imgarr = plt.imread(dir_name + "/" + pic_name)   # matplot读图片
        img_arr = hog(imgarr, cells_per_block=(2, 2))    # hog特征计算
        label = _get_label(pic_name)                     # 求图片的标签
        img_arrs.append(img_arr)
        labels.append(label)
    return img_arrs, labels


# 如果可以正常安装opencv-python,使用下面的参数来处理hog特征提取,否则使用skimage库来处理
# ~ from cv2 import HOGDescriptor
# ~ winSize = (64,64)
# ~ blockSize = (16,16)
# ~ blockStride = (8,8)
# ~ cellSize = (8,8)
# ~ nbins = 9
# ~ derivAperture = 1
# ~ winSigma = 4.
# ~ histogramNormType = 0
# ~ L2HysThreshold = 2.0000000000000001e-01
# ~ gammaCorrection = 0
# ~ nlevels = 64
# ~ hog = HOGDescriptor(winSize,blockSize,blockStride,cellSize,nbins,derivAperture,winSigma,
                    # ~ histogramNormType,L2HysThreshold,gammaCorrection,nlevels)
# ~ img_arr = hog.compute(imgarr)

def load_raw():
    """获取特征数据集，x是feature，y是label"""
    x, y = _get_pic_data(data_dir)
    x = [i.reshape(1764) for i in x]
    x = np.array(x)
    y = np.array(y)
    return x, y

x, y = load_raw()
print("load data successful")

x_train, x_test, y_train, y_test = train_test_split(x, y)  # 借助sklearn进行划分

# 连接数据集，这里需要生成X*1765的数据，1765=1764+1，1764是hog特征值，1是label，X是长度
train_df = np.concatenate((x_train,np.expand_dims(y_train,1)),1)
test_df = np.concatenate((x_test,np.expand_dims(y_test,1)),1)

# 写成csv文件
np.savetxt("src/train.csv",train_df,delimiter=",",fmt="%.1f")
np.savetxt("src/test.csv",test_df,delimiter=",",fmt="%.1f")

print("data saved successful")
