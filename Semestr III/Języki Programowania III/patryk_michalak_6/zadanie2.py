import pandas as panda
import numpy as np

dataset = panda.read_csv("./iris_dataset.csv")

choice = input("Choose the column you want to check: ")
selected_column = dataset[choice]

minimum = float(input ("Choose value that's gonna be a minimal (in cm): "))
maximum = float(input("Choose value that's gonna be a maximum (in cm): "))
filtered_data = dataset[(dataset[choice]>= minimum) & (dataset[choice] <= maximum)]

print(filtered_data[[choice,'target']])
print(filtered_data[choice].max())

feature_name = input("Choose the column you want to scale: ")
new_min = float(input("Input new minimal value: "))
new_max = float(input("Input new maximum value: "))
dataset[feature_name] = np.interp(dataset[feature_name], (dataset[feature_name].min(), dataset[feature_name].max()), (new_min, new_max))
print(dataset[feature_name])  