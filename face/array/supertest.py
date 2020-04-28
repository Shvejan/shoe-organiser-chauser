import cv2
import numpy as np
import os
import time
os.chdir(r"C:\my files\TRC\team 12 induction\face\array\db")
arr = []
cap = cv2.VideoCapture(0)
f_c = 0
while(1):
    ret,frame = cap.read()
    if (f_c%20 == 0) :
            arr.append(frame)
    elif len(arr)>=4:
        break

    cv2.imshow('vdo', frame)
    if(cv2.waitKey(1) == ord('q')):
        break
    f_c+=1


cap.release()
cv2.destroyAllWindows()
print(len(arr))
for i in range(len(arr)):
    name = "" + str(i)+'.jpg'
    cv2.imwrite(name,arr[i])
