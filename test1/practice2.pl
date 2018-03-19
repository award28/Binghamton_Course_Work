edge(a, b).
edge(a, c).
edge(c, d).
edge(d, b).
edge(f, x).

path(X, Y) :- edge(X, Y).
path(X, Y) :- edge(X, Z), edge(Z, Y).

:- path(a, b).
:- path(c, b).
:- (path(c, a)) -> fail; true.
