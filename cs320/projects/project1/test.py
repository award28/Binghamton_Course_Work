import os

tracesDir = input("What is the path to the traces directory?\nEnter here: ")
correctDir = input("What is the path to the correct output directory?\nEnter here: ")
os.system("make");

for i in range(1, 4):
    print("Running short test " + str(i) + "...")
    os.system("./predictors " + tracesDir + "short_trace" + str(i) + ".txt sout" +str(i) +".txt")
    os.system("diff  " + correctDir + "short_trace" + str(i) + "-output.txt sout" + str(i) + ".txt")
    print("Short test " + str(i) + " complete")
    os.system("rm sout" + str(i) + ".txt")

    print("Running long test " + str(i) + "...")
    os.system("./predictors " + tracesDir + "long_trace" + str(i) + ".txt lout" +str(i) +".txt")
    os.system("diff " + correctDir + "long_trace" + str(i) + "-output.txt lout" + str(i) + ".txt")
    print("Long test " + str(i) + " complete")
    os.system("rm lout" + str(i) + ".txt")

os.system("make clean");

