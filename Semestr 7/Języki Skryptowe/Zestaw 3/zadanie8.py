import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import odeint
from matplotlib.animation import FuncAnimation

GM = 6.674e-11 * 1.988e30 * (8.64e4) ** 2 * (1e-9) ** 3  # [Gm^3/d^2]


def pole(X, t=0):
    x, y, vx, vy = X
    dx = vx
    dy = vy
    m = (x**2 + y**2) ** 1.5
    dvx = -GM * x / m
    dvy = -GM * y / m
    return [dx, dy, dvx, dvy]


wp = [152, 0, 0, 2.53]
t = np.linspace(0, 365, 3651)
rozw = odeint(pole, wp, t)
rozw = rozw[::6, :]

fig, ax = plt.subplots()
tx = [rozw[0, 0]]
ty = [rozw[0, 1]]
tr = ax.plot(tx, ty, color="g")[0]
z = ax.plot([rozw[0, 0]], [rozw[0, 1]], "ob")[0]
s = ax.plot([0], [0], "oy")[0]


def anim(i):
    # print(rozw)
    tx.append(rozw[i, 0])
    ty.append(rozw[i, 1])
    tr.set_xdata(tx)
    tr.set_ydata(ty)
    z.set_xdata([rozw[i, 0]])
    z.set_ydata([rozw[i, 1]])


a = FuncAnimation(fig, anim, range(len(rozw)), interval=200, repeat=False)
ax.set_xlim([-240, 240])
ax.set_ylim([-180, 180])
plt.show()
