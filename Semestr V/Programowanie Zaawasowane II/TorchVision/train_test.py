import torch
import torchvision
import matplotlib.pyplot as plt
from sklearn import svm

base_path = '.'

train_loader = torch.utils.data.DataLoader(
    torchvision.datasets.MNIST(base_path+'/datasets/', train=False, download=True,
                             transform=torchvision.transforms.Compose([
                               torchvision.transforms.ToTensor()
                             ])),
    batch_size=60000, shuffle=True, )

test_loader = torch.utils.data.DataLoader(
    torchvision.datasets.MNIST(base_path+'/datasets/', train=False, download=True,
                             transform=torchvision.transforms.Compose([
                               torchvision.transforms.ToTensor()
                             ])),
    batch_size=10, shuffle=True, )

train_set = enumerate(train_loader)
batch_idx, (train_data,train_targets) = next(train_set)
clf = svm.SVC()
clf.fit(train_data,train_targets)
fig = plt.figure()


