Part A:

What is the type of  (\x -> x)?

(\x -> x) :: p -> p

What is the value of (and verify by typing in hugs/ghci).
(\x -> x) 3 ? (Verify by typing in hugs/ghci).

    ...> (\x -> x) 3
    3

(\x -> x) (+) 5 3 ?

    ...> (\x -> x) (+) 5 3
    8

(\x -> x) (+)?  

    ...> (\x -> x) (+)
    • No instance for (Show (Integer -> Integer -> Integer))

What would be a descriptive name for the abstractions in 2.b?

    fivePlusThree

What is the value of
(\x -> x +x ) 3 (verify by typing in hugs/ghci).

    ...>(\x -> x +x ) 3
    6

What is the expression ? (E)

    x + x

What is the value of
(\x -> 3) 6 ? (verify by typing in hugs/ghci).

    ...>(\x -> 3 ) 6
    3

What would be a descriptive name for this abstractions?

    three


> factorial :: Integral a => a -> a
> factorial n = if n ==0 then 1 else n * (factorial (n - 1))

1.
    
> hFact = (\f -> f)

    ...>:t hFact
    hFact :: p -> p

2.
    ...>hFact (^ 2) 4
    16

3.
    ...> hFact factorial 5
    120
    
    ...> factorial 5
    120
