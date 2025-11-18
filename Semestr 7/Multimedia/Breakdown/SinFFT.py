import numpy as np
import matplotlib.pyplot as plt

N = int(input("Harmonics: "))
M = int(input("Points: "))
A = int(input("Amplitude: "))
P = int(input("Zoom: "))

points = np.zeros(M)

for i in range(N):
    if i==0:
        continue
    Ak = (A * 4) / (np.pi * i)
    for j in range(M):
        points[j] = points[j] + Ak * np.sin(2 * np.pi * i * j / M)

t = range(M)
plt.subplot(2, 1, 1)
plt.plot(t, points)
plt.grid()

y = np.fft.fft(points, M)
yy = np.sqrt(y * np.conjugate(y)) / (M / 2)
yy = yy[:len(yy)//2]
plt.subplot(2,1,2)
plt.bar(t[:len(t)//2],yy)
plt.grid()

plt.show()
