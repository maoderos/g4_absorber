import math


angles = [2.5,3.0,4.0,5.0,7.0,9.0]

for angle in angles:
    file = open("run_{0}deg.sh".format(angle),'w')
    file.write("#!/bin/bash\n")
    file.write("mkdir results;\n")
    file.write("./absorber ../macros/events{0}.in;\n".format(angle))
    file.close()
