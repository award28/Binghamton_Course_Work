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
    The running time of program2 is O(2^n) for n >= m. In the case that two strings have no matches, the last line will be run with each recursive call.

CLASSES USED AND INTERACTIONS:
    TopDownLCS, main2.cpp creates a class object.

PURPOSE OF CLASSES:
    TopDownLCS, Used to evaluate LCS by the recursive top-down approach.
    
METHODS IN CLASSES:
    TopDownLCS,     Constructor.
    lcs,        Purpose,    Calls execute and prints the required output.
                Paramters,  x,         A string containing the file name entered as argv[1].
                            y,         A string containing the file name entered as argv[2].
                            output,    A string containing the file name entered as argv[3].
                Variables,  subseq =  string, A Longest common subsequence.
                            fout   =  ofstream, The file to output data to.
                            begin  =  clock_t, Used to start recording the time of the algorithm.
                            end    =  clock_t, Used to end recording the time of the algorithm.
                            time   =  double, Calculates time difference between begin & end.
    execute,    Purpose,    Runs the top-down lcs recursive approach.
                Paramters,  x,         A string containing the file name entered as argv[1].
                            y,         A string containing the file name entered as argv[2].
                            curX,  int, The current index of string x.
                            curY,  int, The current index of string y.
                            lenX,  int, The length of string x.
                            lenY,  int, The length of string y.
                Variables,  N/A

PERCENT COMPLETE:
    100% of the project is complete.

FILES:
    declaration.txt lcs.hpp lenLCS.cpp main1.cpp main2.cpp main3.cpp makefile memoization.cpp readme1.md readme2.md readme3.md topDownLCS.cpp 

TO RUN:
    Unzip the archive, then enter the following commands:

    make
    ./program2 <filex.txt> <filey.txt> <output2.txt> 
