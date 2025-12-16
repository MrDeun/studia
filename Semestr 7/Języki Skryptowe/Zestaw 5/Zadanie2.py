import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import odeint
from matplotlib.animation import FuncAnimation


def pole(p, t):
    x, y, vx, vy = p
    dx = vx
    dy = vy
    if x < 0:
        dvx = 1e6
    elif x > 10:
        dvx = -1e6
    else:
        dvx = 0
    if y < 0:
        dvy = 1e6
    else:
        dvy = -9.81
    return (dx, dy, dvx, dvy)


t = np.arange(0, 15, 0.01)
rozw = odeint(pole, [1, 10, 3, 0], t)
fig, ax = plt.subplots()
ax.plot([0, 0, 10, 10], [15, 0, 0, 15], linewidth=2)
k = ax.plot(rozw[:1, 0], rozw[:1, 1], "og")[0]
tr = ax.plot([], [])[0]


def anim(i):
    k.set_xdata([rozw[i, 0]])
    k.set_ydata([rozw[i, 1]])
    tr.set_xdata(rozw[:i, 0])
    tr.set_ydata(rozw[:i, 1])


a = FuncAnimation(fig, anim, range(len(t)), interval=10, repeat=False)
ax.set_xlim([-5.5, 16.5])
ax.set_ylim([-0.5, 16])
plt.show()
