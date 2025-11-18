import matplotlib.pyplot as plt
import numpy as np


def koch(args):
    pp, pk = args
    r = ((pk[0] - pp[0]) / 3, (pk[1] - pp[1]) / 3)
    p1 = (pp[0] + r[0], pp[1] + r[1])
    p2 = (
        pp[0] + r[0] + (r[0] - np.sqrt(3) * r[1]) / 2,
        pp[1] + r[1] + (np.sqrt(3) * r[0] + r[1]) / 2,
    )
    p3 = (pp[0] + 2 * r[0], pp[1] + 2 * r[1])
    return [p1, p2, p3, pk]


l = [(0.0, 0.0), (1.0, 0.0), (0.5, -np.sqrt(3) / 2), (0.0, 0.0)]
for n in range(6):
    X, Y = zip(*l)
    plt.plot(X, Y)
    plt.axis("equal")
    plt.show()
    l = [l[0]] + sum(map(koch, zip(l[:-1], l[1:])), [])


