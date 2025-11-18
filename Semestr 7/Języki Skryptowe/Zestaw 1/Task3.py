import matplotlib.pyplot as plt
import numpy as np

X = np.linspace(-2.0 * np.pi, 2.0 * np.pi, 1001)
Y = np.copy(X)

dY = np.copy(Y)
for n in range(2, 9):
    dY *= -X**2 / ((2 * n - 2) * (2 * n - 1))
    Y += dY
    Y1 = np.copy(Y)
    Y[np.logical_or(Y <= -1.5, Y >= 1.5)] = np.nan
    plt.plot(X, Y1, color=((n - 1) / 8, 0, 1 - (n - 1) / 8), linewidth=2)

Y1 = np.copy(Y)
Y[np.logical_or(Y <= -1.5, Y >= 1.5)] = np.nan
plt.plot(X, Y1, color=(0, 0, 1), linewidth=2)
plt.show()
