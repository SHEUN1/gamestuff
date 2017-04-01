import time
import numpy as np
import cv2


def timetest():
    image = "/home/sheun/Pictures/transistor/Transistor3.jpg"
    t0 = time.time()
    from cv2.cv import LoadImage
    img = LoadImage(image)
    t1 = time.time()
    from opencvtest import load3
    img2 = load3(image)
    t2 = time.time()
    print "Time taken to load image using cv2.cv module:",
    print t1 - t0
    print "Time taken to load image using boost wrapper:",
    print t2 - t1


timetest()