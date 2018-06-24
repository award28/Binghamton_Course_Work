father(john, tom).
father(tom, mike).
father(tom, jane).
grandfather(X, Y) :- father(X, Z), father(Z, Y).
