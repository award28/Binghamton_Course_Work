/* Homework Assignment 4 - Prolog 2
   Programming Languages
   CS471, Spring 2017
   Binghamton University 
   Austin Ward
   B00518794
   */

/* Instructions */

/* This section deals with general submission instructions.
First, grab this assignment from the site. BEFORE MOVING ON RENAME hw4S18.asn
to username_hw4.pl.
You will be able to code in and run the file in the Prolog interpreter directly.
I recommend reading this assignment directly from the source file.

We will be using swipl for our Prolog environment: To load/reload this file,
cd to its directory and run swipl. Then, in the prompt, type [hw4].

cd PATH_TO_FILE
swipl
[hw4].

From then on you may execute queries (goals) in the prompt. As usual, you
should provide your answers in the designated spot. Once you have added some
code to the file, rerun [hw4]. in the swipl prompt to reload.

In addition, there are unit tests for each problem. These are there to help you
better understand what the question asks for, as well as check your code. They
are included in our "database" as queries and are initially commented out
-- % is a Prolog line comment.

%:- member_times(4,[3,3,2,3],0). % SUCCEED
%:- member_times(4,[1,2,3],3).   % FAIL

After you have finished a problem and are ready to test, remove the initial %
for each test for the associated problem and reload the assignment file
([hw4].). Each SUCCEED line should silently load and succeed, and each FAIL
line should throw a WARNING. If a SUCCEED line throws a WARNING, or a FAIL line
fails to, then you solution is not correct. If you pass the tests there is a
good chance that your code is correct, but not guaranteed; the tests are meant
as guided feedback and are not a check for 100% correctness. */

/* Submission */

/* For this assignment - and the remaining Prolog assignments - you must submit
only the source (template) file. There is no need to tar anything as all coding
should be done directly in hw4.pl. */

/* Homework 4 */

/* Due: , 2/13 at 11:59 PM */

/* Purpose: To get comfortable with backtracking, recursion,
   become familar with reflective mechanism of Prolog,
   and Prolog as a symbolic programming language.
*/

my_append([],Ys,Ys).
my_append([X|Xs],Ys,[X|Zs]) :- my_append(Xs,Ys,Zs).

my_prefix(_,[]).
my_prefix([X|Xs], [X|Ys]) :- my_prefix(Xs,Ys).



/* Problem 0A (NOT GRADED):
Using the preceding predicates, draw the execution trees for the following
queries (goals). You should also enter the queries in swipl to test.

my_append([a,b],[c],Z).
my_append(Xs,[c],[a,b,c]).
my_append(Xs,Ys,[a,b,c]).
my_prefix([a,b,c],Z).

After drawing the execution trees, enable tracking on my_append and my_prefix
by running (two separate queries)

trace(my_append).
trace(my_prefix).

in swipl. Now, execute the above queries and try and match what you drew to
the way the actual query is executed in swipl. To turn off 'trace', type the
query 'nodebug'.

If you prefer a graphical debugger/trace, enter the query 'manpce.' . You will
see a small XPCE manual window. Under the 'Tools' menu select: "Prolog
graphical tracer".

*/


/* Problem 0B (NOT GRADED):
   Each line is an individual Prolog query; it's a good idea type them in your
   prompt (not the file itself) to get a feel for the way Prolog works. You
   should think about whether or not each query will succeed, and if so how the
   variables will be initialized (unified). It will help in doing some of the
   problems.
   (This will be useful in solving problem 8.

?- number(A), A = 5.6.
?- A = 5.6, number(A).
?- integer(4).
?- help(functor).
?- functor(foo(a,b,c),F,N).
?- functor(T,foo,3).
?- help(arg).
?- arg(3, foo(a,b,c),A).
?- help('=..').
?- T =.. [foo,x, y, z].
?- E =.. ['+',2,3], R is E.
?- foo(who, what) =.. T.
?- foo(who, what) =.. [A, B,C].
?- clause(ack(M,0,B),C).
?- clause(H,(B is 2*0)).
*/



/* Problem 1:
   Write a predicate sumlist(List,Sum) which succeeds if Sum is the total value
   of all the elements of List. This will be a top down recursion.
   The recursion clause will add the current value to the result of the sum
   of the rest of the list.
   We have already provided the base case for this predicate underneath
   'Problem 1 Answer'. You just need to add the recursive clause.
*/

/* Problem 1 Answer */

sumlist([], 0).
sumlist([H|T], N) :- sumlist(T, N1), N is N1 + H.

/* Problem 1 Test */
/* There should be no warnings when compiling,
   tests which are supposed to fail are written as such */

:- sumlist([], 0).
:- sumlist([], 1) -> fail ; true.
:- sumlist([1,2,3,4], 10).
:- sumlist([1], 1).

/* Problem 2:
   Write the predicate sumlist2(List,Sum) which succeeds if Sum is the sum total
   of all the elements of List. Instead of adding the current value to the
   result of the sum of the tail, you will calculate the partial sum of the all
   the elements you have reached so far. You will need an extra argument to
   store the partial sum, so you will write an auxilitary predicate sumlist2/3
   to handle the extra argument.

   Underneath 'Problem 2 Answer' we have provided sumlist2/2, which calls the
   auxiliary predicate sumlist2/3. We have also provided the base case for the
   auxiliary predicate. You just need to add the recursive clause for
   sumlist2/3.

*/

/* Problem 2 Answer */

sumlist2(List, Sum) :- sumlist2(List, 0, Sum).
sumlist2([], Sum, Sum).
sumlist2([H|T], Partial, Sum) :- Partial1 is Partial + H, sumlist2(T, Partial1, Sum).
/* Problem 2 Test */

:- sumlist2([], 0).
:- sumlist2([], 1) -> fail ; true.
:- sumlist2([1,2,3,4], 10).
:- sumlist2([1], 1).

/* Problem 3:
   Write the predicate sumPartialR(N, SumLst), which succeeds as follows:
   given a number N, SumLst is a sequence of sums such that the first number in
   S is the sum of all the numbers from N to 1, the second number in S the sum
   of all the numbers from N-1 down to 1, and so on.
   In other words, SumLst = [N+(N-1)+..+1, (N-1)+(N-2)+..+1, ..., 1].
   For example:

     ?- sumPartialR(6,S).
     S = [21, 15, 10, 6, 3, 1] .

   This problem can be solved in 2 clauses.
*/


/* Problem 3 Answer */
sumPartialR(0, []).
sumPartialR(N, [H|T]) :- sumR(N, H), N1 is N - 1, sumPartialR(N1, T).

sumR(0, 0).
sumR(Num, Sum) :- sumR(Num1, Sum1), Num is Num1 + 1, Sum is Sum1 + Num.

/* Problem 3 Test */

:- sumPartialR(1, [1]).
:- sumPartialR(1, []) -> fail ; true.
:- sumPartialR(2, [3, 1]).
:- sumPartialR(6, [21, 15, 10, 6, 3, 1]).



/* Problem 4:
   Write the predicate sumPartialL(N, SumLst). This problem is very similar to
   Problem 3, but has one key difference. The sum totals accumulate from left
   to right, so the SumLst generated will be different. For example, the first
   value in S will be N, the second value will be N + (N-1), and so on.
   In other words, SumLst = [N, N+(N-1), ..., N+(N-1)+(N-2)+...+1].
   For example,

     ?- sumPartialL(6,S).
     S = [6, 11, 15, 18, 20, 21]

   It would be helpful to follow the idea used in problem 2. So your first
   clause should be:

       sumPartialL(N,Lst):-sumPartialL(N,N,Lst).

   You need to add 2 additional clauses.*/

/* Problem 4 Answer */

sumPartialL(N, L) :- sumPartialL(N, 0, L).
sumPartialL(1, Last, [H]) :- H is Last + 1.
sumPartialL(N, Prev, [H|T]) :- H is Prev + N, N1 is N - 1, sumPartialL(N1, H, T).
  
/* Problem 4 Test */

:- sumPartialL(1, [1]).
:- sumPartialL(1, []) -> fail ; true.
:- sumPartialL(6, [6, 11, 15, 18, 20, 21]).


/* Problem 5:
   A) Give a formal mathematical definition of:
     a) a relation
     b) a function 
   B) Is every function a relation? If false, give a counter example.
   C) Is every relation a function? If false, give a counter example. */

/* Problem 5 Answer: 

A) a) A relation is an arbitraty set of finite variables.
   b) A function is a relationship or expression involving 
      one or more variables in an ordered list.
B) Every funciton is a relation since both are a collection of 
   finite objects.
C) Not every relation is a function since, in a function, no other 
   list of a certain length starting with a certain value can have 
   the same unique associated end value.

*/

/* Problem 6:
   We will use a predicate edge(X,Y) to encode a graph.
   edge(X,Y) is true if there is a directed edge from X to Y.
   The following is a mini graph encoded in Prolog. */

edge(a,b).
edge(a,e).
edge(a,c).
edge(b,a).
edge(b,c).
edge(b,d).
edge(c,e).
edge(f,e).

/* Using your knowledge of backtracking and the findall predicate, write
   predicates outgoing/2 and incoming/2.

   outgoing(X,Y) should succeed if Y is a list of all immediate vertices
   reached from X's outgoing edges. incoming(X,Y) should succeed if Y is a
   list of all vertices that have outgoing edges to X.
*/

/* Problem 6 Answer */


outgoing(V, L) :- findall(X, edge(V, X), L).
incoming(V, L) :- findall(X, edge(X, V), L).

/* Problem 6 Test */
:- outgoing(a,X), X = [b,e,c].
:- outgoing(e,X), X = [].
:- outgoing(a,X), X = [b,e,c].
:- incoming(a,X), X = [b].
:- incoming(f,X), X = [].

:- outgoing(e,X), X = [a] -> fail ; true.
:- incoming(e,X), X = [] -> fail ; true.



/* Problem 7:
   Define homoiconic.
   Is Prolog homoiconic?
   What does it mean to say a language is fully reflective?
   Is Prolog fully reflective?

   (See page 584 and Chapter 12)
*/

/* Problem 7 Answer:
homoiconic - the programming language text has the same 
             structure as its AST
Yes, Prolog is homoiconic.
A language is reflective if it can analyize it's structure 
at runtime and modify it and it's behavior.
No, Prolog is not fully reflective.
*/



/* Problem 8:
   Write a predicate computeS/4. computeS(Op, Arg1, Arg2, Result) succeeds if
   Result is the value after computing Arg1 Op Arg2. Use the insight you gained
   in Problem 0B. Op must be a builtin Prolog operator.
*/

/* Problem 8 Answer: */

computeS(Op, Arg1, Arg2, Result) :- E =.. [Op, Arg1, Arg2], Result is E.

% ?- E =.. ['+',2,3], R is E.

/* Problem 8 Test: */
:- computeS(-, 19, 7, 12).
:- computeS(div, 19, 7, 2).
:- computeS(div, 19, 7, R), R = 2.

:- computeS(/, 19, 7, 2) -> fail ; true.
:- catch((computeS(sin, 90, 1, _), fail), error(_Err, _Context), true).


/* Problem 9:
   In class we discussed the 'is' predicate for evaluating expressions. Write a
   predicate results/2.
   result(Elst,RLst) succeeds if Rlst is unifies with the values computed from
   the list of expressions, Elst.
*/

/* Problem 9 Answer: */
result([], []).
result([E|Elst], [R|Rlst]) :- R is E, result(Elst, Rlst).
/* Problem 9 Test */
:- result([],[]).
:- result([+(3,7), mod(104,7),-(5)],[10, 6, -5]).
:- result([+(3,7), +(15, -(3,11))],X), X = [10, 7].

:- result([+(3,7), mod(104,7)],[10,13]) -> fail ; true.

/* Problem 10:
   A good example of symbolic computation is symbolic differentiation. Below
   are the rules for symbolic differentiation where U, V are mathematical
   expressions, C is a number constant, N is an integer constant and x is a
   variable:

        dx/dx = 1
        d(C)/dx = 0.
        d(Cx)/dx = C
        d(-U)/dx = -(dU/dx)
        d(U+V)/dx = dU/dx + dV/dx
        d(U-V)/dx = dU/dx - dV/dx
        d(U*V)/dx = U*(dV/dx) + V*(dU/dx)
        d(U^N)/dx = N*U^(N-1)*(dU/dx)

   Translate these rules into Prolog. (Please keep the order of the rules the
   same for testing purposes).
*/

/* Problem 10 Answer: */
d(Var, Var, R) :- R is 1.
d(C, _Var, R) :- number(C), R is 0.
d(C*Var, Var, R) :- number(C), R is C.
d(-(Poly), Var, R) :- d(Poly, Var, R1), R = -(R1).
d(U+V, Var, R1+R2) :- d(U, Var, R1), d(V, Var, R2).
d(U-V, Var, R1-R2) :- d(U, Var, R1), d(V, Var, R2).
d(U*V, Var, U*R2 + V*R1) :- d(U, Var, R1), d(V, Var, R2).
d(U^N, Var, N*U^(N1)*R) :- N1 is N-1, d(U, Var, R).
/*
*/

/* Problem 10 Test: */
:- d(x,x,R), R = 1 .
:- d(7*x,x,R), R = 7 .
:- d(x +2*(x^3 + x*x),x,Result), Result = 1+ (2* (3*x^2*1+ (x*1+x*1))+ (x^3+x*x)*0) .
:- d(-(1.24*x -x^3),x,Result), Result = - (1.24-3*x^2*1) .
:- d(-(1.24*x -2*x^3),x,Result), Result = - (1.24- (2* (3*x^2*1)+x^3*0)) .

% Pay careful attention to why this fails.
:- d(x +2*(x^3 + x*x),x,Result), Result = 1+ (2* (3*x^(3-1)*1+ (x*1+x*1))+ (x^3+x*x)*0) -> fail ; true.

/* Problem 11:
   (Exercise 3.5 from Learn Prolog Now!)
   Binary trees are trees where all internal nodes have exactly two children.
   The smallest binary trees consist of only one leaf node. We will represent
   leaf nodes as leaf(Label) . For instance, leaf(3) and leaf(7) are leaf
   nodes, and therefore small binary trees.

   Given two binary trees B1 and B2 we can combine them into one binary tree
   using the functor tree/2 as follows: tree(B1,B2) .
   So, from the leaves leaf(1) and leaf(2) we can build the binary tree
   tree(leaf(1),leaf(2)) .
   From the binary trees tree(leaf(1),leaf(2)) and leaf(4) we can build
   tree( tree(leaf(1), leaf(2)), leaf(4)) .

   Define a predicate swap/2 , which produces the mirror image of the binary
   tree that is its first argument. For example:

   ?-  swap( tree( tree(leaf(1), leaf(2)), leaf(4)), T).
   T  =  tree( leaf(4), tree(leaf(2), leaf(1))).
*/

/* Problem 11 Answer: */

swap(leaf(X), leaf(X)).
swap(tree(X, Y), tree(Y1, X1)):- swap(Y, Y1), swap(X, X1).

/* Problem 11 Test: */
:- swap( tree( tree(leaf(1), leaf(2)), leaf(4)), T), T  =  tree( leaf(4), tree(leaf(2), leaf(1))).
:- swap(leaf(1), leaf(1)).
:- swap(tree(leaf(1), leaf(2)), tree(leaf(1), leaf(2))) -> fail ; true.
