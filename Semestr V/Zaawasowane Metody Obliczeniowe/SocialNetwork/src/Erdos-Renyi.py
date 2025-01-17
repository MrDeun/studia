import random
import matplotlib.pyplot as plt
person_count = 100
network = []

connection_chance = 0.5


for _ in range(person_count):
  row = []
  for _ in range(person_count):
    row.append(0)
  network.append(row)

for i in range(len(network)):
  for j in range(len(network[i])):
    if(random.random() > connection_chance):
      network[i][j] = 1


print(network)

degrees = []
for i in range(len(network)):
  degree = 0
  for j in range(len(network[i])):
    if network[i][j] == 1:
      degree += 1
  degrees.append(degree)

print(degrees)
plt.hist(degrees,bins=100,range=(0,99))
plt.show()
