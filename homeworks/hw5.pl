/* Homework Assignment 5
   Programming Languages
   CS471, Spring 18
   Binghamton University */

/* Instructions */

/* This section deals with general submission instructions. 
   First, grab this assignment's  source file. BEFORE MOVING ON RENAME 
   hw5S18.asn to username_hw5.pl. You will be able to code in and run the file 
   in the prolog interpreter directly. I recommend reading this assignment 
   directly from the source file.

We will be using swipl for our prolog environment: 
To load/reload this file, cd to its directory and run swipl. 
Then, in the prompt, type [hw5].

     cd PATH_TO_FILE
     swipl
     [hw5].

From then on you may execute queries (goals) in the prompt. As usual, you should provide your answers in the designated spot. Once you have added some code to the file, rerun [hw5]. in the swipl prompt to reload.

In addition, there are unit tests for each problem. These are there to help you better understand what the question asks for, as well as check your code. They are included in our "database" as queries and are initially commented out -- % is a Prolog line comment.

%:- member_times(4,[3,3,2,3],0). % SUCCEED
%:- member_times(4,[1,2,3],3).   % FAIL

After you have finished a problem and are ready to test, remove the initial % for each test for the associated problem and reload the assignment file ([hw5].). Each SUCCEED line should silently load and succeed, and each FAIL line should throw a WARNING. If a SUCCEED line throws a WARNING, or a FAIL line fails to, then you solution is not correct. If you pass the tests there is a good chance that your code is correct, but not guaranteed; the tests are meant as guided feedback and are not a check for 100% correctness. */

/* Submission */

/* For this assignment -- and the remaining Prolog assignments -- you must submit only the source (template) file. There is no need to tar anything as all coding should be done directly in hw5.pl. */

/* Homework 5 */

/* Due: Next Tuesday, 11:59 PM */

/* Purpose: To get comfortable with unfication and pattern matching. */

/* Problem 0A (NOT GRADED):
Each line is an individual Prolog query; it's a good idea type them in your prompt (not the file itself) to get a feel for the way Prolog works. You should think about whether or not each query will succeed, and if so how the variables will be initialized (unified). You may find these helpful in solving some of the problems in this assignment.

?- S = 19, V = 3, C is S div V.
?- S = 19, V = 3, C is S // V.
?- S = 19, V = 3, C is S / V.
?- A = zzz, atom(A).
?- N = 23, number(N).
?- A = 12, atom(A).
*/


/* Problem 1:
In class we discussed that we can encode a binary search tree in Prolog using complex terms: i.e, the following BST

        5
       / \
      3   7
     / \
    1   4

can be encoded as node(5,node(3,node(1,nil,nil),node(4,nil,nil)),node(7,nil,nil)).

Write a predicate insert(X,Y,Z) that succeeds if Z is the tree Y with X inserted (insert X into Y). You may assume you have a binary search tree. */

/* Problem 1 Answer: */
insert(I_Val, nil, node(I_Val, nil, nil)).
insert(I_Val, node(I_Val, nil, nil), node(I_Val, nil, nil)).

insert(I_Val, node(Val, Y_Left, Right), node(Val, Left, Right)) :- 
  (I_Val < Val), insert(I_Val, Y_Left, Left).

insert(I_Val, node(Val, Left, Y_Right), node(Val, Left, Right)) :- 
  (I_Val > Val), insert(I_Val, Y_Right, Right).

/* Problem 1 Test: */
:- insert(5,node(5,nil,nil),X), X = node(5,nil,nil). %SUCCEED
:- insert(3,node(5,nil,nil),X), X = node(5,node(3,nil,nil),nil). %SUCCEED
:- insert(7,node(5,nil,nil),X), X = node(5,nil,node(7,nil,nil)). %SUCCEED
:- insert(1,node(5,node(3,nil,nil),node(7,nil,nil)),X), X = node(5,node(3,node(1,nil,nil),nil),node(7,nil,nil)).                 %SUCCEED
:- insert(1,node(5,node(3,node(2,nil,nil),nil),node(7,nil,nil)),X), X = node(5,node(3,node(2,node(1,nil,nil),nil),nil),node(7,nil,nil)). %SUCCEED

:- (insert(3,node(5,node(3,node(2,nil,nil),nil),node(7,nil,nil)),X), X = node(5,node(3,node(2,node(3,nil,nil),nil)),node(7,nil,nil))) -> fail ; true.


/* Problem 2:
Using the same encoding for a binary search tree, write a predicate to_list(X,Y) that succeeds if Y is an in-order list of the elements of all the nodes of tree X (Y should show an inorder traversel of X). If you are rusty and do not remember what an inorder traversal is, give https://en.wikipedia.org/wiki/Tree_traversal#In-order a quick glance.

For example...
to_list(node(5,node(3,node(1,nil,nil),node(4,nil,nil)),node(7,nil,nil)),X) will succeed with X = [1,3,4,5,7]. */

/* Problem 2 Answer:  */
to_list(nil, _List).
to_list(node(Val, Left, Right), List) :- 
  to_list(Left, LT),
  to_list(Right, RT),
  append(LT, [Val], Half),
  append(Half, RT, List),
  !
.

/* Problem 2 Tests:  */
:- to_list(node(3,nil,nil),L), L = [3]. %SUCCEED
:- to_list(node(5,node(3,nil,nil),nil),L), L = [3,5].  %SUCCEED
:- to_list(node(5,node(3,node(1,nil,nil),node(4,nil,nil)),node(7,nil,nil)),L), L = [1,3,4,5,7]. %SUCCEED
:- (to_list(node(3,nil,nil),L), L = [5]) -> fail ; true.


/* Problem 3:
Write a predicate right_rotate(X,Y) that succeeds if Y is the tree X rotated right at its root. Read https://en.wikipedia.org/wiki/Tree_rotation to refresh tree rotation in full. This problem may seem hard at first, but once you "see" the answer it really demonstrates the elegance of unfication/pattern matching. You do not need to handle error cases.

For example, the following shows a right rotation at the root.

        5                        3
       / \                      / \
      3   7         -->        2   5
     / \                          / \
    2   4                        4   7

*/

/* Problem 3 Answer: */
right_rotate(
  node(T_Val, node(L_Val, LLeft, LRight), Right),
  node(L_Val, LLeft, node(T_Val, LRight, Right))
).

/* Problem 3 Test: */
:- right_rotate(node(5,node(3,node(2,nil,nil),node(4,nil,nil)),node(7,nil,nil)),X), X = node(3, node(2, nil, nil), node(5, node(4, nil, nil), node(7, nil, nil))). %SUCCEED
:- right_rotate(node(5,node(3,nil,node(4,nil,nil)),node(7,nil,nil)),X), X = node(3, nil, node(5, node(4, nil, nil), node(7, nil, nil))). %SUCCEED
:- right_rotate(node(3,node(2,node(1,nil,nil),nil),nil),X), right_rotate(X,Y), Y = node(1,nil,node(2,nil,node(3,nil,nil))). %SUCCEED

:- right_rotate(node(5,nil,node(7,nil,nil)),_) -> fail ; true. %FAIL


/* Problem 4:

 In the assignment 4, you wrote Prolog rules for symbolic differentiation.
 Below is my solutions for this problem.
 Keep in mind, though, that terms such as U+V are still trees with the functor
 at the root, and that evaluation of such terms requires additional processing
 which you will complete.

 Define the predicate, 'evaluate'/3, that uses the result from symbolic
 differentiation  and a list of items with the structure var:value (e.g. [a:5,x:6]
 and computes the resulting value. e.g.

    ?- d(3*(x +2*x*x),x,Result), VarValue = [x:2,y:5], evaluate(Result,Value,VarValue).
    Result = 3* (1+ (2*x*1+x*2))+ (x+2*x*x)*0,
    VarValue = [x:2, y:5],
    Value = 27


    ?- d((3*x) ^ 4,x,Result), VarValue = [x:2,y:5] , evaluate(Result,Value,VarValue).
    Result = 4* (3*x)^3*3,
    VarValue = [x:2, y:5],
    Value = 2592.


 */

/* Problem 4 Answer:  */

d(x,x,1).
d(C,x,0):-number(C).
d(C*x,x,C):-number(C).
d(-U, X, -DU) :- d(U, X, DU).
d( U + V, x, RU + RV ):-d(U,x,RU), d(V,x,RV).
d( U - V, x, RU - RV ):-d(U,x,RU), d(V,x,RV).
d(U * V,x, U * DV + V * DU):- d(U,x,DU), d(V,x,DV).
d(U ^ N, x, N*U ^ N1*DU) :- integer(N), N1 is N-1, d(U, x, DU).


evaluate(Result, VarValue, []) :- VarValue is Result.
evaluate(Result, VarValue, [Var:Value|T]) :- replace(Result, Var, Value, Res), evaluate(Res, VarValue, T).
replace(Term,Term,With,With) :- !.
replace(Term,Find,Replacement,Result) :-
  Term =.. [Functor|Args],
  replace_args(Args,Find,Replacement,ReplacedArgs),
  Result =.. [Functor|ReplacedArgs]
.
replace_args([],_,_,[]).
replace_args([Arg|Rest],Find,Replacement,[ReplacedArg|ReplacedRest]) :-
  replace(Arg,Find,Replacement,ReplacedArg),
  replace_args(Rest,Find,Replacement,ReplacedRest)
.

/* Problem 4 Tests:  */
:- evaluate(x*y, 6, [x:2, y:3]).
:- evaluate(x*y, 8, [x:2, y:3]) -> fail ; true.
:- evaluate(x^3, 8, [x:2]).
:- evaluate(2*8, 16, []).
:- evaluate(2*8, 0, []) -> fail ; true.
:- evaluate(2*y, 16, [y:8]).

:- d(3*(x +2*x*x),x,Result), VarValue = [x:2,y:5], evaluate(Result,Value,VarValue),
    Result = 3* (1+ (2*x*1+x*2))+ (x+2*x*x)*0,
    VarValue = [x:2, y:5],
    Value = 27.

:- d((3*x) ^ 4,x,Result), VarValue = [x:2,y:5] , evaluate(Result,Value,VarValue),
    Result = 4* (3*x)^3*3,
    VarValue = [x:2, y:5],
    Value = 2592.


/* Problem 5:
We will encode a mini-AST in Prolog using complex data structures. A "node" will consist of either a nb(Functor,LeftExpr,RightExpr), nu(Functor,Expr) or nn(Number).

nb(Functor,LeftExpr,RightExpr) -- "node binary", Functor is guaranteed to be a binary arithmatic predicate that can be evaluated with `is`. LeftExpr and RightExpr are recursively defined "nodes".

nu(Functor,Expr) -- "node unary", Functor is guaranteed to be a unary arithmatic predicate that can be evaluated with `is`. Expr is a recursively defined "node".

nn(Number) -- "node number", Number is guaranteed to be just that.

Hence, the following AST
      +
     / \
    *   random
   / \       \
  2  3        5
would be encoded as nb(+,nb(*,nn(2),nn(3)),nu(random,nn(5))).

Write a predicate run(X,Y) that succeeds if Y is the result obtained from "running" (evaluating) X. You will need to use the =.. predicate. It may be helped to view some of the binary and unary arithmetic predicates -- http://www.swi-prolog.org/man/arith.html. If you write your predicate correctly, you do not need to concern yourself with the actual arithmetic functor supplied in the nodes. */

/* Problem 5 Answer: */

run(nn(Val), Val).
run(nu(U_Op, Val), Ret) :- 
  run(Val, R_Val),
  Op =..[U_Op, R_Val], 
  Ret is Op
.
run(nb(B_Op, Left, Right), Ret) :- 
  run(Left, L_Val), 
  run(Right, R_Val),  
  Op =.. [B_Op, L_Val, R_Val],
  Ret is Op
.

/* Problem 5 Tests: */
:- run(nb(+,nb(*,nn(2),nn(3)),nu(random,nn(5))),_).
:- run(nb(+,nb(*,nn(2),nn(3)),nn(3)),E), E=9.
:- run(nb(+,nb(*,nn(2),nn(3)),nb(-,nn(6),nn(3))),E), E=9.
:- run(nn(2),E), E=2.
:- run(nu(abs,nn(-2)),E), E=2.

:- (run(nb(+,nb(*,nn(2),nn(3)),nb(-,nn(6),nn(3))),E), E=8) -> fail ; true.


/* Problem 6:
Using the AST described in problem 5, write a predicate binaryAP/2.  binaryAP(AST, BPlst) succeeds if all the binary arithmetic predicates that occur in AST are collected into BPlst.  Use an inorder traversal of AST.  */

/* Problem 6 Answer: */
binaryAP(nn(_), []).
binaryAP(nu(_, Main), List) :- binaryAP(Main, List).
binaryAP(nb(Op, Left, Right), List) :- 
  binaryAP(Left, LT),
  binaryAP(Right, RT),
  append(LT, [Op], Half),
  append(Half, RT, List),
  !
.


/* Problem 6 Tests: */
:- T = nb(+,nb(*,nn(2),nn(3)),nu(random,nn(5))), binaryAP(T,L), L = [*, +].  %SUCCEED
:- T = nb(+, nb(*, nn(2), nn(3)), nb(-,nn(3), nn(5))),  binaryAP(T,L), L = [*, +, -]. %SUCCEED
:- T = nb(+, nb(*, nn(2),  nb(-,nn(3), nb(//, nn(2), nn(5)))),nn(9)) ,  binaryAP(T,L), L = [*, -, //, +]. %SUCCEED

:- (T = nb(+,nb(*,nn(2),nn(3)),nu(random,nn(5))), binaryAP(T,L), L = [+,*]) -> fail ; true.      %FAIL



/* Problem 7:
   Write a predicate noAtom/2.  noAtoms(+NestedLists, -C) that counts all the atoms in the
   NestedLists. The NestedLists contains only lists or atoms.  You may assume no numbers
   or variables are in any of the lists.

   ?- noAtoms([[r,ss,[a,b,c]],[a,b,c],[],[s,t,a,b]],C).
   C = 12.
   ?- noAtoms([[r,ss,[a,b,c]],[a,b,c],[],[s,t,[[]],b]],C).
   C = 11.

   Think What NOT how.  */

/* Problem 7 Answer: */
noAtoms([], 0).
noAtoms([H|T], C) :- atom(H), noAtoms(T, C1), C is C1 + 1.
noAtoms([H|T], C) :- noAtoms(H, C1), noAtoms(T, C2), C is C1 + C2.

/* Problem 7 Tests: */
:- noAtoms([[r,ss,[a,b,c]],[a,b,c],[],[s,t,a,b]],12).
:- noAtoms([[r,ss,[a,b,c]],[a,b,c],[],[s,t,a,b]],19) -> fail ; true.
:- noAtoms([[r,ss,[a,b,c]],[a,b,c],[],[s,t,a,b]],10) -> fail ; true.
:- noAtoms([[r,ss,[a,b,c]],[a,b,c],[],[s,t,[[]],b]],11).
:- noAtoms([r], 1).
:- noAtoms([r], 3) -> fail ; true.
:- noAtoms([[[r]]], 1).


/* Problem 8:

In class we discussed difference lists and how to append two of them in "constant" time.

Write a predicate, append3DL(A,B,C,D) that succeeds if D is the difference lists A, B, and C appended.
*/

/* Problem 8 Answer: */
append3DL(L - M, M - N, N - P, L - P).
/* Problem 8 Tests: */
:- append3DL([1,2|A]-A,[3,4|B]-B,[5,6|[]]-[],L), L = [1,2,3,4,5,6]-[]. % SUCCEED
:- append3DL([a,b|A]-A,[b,1,2|B]-B,[3|C]-C,L), L = [a, b, b, 1, 2, 3|C]-C. % SUCCEED


:- (append3DL([1,2|A]-A,[3,4|B]-B,[5,6|[]]-[],L), L = [1,2,3,4,5]-[]) -> fail ; true.   % FAIL



/* Problem 9:
   In class we discussed green and red cuts (!). A green cut is a cut that DOES
   NOT change correctness (the answer returned) but simply improves efficiency
   by preventing unnecessary backtracking. Red cuts change correctness - if a
   predicate is correct and contains a cut that, when removed, is no longer
   correct, it is a red cut.

   Insert cuts into the following 2 predicates. The my_max/3 are already correct, 
   but using a cut (green) will improve their efficiency. 
   The last, my_max1/3 is wrong, but inserting a cut (red) will
   make it correct.
*/

/* Problem 9 Answer */


my_max(X,Y,Y) :- X =< Y, !.
my_max(X,Y,X) :- X > Y.

my_max1(X,Y,Z) :- X =< Y, !, Y = Z.
my_max1(X,_,X).

/* Problem 9 Test */
% You're own your own for this one :) */
:- my_max(5, 8, X), X = 8.
:- my_max(8, 5, X), X = 8.
:- (my_max(5, 8, X), X = 5)  -> fail ; true.  
:- my_max1(5, 8, X), X = 8.  
:- my_max1(8, 5, X), X = 8.  
:- (my_max1(8, 5, X), X = 5)  -> fail ; true.  


/* Problem 10:
   In class we will discuss how Prolog can be used for solving puzzles.
   We will do a well know puzzle: "Send more money".
   Each of the letters  D,E,M,N,O,R,S and Y represents a different digit.
   Moreover, when each letter is mapped to its corresponding digit
   the equation SEND + MORE = MONEY holds.

   Our solution was very naive using Prolog ability to search for the solution.
   The search is very slow because 8 letters to be solved, it simply explores
   the 10*9*...*3 mappings of letters to digits.

   You can speed up the search by implementing the following insights:
      Clearly, SEND < 9999 and MORE < 9999. Thus MONEY < 19998 and hence M = 1.
      Now we have SEND + 1ORE = 1ONEY.
      Again SEND < 9999 and now 1ORE < 1999 so 1ONEY < 11998.
      Since M is already bound to 1, O must be bound to 0.
      A little more thought shows that S must be bound to 8 or 9, and that
      N = E + 1.

   Using these insights to reduce the number of solutions that must be explored,
   write a Prolog predicate sendMoreMoney([D,E,M,N,O,R,S,Y]) that solves this
   puzzle by binding the correct digits to each of the variables in the list.
*/

/* Problem 10 Answer: */
solveSlow( [D,E,M,N,O,R,S,Y]) :-
  Lst = [S,E,N,D,M,O,R,Y],
  Digits = [0,1,2,3,4,5,6,7,8,9],
  assign_digits(Lst, Digits),
  1000*S + 100*E + 10*N + D +
  1000*M + 100*O + 10*R + E =:=
  10000*M + 1000*O + 100*N + 10*E + Y,
  write(Lst)
.
assign_digits([], _List).
assign_digits([D|Ds], List):-
  select(D, List, NewList),
  assign_digits(Ds, NewList)
.

sendMoreMoney([D, E, M, N, O, R, S, Y]) :- 
  M = 1, O = 0,
  Lst = [S, E, N, D, R, Y],
  Digits = [2, 3, 4, 5, 6, 7, 8, 9],
  assign_digits(Lst, Digits),
  1000*S + 100*E + 10*N + D +
  1000*M + 100*O + 10*R + E =:=
  10000*M + 1000*O + 100*N + 10*E + Y
.
/* Problem 10 Test: */
:- M = 1, sendMoreMoney([D,E,M,N,O,R,S,Y]), M = 1, D = 7, E = 5, N = 6, O = 0, R = 8, S = 9, Y = 2.

/* Problem 11:

Write a predicate change/2 that given the change amount, computes the way in which exact change can be given. Use the following USA's coin facts at your solution. */

coin(dollar, 100).
coin(half, 50).
coin(quarter, 25).
coin(dime,10).
coin(nickel,5).
coin(penny,1).

/* The predicate change(S,CL) succeeds if given a positive integer S, CL is a list of tuples that contains the name of the coin and the number of coins needed to return the correct change.

The Coin Changing problem is an interesting problem usually studied in Algorthms.
http://condor.depaul.edu/~rjohnson/algorithm/coins.pdf is a nice discussion.
Think about (no need to turn in)
   1) How could we generalize this problem to handle coins from other currencies?
   2) What are the different techinques to find the change with the fewest number of coins ?
   3) What happens if the order of the "coin" facts change?  */

/* Problem 11 Answer: */

change(0, []).
change(S, [H|T]) :- coin(Name, Val), S1 is S // Val, S1 >= 1, R is S mod Val, H = (Name, S1), change(R, T).

/* Problem 11 Tests: */
:- change(168,C), C = [ (dollar, 1), (half, 1), (dime, 1), (nickel, 1), (penny, 3)] .  %SUCCEED
:- change(75,C),  C = [ (half, 1), (quarter, 1)] .                                     %SUCCEED

:- (change(75,C), C = [(half, 2)]) -> fail ; true.             %FAIL
   %FAIL
