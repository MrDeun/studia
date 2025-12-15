# 𝑥 = (100 + 60𝑐𝑜𝑠𝛽)𝑐𝑜𝑠𝛼
# 𝑦 = (100 + 60𝑐𝑜𝑠𝛽)𝑠𝑖𝑛𝛼
# 𝑧 = 60𝑠𝑖𝑛𝛽
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


def x(alpha, beta):
    return (100 + 60 * np.cos(alpha/2)*t) * np.cos(alpha)


def y(alpha, beta):
    return (100 + 60 * np.cos(alpha/2)*beta) * np.sin(alpha)


def z(alpha, beta):
    return 60 * np.sin(alpha/2)*beta


if __name__ == "__main__":
    alpha,t=np.meshgrid(np.linspace(0,6.28,51),np.linspace(-1,1,51))


    X = x(alpha, t)
    Y = y(alpha, t)
    Z = z(alpha, t)

    
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
