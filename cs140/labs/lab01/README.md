# Lab 01

### Part 1

You are working in a Linux Lab (LNG-103 in the basement of the Bartle
Library) - the operating system on these computers is the Ubuntu
variant of Linux:

1. Enter your Binghamton user id and PODS password to logon -- if that
   does not work consult the TA
1. The TA will show you how to open your "Home Folder" file browser
   and the location of the "File System" folder
1. This home directory is your H drive, i.e. your main directory on
   the bingsuns2 server

#### Some initial setup

1. Open a terminal window

1. Run `rm -rf .cache`
1. Run `rm -rf .android-sdk`
1. Run `mkdir -p cs140/labs` to make a new directory named cs140,
   which itself has one directory named labs
1. Enter into this new directory by running `cd cs140/labs`
1. You are encouraged to use a file structure similar to this one to help keep
   your files organized, however how you organize your system is up to you.

### Part 2

#### Create a [gitlab](http://gitlab.com) account

1. Go to [gitlab.com](http://gitlab.com)
1. Click 'Sign in' in the top-right of the page
1. Scroll down to the 'New user? Creat an acount' form
1. Use your **binghamton** email
1. Raise your hand and show your TA your username and he will give you
   access to the rest of the lab

### Part 3

This semester we are using a program called `git` to retrieve and
submit labs and assignments.
Here are the directions to retrieve the first lab:

* Open a new terminal window and enter your labs directory (`cd cs140/labs`)
* Run `git clone https://gitlab.com/bu-cs140/lab01.git`

There will now be a folder called 'lab01' with the lab files in it.

* Enter the directory by typing `cd lab01`

If you type `ls` you will see all of the files and directories for the
lab.
If you open `README.md` you will see the same directions that you are
currently reading. Lab and assignment directions will always be in a
file called `README.md`.
The `md` extension stands for markdown.
Markdown is a way to present text in a readable format using lists,
links, etc.

Right now we are interested in the file called `HelloWorld.java`.
Open the file with `gedit HelloWorld.java &` and inspect its contents.

We now want to run this code, but first we have to compile it.

To compile `HelloWorld.java` type `javac -d . HelloWorld.java`.
This will create a `HelloWorld.class` file in a directory `lab01`
which is the compiled version of `HelloWorld.java`.
It is in the folder `lab01` because at the top of `HelloWorld.java`
there is a package declaration `package lab01`.
The `-d .` tells `javac` to place the compiled files in the
current directory (`-d` takes a directory to place the files and `.`
stands for 'current directory').

Now we can run the program.
Type `java -cp . lab01.HelloWorld`.
The `-cp .` tells `java` to look for the packages and classes in the
current directory. The `lab01.HelloWorld` tells java to run the
`HelloWorld` class inside the `lab01` package.

You should have just seen "Hello, World!" print out on the screen.
If not, get help from a TA.

### Part 4

We will now explore a more complex scenario with 2 classes,
`Loan.java` and `Loanee.java`.

Open these files in gedit (File->Open or `gedit Loan.java Loanee.java &`)
and look through them. Try to understand every line.
Take notice of the documentation/comments in every file documenting every method.
If you don't understand something ask a TA to explain it to you.

After you've understood everything look at a third file called `Simulation.java`.
The main method here creates some `Loanee`s and tests them. Take a look at
the numbers it uses and try to predict what will be printed.

Compile all three programs at the same time using

`javac -d . Loan.java Loanee.java Simulation.java`

Run the simulation class using

`java -cp . lab01.Simulation`


### Part 5

We can see what files and what lines we've change by using git.
Run the command `git diff` in the directory of the lab (`lab01`).
You should see all the changes you've made to `Loanee.java`.

The lab is now over and there is nothing to submit.