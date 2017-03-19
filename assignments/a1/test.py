import os

x = input("File x?\nEnter here: ")
y = input("File y?\nEnter here: ")
out = input("Out file?\nEnter here: ")

os.system("make");

for i in range(1, 4):
    print("Running program" + str(i) + "...")
    os.system("./program" + str(i) + " " + x + " " + y + " " + out + " && cat " + out)
    print("program" + str(i) + " complete")
    
os.system("rm " + out)

os.system("make clean");

