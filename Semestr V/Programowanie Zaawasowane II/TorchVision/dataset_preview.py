import os
from datetime import datetime
from sklearn import svm
from sklearn.metrics import confusion_matrix
import json
import pickle
import seaborn as sb
import torch
import torchvision
import numpy as np
import matplotlib.pyplot as plt


#pip install torch, torchvision
base_path = "./"
train_loader = torch.utils.data.DataLoader(
    torchvision.datasets.MNIST(base_path+'datasets/', train=True, download=True,
        transform=torchvision.transforms.Compose([
                               torchvision.transforms.ToTensor(),
                               ])),
    batch_size=6000, shuffle=True)

test_loader = torch.utils.data.DataLoader(
    torchvision.datasets.MNIST(base_path+'datasets/', train=False, download=True,
                             transform=torchvision.transforms.Compose([
                               torchvision.transforms.ToTensor(),
                               ])),
    batch_size = 1000, shuffle=True)
#Traing SVM\


train_set = enumerate(train_loader)
batch_idx, (train_data, train_targets) = next(train_set)
train_data = train_data.reshape((6000,-1))
print(train_data.shape)
kernel = 'rbf' #linear, poly, sigmoid
svm_file_path = base_path+'out/svm-model-{}.pkl'.format(kernel)

# Check if the file exists
if os.path.exists(svm_file_path):
    with open(svm_file_path, 'rb') as f:
        clf = pickle.load(f)
        print("Loaded model from file")
else:
    # start = datetime.now()
    # print("Start training:", start)
    # clf = svm.SVC(kernel=kernel)
    # clf.fit(train_data, train_targets)
    # end = datetime.now()
    # print("End training:", end)
    # print("Training time:",end-start)
    # # save svm as pickle
    # with open(svm_file_path, 'wb') as f:
    #     pickle.dump(clf, f)
    # print("Saved model")
    # training_meta = {'method':'svm',
    #                  'kernel':kernel,
    #                  'file':os.path.basename(svm_file_path),
    #                  'start':str(start),
    #                  'end':str(end),
    #                  'dataset':'mnist',
    #                  'duration':str(end-start)}
    # with open(base_path + 'out/svm-train-metadata.json', 'r') as f:
    #     _json = json.load(f)
    # _json['models'].append(training_meta)
    # with open(base_path+'out/svm-train-metadata.json', 'w') as f:
    #     json.dump(_json, f, indent=4)
    pass


examples = enumerate(test_loader)
batch_idx, (example_data, example_targets) = next(examples)
#print(example_data[0][0])
print(example_data[0].shape)
print(example_targets[0].shape)

pred = clf.predict(example_data.reshape((1000,-1)))

fig = plt.figure()
for i in range(8):
      plt.subplot(2, 4, i + 1)
      #plt.tight_layout()
      plt.imshow(example_data[i][0], cmap='gray')

      plt.title("P: {}, E: {} ".format(pred[i],example_targets[i]))
      plt.xticks([])
      plt.yticks([])
fig.show()
fig.waitforbuttonpress()


cmatrix= confusion_matrix(example_targets,pred)
json_data = {"array":cmatrix.tolist()}
with open("cmatrix.json",'w') as json_file:
    json.dump(json_data,json_file)
fig = plt.figure()
sb.heatmap(cmatrix,annot =True, fmt='g')
plt.xlabel('Actual')
plt.ylabel('Predicted')
plt.title('SVM MNIST Confusion Matrix')
fig.show()
fig.waitforbuttonpress()

print("Accuracy:", np.trace(cmatrix)/np.sum(cmatrix))