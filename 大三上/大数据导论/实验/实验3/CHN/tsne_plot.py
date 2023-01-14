# TSNE 降维并绘图程序 可以将n维数据 x, y 降维到 2维 并绘图
import numpy as np
import matplotlib.pyplot as plt
import os

data_dir = "RawDataset"

def _get_label(pic_name):
    set_str = pic_name.strip("Locate{}.jpg")  # cut paddings
    label = set_str[-set_str[::-1].index(","):] # get label after the last ','
    return int(label)-1

def _get_pic_data(dir_name):
    pic_names = os.listdir(dir_name)
    img_arrs, labels = [], []
    for pic_name in pic_names:
        imgarr = plt.imread(dir_name + "/" + pic_name)
        img_arr = imgarr.reshape(4096)
        label = _get_label(pic_name)
        img_arrs.append(img_arr)
        labels.append(label)
    return img_arrs, labels

def load_raw():
    x, y = _get_pic_data(data_dir)
    x = np.array(x)
    y = np.array(y)
    return x, y

x, y = load_raw()

print(x.shape,y.shape)

from sklearn.manifold import TSNE
df = TSNE(n_components=2).fit_transform(x)
vx = df[:,0]
vy = df[:,1]
label = y
plt.scatter(vx, vy, c=label, s=1, cmap=plt.cm.get_cmap("jet", 15))
plt.show()
