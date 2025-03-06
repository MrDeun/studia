import tensorflow as tf
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import random

data = pd.read_csv('dane_1.csv')
data_2 = np.array(data.iloc[:,1:])

real_x = data_2[:,0]
real_y = data_2[:,1]

def loss_fn(real_y, pred_y):
    return tf.reduce_mean((real_y - pred_y)**2)

lossed = []

for epochs_, lr in zip(epochs,learning_rate):

  Loss = []
  a = tf.Variable(random.random())
  b = tf.Variable(random.random())

  for _ in range(epochs_):
    with tf.GradientTape() as tape:
      pred_y = a * real_x + b
      loss = loss_fn(real_y, pred_y)
      # print(loss.numpy())
      Loss.append(loss.numpy())

      dloss_da, dloss_db = tape.gradient(loss,(a, b))

      a.assign_sub(lr*dloss_da)  # a = a - learning_rate*dloss_da
      b.assign_sub(lr*dloss_db)  # b = b - learning_rate*dloss_db
  print("y = {}x + {}".format(a.numpy(),b.numpy()))
  lossed.append(Loss)

for loss in lossed:
  plt.scatter(np.arange(len(loss)),loss)
  plt.show()