import matplotlib.pyplot as plt
import numpy as np

test_cases = int(input())

size_line = input()
x, y = size_line.split()
x = int(x)
y = int(y)
print(x,y)
mat = []
for i in range(y):
    line = input()
    mat_line = []
    split_lines = line.split()
    for val in split_lines:
        mat_line.append(float(val))
    mat.append(mat_line)
np_mat = np.array(mat)
print(np_mat)

plt.imshow(np_mat,interpolation='none')
plt.savefig("pre_Transform.jpg")
plt.show()
transformed = abs(np.fft.fft2(np_mat))
plt.imshow(transformed,interpolation='none')
plt.savefig("post_Transform.jpg")
plt.show()
