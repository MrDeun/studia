import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import scipy as sp
graph_x = []
graph_y = []

data = pd.read_csv('demon.csv')
simulation_counts = int((data.shape[1] - 1) / 2)
for i in range(simulation_counts):
  bucket_column = f'bucket{i}'
  magnetism_column = f'magnetism{i}'
  # buckets_values = data[ bucket_column]
  # magnetisms_values = data[ magnetism_column]
  value_counts = data[bucket_column].value_counts()
  top_20 = value_counts.nlargest(20).index
  filtered_data = data[data[bucket_column].isin(top_20)]
  iterator_table = range(1, 21)
    # print(filtered_data)
    # plt.hist(filtered_data[bucket_column], bins=len(
     #data[bucket_column]/4), align = 'mid')
          # plt.title(f'Bucket values for Simulation no. {i+1}')
          # plt.xlabel('value')
            # plt.yscale('log')
            # plt.ylabel('frequency')
            # plt.show()
            # plt.savefig(f'{bucket_column}.png')
            # plt.clf()

  buckets_vals = data[bucket_column]
  x = np.array(iterator_table)
  y = np.array(buckets_vals[:20])
  popt, popc = sp.optimize.curve_fit(lambda t, a, b: a*np.exp(b*t), x, y)
  print(-1/popt[0])
  print(popc)
  graph_x.append(-1/popt[0])

  plt.scatter(
  list(range(len(data[magnetism_column]))), data[magnetism_column])
  plt.title(f'Magnetism values for Simualtion no.{i+1}')
  plt.xlabel('iteration')
  plt.ylabel('magnetism')
  plt.savefig(f'{magnetism_column}.png')
  plt.clf()
  # plt.show()
  magnetism_arr = data[magnetism_column]
  avg = np.average(magnetism_arr[2000:])
  print(avg)
  graph_y.append(avg)
  pass

plt.scatter(graph_x, graph_y)
plt.title('Magnetims from tempeture')
plt.xlabel('temp')
plt.ylabel('magnet')
# plt.show()
plt.savefig('temp_magnet.png')
plt.clf()
