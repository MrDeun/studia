import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import odeint

def surface(point, time=0):
    return (point[1],-np.sin(point[0]))

fi = np.linspace(-3.14,3.14,21)
om = np.linspace(-2,2,21)
fi,om = np.meshgrid(fi,om)

dfi,dom = surface((fi,om))
plt.quiver(fi,om,dfi,dom,width=0.002,scale=40)
t = np.linspace(0,15,1501)
solution = odeint(surface,[3,0],t)
print(solution)
plt.plot(solution[:,0],solution[:,1])
plt.show()