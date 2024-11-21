import json
import numpy as np

with open("cmatrix.json",'r') as json_data:
  data = json.load(json_data)

precisions = []
recalls = []
f1s = []

arr = np.array(data['array'])
print(arr.reshape(10,10))
for i in range(10):
  TP = arr[i][i]
  FP = np.sum(arr[i,:]) - TP
  FN = np.sum(arr[:,i]) - TP
  precision = TP/(TP+FP)
  precisions.append(precision)
  
  recall = TP/(TP+FN)
  recalls.append(recall)

  f1 = 2*TP/(2*TP+FP+FN)
  f1s.append(f1)

  print(f"Precision: {precision}\tRecall: {recall}\tF1: {f1}")
averagePrecision = np.sum(precisions)/len(precisions)
averageRecall = np.sum(recalls)/len(recalls)
averageF1 = np.sum(f1s)/len(f1s)
print(f"Average precision: {averagePrecision}\tAverage recall: {averageRecall}\tF1: {averageF1}")
