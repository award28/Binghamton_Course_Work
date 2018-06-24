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
   There are (m+1)(n+1) entries, thus total number of calls is at most 2(m+1)(n+1)+1, thus program3 is O(mn). 

CLASSES USED AND INTERACTIONS:
    Memoization, main3.cpp creates a class object.

PURPOSE OF CLASSES:
    Memoization, Used to evaluate LCS by the recursive top-down approach with memoization.
    
METHODS IN CLASSES:
    Memoization,     Constructor.
    lcs,        Purpose,    Calls execute and prints the required output.
                Paramters,  x,         A string containing the file name entered as argv[1].
                            y,         A string containing the file name entered as argv[2].
                            output,    A string containing the file name entered as argv[3].
                Variables,  subseq =  string, A Longest common subsequence.
                            fout   =  ofstream, The file to output data to.
                            begin  =  clock_t, Used to start recording the time of the algorithm.
                            end    =  clock_t, Used to end recording the time of the algorithm.
                            time   =  double, Calculates time difference between begin & end.
    execute,    Purpose,    Runs the top-down lcs recursive approach with memoization.
                Paramters,  x,         A string containing the file name entered as argv[1].
                            y,         A string containing the file name entered as argv[2].
                            curX,  int, The current index of string x.
                            curY,  int, The current index of string y.
                            lenX,  int, The length of string x.
                            lenY,  int, The length of string y.
                Variables,  N/A

GLOBAL VARIABLES:
    arr - int, A two dimensional array used for memoization in the execution method.

PERCENT COMPLETE:
    100% of the project is complete.

FILES:
    declaration.txt lcs.hpp lenLCS.cpp main1.cpp main2.cpp main3.cpp makefile memoization.cpp readme1.md readme2.md readme3.md topDownLCS.cpp 

TO RUN:
    Unzip the archive, then enter the following commands:

    make
    ./program3 <filex.txt> <filey.txt> <output3.txt> 
