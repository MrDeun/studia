import numpy as np
import matplotlib.pyplot as plt
X = np.array([[2, 1], [2, 2], [0, 6], [-2, 10], [-2, 0],[0,0], [4, -20]])
y = np.array([1, 1, 1, 1, -1,-1, -1])


weights = np.zeros(2)
bias = 0

for i in range(len(X)):
    activation = np.dot(weights, X[i]) + bias
    predicted = 1 if activation >= 0 else -1
    if predicted != y[i]:
        for j in range(len(weights)):
            weights += y[i] * X[i]

def equation(weights, bias):
    print(f"Decision boundary equation: x2 = {-weights[0]/weights[1]}*x1 + {bias/weights[1]}")
    for x,y in X:
        plt.scatter(x,y)
    plt.show()

equation(weights, bias)
