'''Neural-Network
    构建一个神经网络,利用梯度下降法实现参数的更新,最终实现对0-9的10个手写数字的识别
实现神经网络算法识别手写数字集。
'''
import os
import sys
import gzip
import struct
import numpy as np
import matplotlib.pyplot as plt
from scipy.special import expit

def load_mnist_train(path,kind='train'):    #加载训练集文件
    #path:数据集的路径
    #kind:值为train,代表读取训练集(若为't10k'则为测试集)
    #os用于文件路径拼接
    labels_path=os.path.join(path,'%s-labels-idx1-ubyte.gz'% kind)  #样本标签,即真实值
    images_path=os.path.join(path,'%s-images-idx3-ubyte.gz'% kind)  #样本图片
    #使用gzip读取文件(数据集里的图片,以二进制形式存储),'rb'表示读取二进制数据
    #lbpath即为读取到的二进制数据,使用np.fromstring将其转化成numpy需要的数据形式
    with gzip.open(labels_path,'rb') as lbpath:
	    #使用struct.unpack方法读取前两个数据,>代表高位在前,I代表32位整型。
        #lbpath.read(8)表示一次从文件中读取8个字节(两个数据)
	    #magic number(调用fromfile将字节读入NumPy array之前在文件缓冲中的item数)和样本数n
        magic,n=struct.unpack('>II',lbpath.read(8))
        #lbpath.read()表示读取剩下的所有的数据
        labels=np.frombuffer(lbpath.read(),dtype=np.uint8)
    with gzip.open(images_path,'rb') as imgpath:
        magic,num,rows,cols=struct.unpack('>IIII',imgpath.read(16))
        #28*28=784,即为每个样本图片的所有像素点
        images=np.frombuffer(imgpath.read(),dtype=np.uint8).reshape(len(labels),784)
    '''函数返回两个数组,第一个是一个n*m维的Numpy数组(images),这里的n是样本数,m是特征数。训
    练数据集包含60,000个样本,测试数据集包含10000样本。在MNIST数据集中的每张图片由28*28个像
    素点构成,每个像素点用一个灰度值表示,因此images每行为一个包含784个灰度值的数组。函数返回
    的第二个数组(labels)包含了相应的目标变量,也就是手写数字的类标签(整数0~9)'''
    return images,labels
# X_train,y_train=load_mnist_train('OptimizationTechnology\实验4\MNIST','t10k')
# X_train,y_train=load_mnist_train('OptimizationTechnology\实验4\MNIST')

def show_images_09(X_train,y_train):        #显示数据集中第一个0~9的图像
    fig,ax=plt.subplots(nrows=2,ncols=5,sharex=True,sharey=True)
    #将ax由n*m的Axes组展平成1*nm的Axes组,便于循环遍历
    ax=ax.flatten()
    for i in range(10):
        #y_train==i返回一个boolen型数组,X_train[y_train==i]为所有满足y_train==i的数据集图像
        #img选取X_train中第一个等于i的图像
        img=X_train[y_train==i][0].reshape(28,28)
        #生成热图,主题为“灰色”
        #图像放大算法:最近邻法(Nearest Interpolation)
        ax[i].imshow(img,cmap='Greys',interpolation='nearest')
    ax[0].set_xticks([])
    ax[0].set_yticks([])
    plt.tight_layout()
    plt.show()
# show_images(X_train,y_train)

def show_images_x(X_train,y_train,x,n):     #显示数字x的前n个不同图像(请保证n%5=0)
    fig,ax=plt.subplots(nrows=5,ncols=n//5,sharey=True,sharex=True)
    ax=ax.flatten()
    for i in range(n):
        img=X_train[y_train==x][i].reshape(28,28)
        ax[i].imshow(img,cmap='Greys',interpolation='nearest')
    ax[0].set_xticks([])
    ax[0].set_yticks([])
    plt.tight_layout()
    plt.show()
# show_images_x(X_train,y_train,5,30)

class Neural_Nets(object):
    def __init__(self,n_input,n_output,n_hidden,
        L1=0.0,L2=0.0,epoch_times=1000,
        Eta=0.001,alpha=0.0,de_Eta=0.0,
        shuffle=True,n_minibatch=1,random_seed=1):
        self.n_input=n_input            #输入层特征数
        self.n_output=n_output          #输出层特征数
        self.n_hidden=n_hidden          #隐藏层特征数
        self.w1,self.w2=self.Init_wgt() #前后两层间的权重w(包括偏置b)
        self.L1=L1                      #L1正则化系数(降低过拟合程度)
        self.L2=L2                      #L2正则化系数
        self.epoch_times=epoch_times    #迭代次数
        self.Eta=Eta                    #学习率
        self.alpha=alpha
        self.de_Eta=de_Eta              #随迭代次数增加而降低Eta的常数
        self.shuffle=shuffle            #每次迭代前打乱训练集的顺序以防陷入死循环
        self.n_minibatch=n_minibatch    #小批量的每批的数量
        np.random.seed(random_seed)     #用随机数种子生成随机数

    def Encode_label(self,y,n_out):     #解码标签集y,每个数字对应的图片
        #y为读取的训练集标签集(60000*1),n_out为输出层特征数
        labels=np.zeros((n_out,y.shape[0])) #n_out数(0~9这10个数)作为行数,y的行数(60000)作为列数
        for idx,val in enumerate(y):        #顺序枚举y中元素,idx为序号(0~59999)
            labels[val,idx]=1.0             #这里  
        return labels                   #返回10*60000的np数组,描述每个数字对应的哪些图片  
    def Add_bias(self,X,how='column'):  #为图像集X增加一行/列
        #X为读取的训练集图像集
        #虽然Init_wgt中已经生成随机偏置,但矩阵相乘时需要列行数对应,因此将X扩一列(行)1
        if how=='column':
            X_new=np.ones((X.shape[0],X.shape[1]+1))
            X_new[:,1:]=X
        elif how =='row':
            X_new=np.ones((X.shape[0]+1,X.shape[1]))
            X_new[1:,:]=X
        else:
            raise AttributeError("'how' must be 'column' or 'row'")
        return X_new
    def Init_wgt(self): #初始化输入层->隐藏层的权重w1和偏置b1、隐藏层->输出层的权重w2和偏置b2
        #[-1,1]上均匀分布的随机数并整合成正确大小
        w1=np.random.uniform(-1.0,1.0,size=self.n_hidden*(self.n_input+1))
        w1=w1.reshape(self.n_hidden,self.n_input+1)
        w2=np.random.uniform(-1.0,1.0,size=self.n_output*(self.n_hidden+1))
        w2=w2.reshape(self.n_output,self.n_hidden+1)
        return w1,w2

    def Sigmoid(self,z):    #激活函数
        return expit(z)     #expit等价于1/(1+np.exp(-z))
    def Sigmoid_gradient(self,z):       #激活函数的梯度
        sg=self.Sigmoid(z)
        return sg*(1-sg)                #仅限expit(z)
    def L1_Norm(self,L1,w1,w2):         #L1正则化
        return (L1/2.0)*(np.abs(w1[:,1:]).sum()+np.abs(w2[:,1:]).sum())
    def L2_Norm(self,L2,w1,w2):         #L2正则化
        return (L2/2.0)*(np.sum(w1[:,1:]**2)+np.sum(w2[:,1:]**2))

    def Forward_prop(self,X,w1,w2):     #正向传播
        a1=self.Add_bias(X,how='column')
        z2=w1.dot(a1.T)                 #矩阵相乘(w1×a1的转置)
        a2=self.Sigmoid(z2)             #隐含层的z
        a2=self.Add_bias(a2,how='row')  #将z2激活
        z3=w2.dot(a2)
        a3=self.Sigmoid(z3)
        return a1,z2,a2,z3,a3           #数据集全部返回
    def Get_cost(self,labels,a3,w1,w2): #损失函数(交叉熵)
        #labels为10*60000训练集标签数组,a3为正向传播的输出
        c1=labels*(np.log(a3))
        c2=(1-labels)*np.log(1-a3)
        cost=np.sum(-c1-c2)             #交叉熵
        L1_norm=self.L1_Norm(self.L1,w1,w2)
        L2_norm=self.L2_Norm(self.L2,w1,w2)
        cost=cost+L1_norm+L2_norm
        return cost

    def Get_gradient(self,a1,a2,a3,z2,labels,w1,w2):    #反向传播,计算w2 w2的梯度(下降步长)
        sigma3=a3-labels
        z2=self.Add_bias(z2,how='row')
        sigma2=w2.T.dot(sigma3)*self.Sigmoid_gradient(z2)
        sigma2=sigma2[1:,:]
        grad1=sigma2.dot(a1)            #w1调整
        grad2=sigma3.dot(a2.T)          #w2调整
        grad1[:,1:]+=(w1[:,1:]*(self.L1+self.L2))
        grad2[:,1:]+=(w2[:,1:]*(self.L1+self.L2))
        return grad1,grad2

    def Test(self,X):       #训练结束后,输入图像集X得到每张图像的识别结果
        a1,z2,a2,z3,a3=self.Forward_prop(X,self.w1,self.w2)
        #返回每一列最大元素的行号(由于z3中每列只有1个1其他9个0,因此提取出的就是每个训练图像的真实值)
        ans=np.argmax(z3,axis=0)
        return ans

    def Train(self,X,y,print_progress=False):
        self.costs=[]       #存储每次训练后的损失函数
        X_data,y_data=X.copy(),y.copy()
        labels=self.Encode_label(y,self.n_output)
        d_w1_prev=np.zeros(self.w1.shape)   #前一次w下降步长
        d_w2_prev=np.zeros(self.w2.shape)

        for i in range(self.epoch_times):
            self.Eta/=(1+self.de_Eta*i) #随迭代次数增加而降低Eta
            # print('\rEpoch times:%d/%d'%(i+1,self.epoch_times))
            if print_progress:          #错误标准输出(后面的可以刷掉前面的)
                # sys.stderr.write('\rEpoch times: %d/%d'%(i+1,self.epoch_times))
                sys.stderr.write("\rEpoch times: %d/%d "%(i+1,self.epoch_times)+"▋"*(i//20))
                sys.stderr.flush()
            if self.shuffle:            #打乱训练集的顺序以防陷入死循环
                #np.random.permutation(n)对[0,3)范围内的数字随机排序
                idx=np.random.permutation(y_data.shape[0])  #y_data的行之间随机打乱
                X_data,y_data=X_data[idx],y_data[idx]
            #将y_data所有行按顺序等分成n_minibatch组
            mini=np.array_split(range(y_data.shape[0]),self.n_minibatch)
            for sub in mini:            #每个小批量进行正向传播并优化参数
                #正向传播并计算损失函数
                a1,z2,a2,z3,a3=self.Forward_prop(X[sub],self.w1,self.w2)
                cst=self.Get_cost(labels[:,sub],a3,self.w1,self.w2)
                self.costs.append(cst)
                #反向传播计算梯度
                grad1,grad2=self.Get_gradient(a1,a2,a3,z2,labels[:,sub],self.w1,self.w2)
                #更新权重
                d_w1=self.Eta*grad1     #当前w下降步长
                d_w2=self.Eta*grad2
                self.w1-=(d_w1+(self.alpha*d_w1_prev))
                self.w2-=(d_w2+(self.alpha*d_w2_prev))
                d_w1_prev,d_w2_prev=d_w1,d_w2
        return self

def costplt1(nn):       #所有代价
    plt.plot(range(len(nn.costs)),nn.costs)
    plt.ylim([0,2000])
    plt.ylabel('Cost')
    plt.xlabel('Epoch_times*50')
    plt.tight_layout()
    plt.show()

def costplt2(nn):       #每次(训练代价的均值)
    #np.array_split(array,n)将array分成n组
    idx=np.array_split(range(len(nn.costs)),1000)   #costs分为1000组(训练次数)的坐标数组
    costs=np.array(nn.costs)
    costs_avg=[np.mean(costs[i]) for i in idx]      #每组costs的平均值
    plt.plot(range(len(costs_avg)),costs_avg,color='red')
    plt.ylim([0,10000])
    plt.ylabel('Cost/train')
    plt.xlabel('Epoch_times')
    plt.tight_layout()
    plt.show()

if __name__ == '__main__':
    #读取训练样本和测试样本
    path = 'OptimizationTechnology\\实验4\\MNIST'
    X_train,y_train=load_mnist_train(path,kind='train') #X_train:60000*784
    X_test,y_test=load_mnist_train(path,kind='t10k')    #X_test:10000*784
    #训练样本并绘制损失函数
    nn=Neural_Nets(X_train.shape[1],10,50,0.0,0.1,1000,0.001,0.001,0.00001,True,50,1)
    nn.Train(X_train,y_train,True)      #训练结束后w和b被优化至最佳
    costplt1(nn)
    costplt2(nn)
    #训练集和测试集的结果及准确度
    train_ans=nn.Test(X_train)          #训练集每个图像识别出来的结果
    acc=np.sum(y_train==train_ans,axis=0)/X_train.shape[0]
    print('\n训练准确率: %.2f%%'%(acc*100))
    test_ans=nn.Test(X_test)            #测试集每个图像识别出来的结果
    acc=np.sum(y_test==test_ans,axis=0)/X_test.shape[0]
    print('测试准确率: %.2f%%'%(acc*100))
    #前30个错误样本
    wrong_img=X_test[y_test!=test_ans][:30]     #截取前30个
    real_lab=y_test[y_test!=test_ans][:30]
    wrong_lab=test_ans[y_test!=test_ans][:30]
    fig,ax=plt.subplots(nrows=5,ncols=6,sharex=True,sharey=True)
    ax=ax.flatten()
    for i in range(30):
        img=wrong_img[i].reshape(28,28)
        ax[i].imshow(img,cmap='Greys',interpolation='nearest')
        ax[i].set_title('train:%d'%(wrong_lab[i]))
    ax[0].set_xticks([])
    ax[0].set_yticks([])
    plt.tight_layout()
    plt.show()
    #前30个正确样本
    right_img=X_test[y_test==test_ans][:30]
    real_lab=y_test[y_test==test_ans][:30]
    right_lab=test_ans[y_test==test_ans][:30]
    fig,ax=plt.subplots(nrows=5,ncols=6,sharex=True,sharey=True)
    ax=ax.flatten()
    for i in range(30):
        img=right_img[i].reshape(28,28)
        ax[i].imshow(img,cmap='Greys',interpolation='nearest')
        ax[i].set_title('train:%d'%(right_lab[i]))
    ax[0].set_xticks([])
    ax[0].set_yticks([])
    plt.tight_layout()
    plt.show()