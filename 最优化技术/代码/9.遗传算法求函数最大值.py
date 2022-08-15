#遗传算法求解二元函数f(x,y)最大值
#f(x,y)=3((1-x)^2)*(e^(-x^2-(y+1)^2))-10(x/5-x^3-y^5)*e^(-x^2-y^2)-(1/3)^(e^(-(x+1)^2-y^2))
#-3<=x<=3,-3<=y<=3
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm
from mpl_toolkits.mplot3d import Axes3D
def F(x,y):
	return 3*(1-x)**2*np.exp(-(x**2)-(y+1)**2)-10*(x/5-x**3-y**5)*np.exp(-x**2-y**2)-1/3**np.exp(-(x+1)**2-y**2)
X_bound=[-3,3]          #x、y范围
Y_bound=[-3,3]
DNA_size=24             #DNA链长度(即X/Y编码长度),链长越长,精确度越高                  
POP_size=200            #种群DNA数量(初始点数量),由经验值得到
Crossover_rate=0.8      #交叉概率
Mutaion_rate=0.005      #变异概率
N_Generations=50

#个体编码,一条染色体奇数位为X,偶数位为Y
# X=np.random.randint(X_bound[0],X_bound[1],2*DNA_size)
# Y=np.random.randint(Y_bound[0],Y_bound[1],2*DNA_size)
#其实编码过程并不重要,因为初始种群随机生成,因此随机生成十进制数再映射到编码不如直接生成随机二进制编码
# def Encode(X):
#     return ...
# pop=np.random.randint(2,size=(POP_size,2*DNA_size)) #生成范围[0,2)的随机矩阵(POP_size组编码)

#解码:截取DNA向量为X、Y —>压缩到[0,1] —>映射到[-3,3]
def Decode(pop):
    x_pop=pop[:,1::2]       #奇数列表示x
    y_pop=pop[:,::2]        #偶数列表示y
    x_decimal=x_pop.dot(2**np.arange(DNA_size)[::-1])       #将二进制串解码为十进制数
    y_decimal=y_pop.dot(2**np.arange(DNA_size)[::-1])
    Code_max=2**DNA_size-1  #编码串的最大表示数
    x=x_decimal/Code_max*(X_bound[1]-X_bound[0])+X_bound[0] #将十进制数映射到[-3,3]
    y=y_decimal/Code_max*(Y_bound[1]-Y_bound[0])+Y_bound[0]
    #print(x,y)   
    return x,y

#适应度:将F(x,y)看作是对环境的适应程度,求解最大值时适应程度越大的点留下来的可能性越大
#Max_Fitness函数返回适应程度,由于后面选择时需要概率为正,因此减去最小值使pred为正
#遗传算法不绝对否定谁也不绝对肯定谁,所以最后加上了一个很小的正数以保证最不适应的点也有几率留下来
def Max_Fitness(pop):
    x,y=Decode(pop)
    pred=F(x,y)
    return (pred-np.min(pred))+1e-3
def Min_Fitness(pop):       #求最小值时使用
    x,y=Decode(pop)
    pred=F(x,y)
    return -(pred-np.max(pred))+1e-3
#自然选择:根据适者生存法则将优秀者保留:适应度越高,被选择的机会越高
#np.random.choice(a,size=None,replace=True,p=None):在数组a中按概率数组p取size个数,其中replace为是否可重复
def select(pop,fitness):    #fitness:点的适应度数组
    idx=np.random.choice(np.arange(2*POP_size),size=POP_size,replace=True,p=(fitness)/(fitness.sum()))
    return pop[idx]

#繁殖(交叉+变异):pop为原先种群,作为父母生成孩子,POP_size个父代生成2*POP_size个子代
def Mutation(child,Mutation_rate=0.003):
    if (np.random.rand()<Mutation_rate): 				#以Mutation_rate的概率进行变异
        mutate_point=np.random.randint(0,DNA_size)	    #随机产生要变异基因的位置
        child[mutate_point]=child[mutate_point]^1 	    #异或
def Crossover_Mutation(pop,Crossover_rate=0.8):     #返回子代的DNA数组
    new_pop=[]
    for father in pop:		                        #遍历种群中的每一个个体作为父亲
        child=father		                        #孩子先得到父亲的全部基因
        if (np.random.rand()<Crossover_rate):		#以一定的概率发生交叉
            mother=pop[np.random.randint(POP_size)]	#在种群中随机选择一个个体作为母亲
            cross_points=np.random.randint(low=0,high=DNA_size*2)	#随机产生交叉的点位置
            child[cross_points:]=mother[cross_points:]  #孩子得到位于交叉点后的母亲的基因
        Mutation(child)	#每个后代有一定的机率发生变异
        new_pop.append(child)
    for father in pop:		                        #扩大子代数量给自然选择
        child=father
        if (np.random.rand()<Crossover_rate):
            mother=pop[np.random.randint(POP_size)]
            cross_points=np.random.randint(low=0,high=DNA_size*2)
            child[cross_points:]=mother[cross_points:]
        Mutation(child)
        new_pop.append(child)
    return new_pop

def plot_3d(ax):
    X=np.linspace(*X_bound,100)
    Y=np.linspace(*Y_bound,100)
    X,Y=np.meshgrid(X,Y)
    Z=F(X,Y)
    ax.plot_surface(X,Y,Z,rstride=1,cstride=1,cmap=cm.coolwarm)
    ax.set_zlim(-10,10)
    ax.set_xlabel('x')
    ax.set_ylabel('y')
    ax.set_zlabel('z')
    plt.pause(3)
    plt.show()
def print_info(pop):
    fitness=Max_Fitness(pop)
    max_fitness_index =np.argmax(fitness)   #找到最大值下标
    print("max_fitness:",fitness[max_fitness_index])
    x,y=Decode(pop)
    print("optimal gene: ",pop[max_fitness_index])
    print("(x,y):",(x[max_fitness_index],y[max_fitness_index]))
    print("Max{F(x,y)}:",F(x[0],y[0]))

if __name__ == "__main__":
    fig=plt.figure()
    ax=Axes3D(fig)	
    plt.ion()   #将画图模式改为交互模式,程序遇到plt.show不会暂停,而是继续执行
    plot_3d(ax)
    
    pop=np.random.randint(2,size=(POP_size,2*DNA_size)) #种群初始化

    for i in range(N_Generations):      #迭代N代
        x,y=Decode(pop)
        if 'sca' in locals(): 
            sca.remove()
        sca=ax.scatter(x,y,F(x,y),c='black',marker='o')
        plt.show()
        plt.pause(0.1)
        pop=np.array(Crossover_Mutation(pop,Crossover_rate))
        fitness=Max_Fitness(pop)
        pop=select(pop,fitness)         #选择生成新的种群

    print_info(pop)
    plt.ioff()
    plot_3d(ax)