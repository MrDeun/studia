import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
X = np.linspace(-1.57,1.57,100)
X,Y = np.meshgrid(X,X)
Z = np.sin(2*X)+1.5*np.cos(Y)**4+2*np.cos(X+Y)

print(X,Y,Z)
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d') 
surf=ax.plot_surface(X,Y,Z,rstride=1,cstride=1,linewidth=0,cmap='jet')
plt.show()