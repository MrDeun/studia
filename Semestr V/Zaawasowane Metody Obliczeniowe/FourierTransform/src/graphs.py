import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

points = pd.read_csv('result.csv')

plt.scatter(points['real'],points['imag'])
plt.show()
  