import os

x = "filex.txt" 
y = "filey.txt"
out = "out.txt"

os.system("make");

for i in range(1, 4):
    print("Running program" + str(i) + "...")
    os.system("./program" + str(i) + " " + x + " " + y + " " + out + " && cat " + out)
    print("\nprogram" + str(i) + " complete")
    
os.system("rm " + out)

os.system("make clean");

