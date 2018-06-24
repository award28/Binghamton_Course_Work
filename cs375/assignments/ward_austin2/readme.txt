CS375 Design & Analysis of Algorithms
Spring 2017
assignment2 README FILE

Due Date: 4/19/17
Submission Date: 4/19/17
Author:     Austin Ward
BU-ID:      award9
B-Number:   B00518794
email:      award9@binghamton.edu

DATA STRUCTURES:
   Binary Tree

ANALYSIS OF COMPUTATION TIME:
    The running time of program1 is O(2^n) since the worst case creates 2^n nodes, each of which takes Θ(1) time to compute.

CLASSES USED AND INTERACTIONS:
    Knapsack, main.cpp creates a class object.

PURPOSE OF CLASSES:
    Knapsack, Used to evaluate Knapsack by the best first search branch and bounds approach.
    
METHODS IN CLASSES:
    Knapsack,   Constructor.
    kwf,        Purpose,    Executes Knapsack with Fractions algorithm.
                Paramters,  N/A.
                Variables,  itemFrac    =   int, Array of profit/weight per item.
                            temp        =   std::pair<int, int>, temporary value for switching typedef item.
                            weight      =   int, Current weight.
    execute,    Purpose,    Executes the best first search branch and bounds algorithm.
                Paramters,  index,     An int of the current index.
                            profit,    An int of the current profit.
                            weight,    An int of the current weight.
                Variables,  N/A
    promising,  Purpose,    Checks if a branch is promising.
                Paramters,  index,     An int of the current index.
                            profit,    An int of the current profit.
                            weight,    An int of the current weight.
                Variables, N/A 
    kwfAux,     Purpose,    An auxilary KFW algorithm.
                Paramters,  index,     An int of the current index.
                            profit,    An int of the current profit.
                            weight,    An int of the current weight.
                Variables,  itemFrac    =   int, Array of profit/weight per item.
                            bound       =   int, Set to the current profit of that branch.
    print,      Purpose,    Print the results.
                Paramters,  outfile,     A string for the output data file. 
                Variables,  fout    =    ofstream, Outfile to print data to.
PERCENT COMPLETE:
    90% of the project is complete.

FILES:
    declaration.txt knapsack.cpp knapsack.hpp main.cpp makefile readme.txt 

TO RUN:
    Unzip the archive, then enter the following commands:

    make
    ./BestFirstSearch <input.txt> <output.txt> 
