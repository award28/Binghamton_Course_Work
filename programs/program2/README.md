
CS240 Data Structures and Algorithms
Spring 2016
program2 README FILE

Due Date: 4/20/16
Submission Date: 4/19/16
Author(s): Austin Ward
e-mail(s): award9@binghamton.edu

PURPOSE:
Describe the purpose of the software as described by the software requirements in your own words
   Implement a max-heap based array for a tournament of backroom high card.

PERCENT COMPLETE:
How much of the project you believe you have completed
    100% of the project.

PARTS THAT ARE NOT COMPLETE:
What parts of the project you were not able to complete
    
BUGS:
Known bugs

FILES:
A list of files included in the jar archive, including this README
    Card.hpp, Deck.hpp/cpp, Heap.hpp/cpp, Player.hpp/cpp, Table.hpp/cpp, program2.cpp, players.txt, players2.txt, README.md, makefile 

SAMPLE OUTPUT:
A sample of the output from your program copy and pasted from the terminal
	TEST #0: Missing file handled

	========================PASS========================


	TEST #1: Create Players and store them in a heap

	========================PASS========================


	TEST #2: Players stored in correct order when removed from the heap

	========================PASS========================


	TEST #3: Heap is empty

	========================PASS========================


	TEST #4: Can add individual players to the heap

	========================PASS========================


	TEST #5: Play 1 round of highcard

	========================PASS========================


	TEST #6: Play highcard tournament

	Winner: Tyler Durden
	Winnings: 1180

	========================PASS========================


	TEST #7: Play highcard tournament with equal starting budgets

	Winner: John McClane
	Winnings: 430

	========================PASS========================


	TEST #8: Check heap copy constructor

	========================PASS========================


	TEST #9: Call getPlayer when non exist

	========================PASS========================
    
TO RUN:
Instructions for extracting your archive and running your code
    Unzip the archive, then enter the following commands:
    ''''''''''
        make
        ./program2 
    ''''''''''

EXTRA CREDIT:
Describe any extra credit you may have completed here

BIBLIOGRAPHY:
Any references or resources you may have used to help you complete the program

MISCELLANEOUS:
Any additional notes you feel are relevant to your submission
