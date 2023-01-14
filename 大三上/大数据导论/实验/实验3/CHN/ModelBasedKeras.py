import os.path as osp
import glob
from PIL import Image
import numpy as np

import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split

IMAGE_DIR="./RawDataset"

def _get_label(pic_name):
    set_str = pic_name.strip("Locate{}.jpg")  # cut paddings
    label = set_str[-set_str[::-1].index(","):] # get label after the last ','
    return int(label) - 1

def load_data():
    file_list = glob.glob(IMAGE_DIR + "/*.jpg")
    x = []
    y = []
    for fname in file_list:
        with Image.open(fname) as img:
            np_img = np.array(img)
        label = _get_label(osp.split(fname)[-1])
        x.append(np_img)
        y.append(label)
    x, y = np.array(x), np.array(y)
    x = np.expand_dims(x, -1)
    x = x / 255.
    return x, y
    
x, y = load_data()
print("load data successful")

# split the data into training and test sets
x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.2)
print("split data successful")

from tensorflow.keras import Sequential
from tensorflow.keras.layers import Conv2D, MaxPool2D, Dense, Flatten

# create the model
model = Sequential([
    Conv2D(6, 5, activation='relu', input_shape=x_train.shape[1:]),
    MaxPool2D(2),
    Conv2D(16, 5, activation='relu',),
    MaxPool2D(2),
    Flatten(),
    Dense(120, activation='relu'),
    Dense(84, activation='relu'),
    Dense(15, activation='softmax')
])


from tensorflow.keras.optimizers import Adam

# configure the model for training
model.compile(loss='sparse_categorical_crossentropy',
              optimizer=Adam(lr=0.001),
              metrics=['acc'])

model.summary()

# train the model
model.fit(x_train, y_train, validation_data=(x_test, y_test), epochs=10, batch_size=4, verbose=2)
