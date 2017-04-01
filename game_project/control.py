import subprocess
import os
import time
import random
from subprocess import Popen, PIPE
from random import randint

executable = os.path.join("/home/sheun/game_project", 'my_script')
up= ["Up", ""]
down= ["Down", ""]
right= ["Right", ""]
left= ["Left", ""]
Select_attack= ['1', '2', '3', '4']
Press_space= ["space", ""]
R_click= ["R", ""]
Mouse_x=0
Mouse_y=0
mouse_clickL=["ClickMouseL2", ""]
mouse_clickR=["ClickMouseR2", ""]
#a = (subprocess.call(["xdotool", "getactivewindow", "getwindowname"]))
b ='Transistor'
#p = subprocess.Popen([executable, "Move", up[0], down[0], right[0], left[0], Select_attack[0], Press_space[0], Mouse_x, Mouse_y, mouse_click [0]])

#p = subprocess.Popen([executable, "Move", random.choice (up), random.choice (down), random.choice (right), random.choice (left), random.choice (Select_attack), random.choice (Press_space), str(randint(0,1400)), str(randint(0,1400)), random.choice (mouse_click)])

while True:
    a = (subprocess.check_output(["xdotool", "getactivewindow", "getwindowname"]).decode("utf-8").strip())
    #print (a == b)
    while a == b:
        p = subprocess.Popen(
             [executable, "Move", random.choice(up), random.choice(down), random.choice(left), random.choice(right),
              random.choice(Select_attack), random.choice(Press_space), str(randint(0, 1400)), str(randint(0, 1400)),
              random.choice(R_click),random.choice(mouse_clickL),random.choice(mouse_clickR)])
        # p = subprocess.Popen(
        #          [executable, "Move", random.choice(up), random.choice(down), random.choice(right), random.choice(left),
        #           "", "", "", "",
        #           "","",""])
        time.sleep( 1 )
        a = (subprocess.check_output(["xdotool", "getactivewindow", "getwindowname"]).decode("utf-8").strip())


#raw_input("Press Enter to continue...")
