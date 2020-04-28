import os
import cv2
import time
from PIL import Image
import numpy as np
import pickle



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
    time.sleep(2)
