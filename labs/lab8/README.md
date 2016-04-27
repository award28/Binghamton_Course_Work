
CS240 Data Structures and Algorithms
Spring 2016
lab6 README FILE

Due Date: 4/06/16
Submission Date: 4/10/16
Author(s): Austin Ward
e-mail(s): award9@binghamton.edu

PURPOSE:
Describe the purpose of the software as described by the software requirements in your own words
   Implement a binary search tree. 

PERCENT COMPLETE:
How much of the project you believe you have completed
    75% of the project.

PARTS THAT ARE NOT COMPLETE:
What parts of the project you were not able to complete
    I couldn't get test 7,8 and 10 to fully work.
BUGS:
Known bugs

FILES:
A list of files included in the jar archive, including this README
     BSTree.hpp, BSTree.cpp, lab7.cpp, makefile, README.md

SAMPLE OUTPUT:
A sample of the output from your program copy and pasted from the terminal
	TEST #0: Passes all tests from Lab 6

	========================PASS========================


	TEST #1: Cannot remove node that is not in the tree
 [1]  [2]  [3]  [4]  [5]  [6]  [7]  [8]  [9]  [10]  [11]  [12]  [13]

	========================PASS========================


	TEST #2: Remove a leaf node
 [2]  [3]  [4]  [5]  [6]  [7]  [8]  [9]  [10]  [11]  [12]  [13]

	========================PASS========================


	TEST #3: Remove single branch using the Short Circuit algorithm
 [2]  [3]  [4]  [5]  [6]  [8]  [9]  [10]  [11]  [12]  [13]

	========================PASS========================

Test #4: Remove two branch node promoting a leaf node
 [2]  [3]  [4]  [5]  [6]  [8]  [9]  [11]  [12]  [13]

	========================PASS========================


	TEST #5: Remove two branch node promoting a 1 branch node using Short Circuit
 [2]  [3]  [4]  [5]  [6]  [8]  [9]  [12]  [13]

	========================PASS========================


	TEST #6: Remove root with two branches
 [2]  [3]  [4]  [6]  [8]  [9]  [12]  [13]

	========================PASS========================


	TEST #7: Remove root with one branch
lab7(37545,0x7fff7325b000) malloc: ** error for object 0x7fb0fac031f0: pointer being freed was not allocated

TO RUN:
Instructions for extracting your archive and running your code
    Unzip the archive, then enter the following commands:
    ''''''''''
        make
        ./lab7
    ''''''''''

EXTRA CREDIT:
Describe any extra credit you may have completed here

BIBLIOGRAPHY:
Any references or resources you may have used to help you complete the program

MISCELLANEOUS:
Any additional notes you feel are relevant to your submission
