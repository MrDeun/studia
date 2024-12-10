import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import sys
dataframe = pd.read_csv(sys.argv[1])

x = dataframe['x'].to_numpy()
pos_x = range(len(x))
com = dataframe['y'].to_numpy()
y = []
for i in range(len(com)):
  y.append(x[i]+com[i]*1.0j)
y = np.array(y)
print(y)
z = np.polyfit(pos_x,abs(y),1)
func = np.poly1d(z)
print(z)
# plt.plot(pos_x,func(x))
plt.subplot(2,1,1)
plt.scatter(pos_x,abs(y))
plt.subplot(2,1,2)
plt.plot(pos_x,abs(y))
plt.tight_layout()
plt.savefig("keh.jpg")
plt.show()