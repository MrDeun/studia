import matplotlib.pyplot as plt
import cv2
import numpy as np


def show(title:str,val):
  cv2.imshow(title,val)
  cv2.waitKey(0)
  cv2.destroyAllWindows()
  pass

img = cv2.imread("./chicken4.jpg")
img_2 = cv2.cvtColor(img,cv2.COLOR_BGR2HSV)
print(img.shape)
#cv2.imshow("kurczak",img)
# show("kurczak",new_red)
# show("kurczak",green)
# show("kurczak",blue)
show("kurczak",img)

hue = img_2[:,:,0]
sat = img_2[:,:,1]
val = img_2[:,:,2]

show("hue",hue)
show("sat",sat)
show("val",val)

plt.plot(np.histogram(hue,bins=256,range=(0,255))[0],label="hue")
plt.plot(np.histogram(sat,bins=256,range=(0,255))[0],label="sat")
plt.plot(np.histogram(val,bins=256,range=(0,255))[0],label="val")
img_2[:,:,1] = sat
img_3 = cv2.cvtColor(img_2,cv2.COLOR_HSV2BGR)
show("after",img_3)
plt.legend()
plt.show()