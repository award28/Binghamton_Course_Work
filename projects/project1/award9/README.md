
CS320 Computer Systems III 
Spring 2017
project1 README FILE

Due Date: 3/12/17
Submission Date: 3/12/17
Author:     Austin Ward
BU-ID:      award9
B-Number:   B00518794
email:      award9@binghamton.edu

PURPOSE:
    Gain a clear understanding of different branch prediction implementations. 

PERCENT COMPLETE:
    100% of the project is complete.

FILES:
    README.md test.py makefile predictors.hpp main.cpp saturatingBimodal.cpp gShare.cpp notTaken.cpp singleBimodal.cpp tournament.cpp taken.cpp

TO RUN:
    Unzip the archive, then enter the following commands:

    make
    ./predictors <input-file> <output-file>

TEST:
    To test the code with the python script, you need to have python 3 installed. Then, run `python3 test.py`.
    The program will ask you for the traces directory path, and the correct output path. 
    Once this has been entered, the program will: 
        1. Run make
        2. Create the output files from the traces
        3. Compare the two files
        4. Delete the created files
        5. Run make clean

    If there is no diff output, the run was successful. 

FOUND INTERESTING:
    Previously, I had not used bit manipulation in a programming project. Considering that was essential for this project, I studied up on bitwise operators and learned quite a few interesting techniques.
