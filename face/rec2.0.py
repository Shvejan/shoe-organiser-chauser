import cv2
import numpy as np
import pickle
from firebase import firebase
import webbrowser
import os
from copy import copy
import time
from PIL import Image

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
pname = 1




def train():
    if(1==1):
        base_dir = os.path.dirname(os.path.abspath(__file__))
        image_dir = os.path.join(base_dir, "images")

        tface_cas = cv2.CascadeClassifier('haarcascadeFiles\haarcascade_frontalface_default.xml')

        trecognizer = cv2.face.LBPHFaceRecognizer_create()


        x_train = []
        y_lables = []
        current_id = 0
        lable_ids = {}
        for root, dirs, files in os.walk(image_dir):
            for file in files:
                if file.endswith("png") or file.endswith("jpg"):
                    path = os.path.join(root, file)
                    lable = os.path.basename(root).replace(" ", "-").lower()
                    if not lable in lable_ids:
                        lable_ids[lable]= current_id
                        current_id +=1
                    id_ = lable_ids[lable]
                    #print(lable_ids)


                    pil_image = Image.open(path).convert("L")
                    image_array = np.array(pil_image, "uint8")
                    #print(image_array)
                    faces = tface_cas.detectMultiScale(image_array,1.5,5)
                    for (x,y,w,h) in faces:
                        roi = image_array[y:y+h, x:x+w]
                        x_train.append(roi)
                        y_lables.append(id_)

        with open("lables.pickle", 'wb') as f:
            pickle.dump(lable_ids, f)

        trecognizer.train(x_train, np.array(y_lables))
        trecognizer.save("trainner.yml")
        print('sleeping')
        recognizer.read("trainner.yml")
        with open("lables.pickle", 'rb') as f:
            lables = pickle.load(f)
            lables = {v:k for k,v in lables.items()}
        #time.sleep(2)
















train()

cap = cv2.VideoCapture(0)
while(1):
    ret,frame = cap.read()
    frame_copy = copy(frame)
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_cas.detectMultiScale(gray,1.3,5)
    for (x,y,w,h) in faces:
        roi_gray = gray[y:y+h, x:x+w]
        roi_color = frame[y:y+h, x:x+w]
        cv2.rectangle(frame, (x,y), (x+w,y+h), (255,255,0),2)
        id_,conf = recognizer.predict(roi_gray)
        if(conf>=50 and conf<=85):
            #print(lables[id_])
            font = cv2.FONT_HERSHEY_DUPLEX
            name = lables[id_]
            cv2.putText(frame, name,(x,y), font, 1, (0,0,255), 2 )
        else:
            try:
                print("else")
                path = "images/id" + str(pname)
                os.mkdir(path)
                imgpath = path+'/s.jpg'
                cv2.imwrite(imgpath, frame_copy)
                pname+=1

                if(currentName != name):
                    currentName=name
                    for x,y in rack.items():
                        if name == y:
                            if(x==1):
                                #webbrowser.open('192.168.4.1/one?')
                                print(1)
                            elif(x==2):
                                #webbrowser.open('192.168.4.1/two?')
                                print(2)
                            elif(x==3):
                                #webbrowser.open('192.168.4.1/three?')
                                print(3)
                    else:
                        if rack[1]=="":
                            #webbrowser.open('192.168.4.1/one?')
                            print(1)
                        elif rack[2]=="":
                            #webbrowser.open('192.168.4.1/two?')
                            print(2)
                        elif rack[3]=="":
                            #webbrowser.open('192.168.4.1/three?')
                            print(3)
            except:
                pass
            train()







    cv2.imshow('vdo', frame)
    if(cv2.waitKey(1) == ord('q')):
        break

cap.release()
cv2.destroyAllWindows()
