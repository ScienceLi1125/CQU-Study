import numpy as np
from matplotlib import pyplot as plt

fig,ax = plt.subplots(figsize=(8,5))
X=np.linspace(-5,5,200)
Y=X*X
A=np.linspace(-5,0,10)
B=A*A
plt.plot(X,Y,color='royalblue')
plt.scatter(A,B,color='orangered')
for i in range(9):
    a1=A[i]
    b1=B[i]
    a2=A[i+1]
    b2=B[i+1]
    ax.annotate("",
                xy=(a2, b2),
                xytext=(a1, b1),
                arrowprops=dict(arrowstyle="->", color="r"))

plt.show()