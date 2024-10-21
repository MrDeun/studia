import numpy as np
import matplotlib.pyplot as plt
import csv

data = []

with open("net1.txt") as file:
  reader = csv.DictReader(file,delimiter="\t")
  for row in reader:
    print(row["demonenergy"])
