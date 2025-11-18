import random
import numpy as np
import matplotlib.pyplot as plt
time_max = 200
def random_step():
    step = 1 if (random.random() > 0.5) else -1
    return step

def generation():
    position = 0
    history = []
    for _ in range(time_max):
        position += random_step()
        history.append(position)
    return history

end_val = 0
for i in range (10):
    history = generation()
    plt.plot(history)
plt.show()

