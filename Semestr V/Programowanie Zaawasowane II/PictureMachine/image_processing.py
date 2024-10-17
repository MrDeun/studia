from hmac import new
import matplotlib.pyplot as plt
import cv2
import numpy as np


def show(title:str,val):
  cv2.imshow(title,val)
  cv2.waitKey(0)
  cv2.destroyAllWindows()
  pass

img = cv2.imread("./chicken4.jpg")
print(img.shape)
#cv2.imshow("kurczak",img)
blue = img[:,:,0]
green = img[:,:,1]
red = img[:,:,2]

new_red = red.copy()
new_green = green.copy()
new_blue = blue.copy()

new_red[new_red<150] = 0
new_green[new_green<170] = 0
new_blue[new_blue<130] = 0

print(red)
# show("kurczak",new_red)
# show("kurczak",green)
# show("kurczak",blue)
show("kurczak",img)
img[:,:,2] = new_red
img[:,:,1] = new_green
img[:,:,0] = new_blue
show("kurczak",img)
plt.plot(np.histogram(blue,bins=256,range=(0,255))[0],label="blue")
plt.plot(np.histogram(red,bins=256,range=(0,255))[0],label="red")
plt.plot(np.histogram(green,bins=256, range=(0,255))[0],label="green")
plt.legend()
plt.show()