import numpy as np
import matplotlib.pyplot as plt

test_case = []
test_case_size = int(input())
for i in range(test_case_size):
  points_size = int(input())
  points = []
  for j in range(points_size):
    point = float(input())
    points.append(point)
  test_case.append(points)

for _case in test_case:
  x = np.array(range(len(_case)))
  y = np.array(_case)
  plt.scatter(x,y)
  plt.show()
  
  transformed_y = np.fft.fft(y)
  plt.scatter(x,abs(transformed_y))
  plt.show()
  
  for comp in range(len(transformed_y)):
    transformed_y[comp] /= len(transformed_y)
    if abs(transformed_y[comp]) > 1.5:
      transformed_y[comp] = 0.0 + 0.0j
      pass
#   plt.scatter(x,abs(transformed_y))
  trend_line = np.polyfit(x,np.fft.ifft(transformed_y),1)
  trend_function = np.poly1d(trend_line)
  plt.plot(x,trend_function(x))
  plt.scatter(x,np.fft.ifft(transformed_y))
  plt.show()
  