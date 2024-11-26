import matplotlib.pyplot as plt
import numpy as np
import math

y_s = []
x_s = []

with open('dane_07.in','r') as file:
  while True:
    line = file.readline()
    if not line:
      break
    y_s.append(float(line))
y_s = y_s[2:]
x_s = range(len(y_s))
arr_x = np.array(x_s)
arr_y = np.array(y_s) 
for i in arr_x:
  i = i*2*math.pi/len(y_s)
print(arr_x)
print(arr_y)

plt.scatter(arr_x,arr_y)
plt.show()
    


