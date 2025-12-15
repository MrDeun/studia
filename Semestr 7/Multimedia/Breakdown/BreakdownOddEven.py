import numpy as np
import matplotlib.pyplot as plt
size = 10
init_signal = np.random.randint(-5,5,size=size)

even_signal = np.zeros(size)
odd_signal = np.zeros(size)

for i in range(size):
    even_signal[i] = (init_signal[i] + init_signal[size-i-1])/2
    odd_signal[i] = (init_signal[i] - init_signal[size-i-1])/2
plt.plot(init_signal,color=(0.0,0.0,0.0))
plt.plot(even_signal,color=(1.0,0.0,0.0))
plt.plot(odd_signal,color=(0.0,1.0,0.0))

print(f"Initial signal: {init_signal}")
print(f"Even signal: {even_signal}")
print(f"Odd signal: {odd_signal}")
print(f"Summed signal: {(even_signal + odd_signal) - init_signal}")
plt.show()


