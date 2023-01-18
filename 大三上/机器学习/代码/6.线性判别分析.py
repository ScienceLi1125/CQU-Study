import numpy as np
from matplotlib import pyplot as plt


def load_dataset():
    file = open(r'ML\data\melon3_dataset.txt')
    dataMat = []
    labelMat = []
    for line in file.readlines():
        lineArr = line.strip().split()
        dataMat.append([float(lineArr[0]), float(lineArr[1])])
        labelMat.append(int(lineArr[2]))
    return dataMat, labelMat


def mat_plot(w, data):
    fig = plt.figure()
    ax = fig.add_subplot(111)
    n = np.shape(data)[0]
    for i in range(n):
        if i < 8:
            ax.scatter(data[i, 0], data[i, 1], c='r')
        else:
            ax.scatter(data[i, 0], data[i, 1], c='b')
    x = np.arange(0, 1, 0.01)
    print(np.shape(w))
    print(w)
    y = (w[1, 0] / w[0, 0]) * x
    ax.plot(x, y)
    plt.xlim(0, 1)
    plt.ylim(0, 0.5)
    plt.show()


def model():
    dataMat, labelMat = load_dataset()
    data = np.array(dataMat)
    X_0 = np.array(data[:8])
    X_1 = np.array(data[8:])
    miu_0 = np.mean(X_0, axis=0).reshape((-1, 1))
    miu_1 = np.mean(X_1, axis=0).reshape((-1, 1))
    cov_0 = np.cov(X_0, rowvar=False)
    cov_1 = np.cov(X_1, rowvar=False)
    print(np.shape(X_0))
    print(cov_0)
    S_w = np.mat(cov_0 + cov_1)
    Omega = S_w.I * (miu_0 - miu_1)
    mat_plot(Omega, data)


if __name__ == '__main__':
    model()
