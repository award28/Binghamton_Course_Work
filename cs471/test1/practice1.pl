palindrome([]).
palindrome([X]).
palindrome([H|T]):- same_back(H, T), remove_last(T, T1), palindrome(T1).

same_back(H, [H]).
same_back(H, [H1|T]):-same_back(H,T).

remove_last([X], []).
remove_last([H|T], [H|T1]):-remove_last(T, T1).

dups([], []).
dups([H|T], New) :- same_front(H, T), dups(T, New), !.
dups([H|T], [H|T1]) :- dups(T, T1).

same_front(H, [H|T]).

rotate_left(List, New, N) :- N = 0, New = List.
rotate_left([H|T], New, N) :- append(T, [H], R), N1 is N - 1, rotate_left(R, New, N1).

gcd(A, 0, A).
gcd(A, B, R) :- C is A mod B, gcd(B, C, R).

ack(X, Y, Z, R) :- X = 0, R is Y + Z.
ack(X, Y, Z, R) :- X = 1, Z = 0, R = 0.
ack(X, Y, Z, R) :- X = 2, Z = 0, R = 1.
ack(X, Y, Z, R) :- X > 2, Z = 0, R = Y.
ack(X, Y, Z, R) :- X > 0, Z > 0, X1 is X - 1, Z1 is Z - 1, ack(X, Y, Z1, Z2), ack(X1, Y, Z2, R).
