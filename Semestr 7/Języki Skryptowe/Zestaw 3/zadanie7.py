import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import odeint
from matplotlib.animation import FuncAnimation

mass1 = 1.5
mass2 = 2  # [kg]
lenght1 = 1
lenght2 = 0.6  # [m]
g = 9.81  # [m/s^2]
a = mass1 * lenght1**2 / 3 + mass2 * lenght1**2
c = mass2 * lenght2**2 / 3
b = mass2 * lenght1 * lenght2 / 2
p = (mass1 / 2 + mass2) * g * lenght1
q = mass2 * g * lenght2 / 2


def pole(X, t=0):
    mianownik = a * c - (b * np.cos(X[1] - X[0])) ** 2
    delta_teta1 = X[2]
    delta_teta2 = X[3]
    z1 = b * np.sin(X[0] - X[1]) * X[3] ** 2 + p * np.sin(X[0])
    z2 = b * np.sin(X[1] - X[0]) * X[2] ** 2 + q * np.sin(X[1])
    delta_omega1 = -(c * z1 - b * np.cos(X[0] - X[1]) * z2) / mianownik
    delta_omega2 = -(a * z2 - b * np.cos(X[1] - X[0]) * z1) / mianownik
    return [delta_teta1, delta_teta2, delta_omega1, delta_omega2]


t = np.linspace(0, 10, 1001)
rozw = odeint(pole, [3 * np.pi / 4, 3 * np.pi / 4, 0, 0], t)
fig, ax = plt.subplots()
tx = [100 * lenght1 * np.sin(rozw[0, 0]) + 100 * lenght2 * np.sin(rozw[0, 1])]
ty = [-100 * lenght1 * np.cos(rozw[0, 0]) - 100 * lenght2 * np.cos(rozw[0, 1])]
tr = ax.plot(tx, ty, color="g")[0]
pret1 = ax.plot(
    [0, 100 * lenght1 * np.sin(rozw[0, 0])],
    [0, -100 * lenght1 * np.cos(rozw[0, 0])],
    linewidth=2,
    color="r",
)[0]
pret2 = ax.plot(
    [0, 100 * lenght1 * np.sin(rozw[0, 0]) + 100 * lenght2 * np.sin(rozw[0, 1])],
    [0, -100 * lenght1 * np.cos(rozw[0, 0]) - 100 * lenght2 * np.cos(rozw[0, 1])],
    linewidth=2,
    color="r",
)[0]


def anim(i):
    pret1.set_xdata([0, 100 * lenght1 * np.sin(rozw[i, 0])])
    pret1.set_ydata([0, -100 * lenght1 * np.cos(rozw[i, 0])])
    pret2.set_xdata(
        [
            100 * lenght1 * np.sin(rozw[i, 0]),
            100 * lenght1 * np.sin(rozw[i, 0]) + 100 * lenght2 * np.sin(rozw[i, 1]),
        ]
    )
    pret2.set_ydata(
        [
            -100 * lenght1 * np.cos(rozw[i, 0]),
            -100 * lenght1 * np.cos(rozw[i, 0]) - 100 * lenght2 * np.cos(rozw[i, 1]),
        ]
    )
    tx.append(100 * lenght1 * np.sin(rozw[i, 0]) + 100 * lenght2 * np.sin(rozw[i, 1]))
    ty.append(-100 * lenght1 * np.cos(rozw[i, 0]) - 100 * lenght2 * np.cos(rozw[i, 1]))
    tr.set_xdata(tx)
    tr.set_ydata(ty)


a = FuncAnimation(fig, anim, range(len(t)), interval=10, repeat=False)
ax.set_xlim([-240, 240])
ax.set_ylim([-180, 180])
plt.show()
