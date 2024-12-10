import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import sys
dataframe = pd.read_csv(sys.argv[1])

y = dataframe['x'].to_numpy()
x = range(len(y))
z = np.polyfit(x,y,1)
func = np.poly1d(z)
print(z)
plt.plot(x,func(x))
plt.scatter(x,y)
plt.show()