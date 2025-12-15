import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

_range = np.linspace(-np.pi,np.pi,50)

x,y = np.meshgrid(_range,_range)

func = np.sin(2*x) + 1.5 * np.cos(4*y) + 2*np.cos(x+y)
grad = np.gradient(func)
plt.contour(x,y,func)
x=x[::5,::5]
y=y[::5,::5]

vx = 2*np.cos(2*x)-2*np.sin(x+y)
vy = -6*np.cos(y)**3*np.sin(y)-2*np.sin(x+y)

plt.quiver(x,y,vx,vy)
plt.show()