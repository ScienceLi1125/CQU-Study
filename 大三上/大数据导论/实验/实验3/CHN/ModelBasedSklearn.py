import numpy as np
import os
from sklearn.neighbors import KNeighborsClassifier
import time
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt
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

def main():
    x, y = load_raw()
    x_train, x_test, y_train, y_test = train_test_split(x, y)
    
    print(len(x_train),len(x_test))
    print("load data successful")
    
    print("model train start at: ", time.strftime('%Y-%m-%d %H:%M:%S'))
    
    model_knn = KNeighborsClassifier(n_neighbors=5, n_jobs=-1)
    model_knn.fit(x_train, y_train)
    
    print("model train successful at:", time.strftime('%Y-%m-%d %H:%M:%S'))

    print("knn,n=5 model accuracy：", model_knn.score(x_test, y_test))

if __name__ == "__main__":
    main()
