# 𝑥 = (100 + 60𝑐𝑜𝑠𝛽)𝑐𝑜𝑠𝛼
# 𝑦 = (100 + 60𝑐𝑜𝑠𝛽)𝑠𝑖𝑛𝛼
# 𝑧 = 60𝑠𝑖𝑛𝛽
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


def x(alpha, beta):
    return (100 + 60 * np.cos(beta)) * np.cos(alpha)


def y(alpha, beta):
    return (100 + 60 * np.cos(beta)) * np.sin(alpha)


def z(alpha, beta):
    return 60 * np.sin(beta)


if __name__ == "__main__":
    base = np.linspace(0, 2 * np.pi, 51)

    alpha, beta = np.meshgrid(base, base)

    X = x(alpha, beta)
    Y = y(alpha, beta)
    Z = z(alpha, beta)

    
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')  # Modern approach

# Remove the stray "2" that was here
    surf = ax.plot_surface(X, Y, Z, rstride=1, cstride=1, linewidth=0, alpha=0.8, cmap='viridis')

# Use set_xlim, set_ylim, set_zlim instead of auto_scale_xyz (deprecated)
    ax.set_xlim([-160, 160])
    ax.set_ylim([-160, 160])
    ax.set_zlim([-120, 120])

# Optional: Add labels
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')

    plt.show()
