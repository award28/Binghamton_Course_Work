CS375 Design & Analysis of Algorithms
Spring 2017
assignment1 README FILE

Due Date: 3/20/17
Submission Date: 3/20/17
Author:     Austin Ward
BU-ID:      award9
B-Number:   B00518794
email:      award9@binghamton.edu

DATA STRUCTURES:
   N/A

ANALYSIS OF COMPUTATION TIME:
    The running time of program1 is Θ(m×n) since each table entry takes Θ(1) time to compute.

CLASSES USED AND INTERACTIONS:
    LenLCS, main1.cpp creates a class object.

PURPOSE OF CLASSES:
    LenLCS, Used to evaluate LCS by the iterative bottom-up approach.
    
METHODS IN CLASSES:
    LenLCS,     Constructor.
    execute,    Purpose,    Runs the bottom-up lcs iterative approach and prints the required output.
                Paramters,  x,         A string containing the file name entered as argv[1].
                            y,         A string containing the file name entered as argv[2].
                            output,    A string containing the file name entered as argv[3].
                Variables,  lenx   =  int, The length of string x.
                            leny   =  int, The length of string y.
                            c      =  int, A two dimensional array to store matching letter number values.
                            b      =  char, A two dimensional array to store either left, up, or up left.
                            subseq =  string, A Longest common subsequence.
                            fout   =  ofstream, The file to output data to.
                            begin  =  clock_t, Used to start recording the time of the algorithm.
                            end    =  clock_t, Used to end recording the time of the algorithm.
                            time   =  double, Calculates time difference between begin & end.

PERCENT COMPLETE:
    100% of the project is complete.

FILES:
    declaration.txt lcs.hpp lenLCS.cpp main1.cpp main2.cpp main3.cpp makefile memoization.cpp readme1.md readme2.md readme3.md topDownLCS.cpp 

TO RUN:
    Unzip the archive, then enter the following commands:

    make
    ./program1 <filex.txt> <filey.txt> <output1.txt> 
