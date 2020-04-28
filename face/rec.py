import cv2
import numpy as np
import pickle
from firebase import firebase
import os
os.chdir('C:\my files\TRC\team 12 induction\face')
firebase = firebase.FirebaseApplication("https://shoe-16ee2.firebaseio.com/")
face_cas = cv2.CascadeClassifier('haarcascadeFiles\haarcascade_frontalface_default.xml')
recognizer = cv2.face.LBPHFaceRecognizer_create()
recognizer.read("trainner.yml")
lables = {}
with open("lables.pickle", 'rb') as f:
    lables = pickle.load(f)
    lables = {v:k for k,v in lables.items()}

currentName = ''
name = "no"
rack = {1:'',2:'',3:''}

cap = cv2.VideoCapture(0)
while(1):
    ret,frame = cap.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_cas.detectMultiScale(gray,1.3,5)
    for (x,y,w,h) in faces:
        roi_gray = gray[y:y+h, x:x+w]
        roi_color = frame[y:y+h, x:x+w]
        cv2.rectangle(frame, (x,y), (x+w,y+h), (255,255,0),2)
        id_,conf = recognizer.predict(roi_gray)
        if(conf>=70 and conf<=95):
            #print(lables[id_])
            font = cv2.FONT_HERSHEY_DUPLEX
            name = lables[id_]
            cv2.putText(frame, name,(x,y), font, 1, (0,0,255), 2 )
        else:
            print("else")
            saved_image = "images/new/s.jpg"
            cv2.imwrite(saved_image, roi_gray)


            if(currentName != name):
                currentName=name
                for x,y in rack.items():
                    if name == y:
                        person = firebase.put('/','person',x)
                else:
                    if rack[1]=="":
                        person = firebase.put('/','person',1)
                    elif rack[2]=="":
                        person = firebase.put('/','person',2)
                    elif rack[3]=="":
                        person = firebase.put('/','person',3)






    cv2.imshow('vdo', frame)
    if(cv2.waitKey(1) == ord('q')):
        break

cap.release()
cv2.destroyAllWindows()
