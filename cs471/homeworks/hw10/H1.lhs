> module H1
> where

Define factorial. Let Haskell infer the type of factorial.

> factorial n = if n == 0 then 1 else n * factorial (n - 1)

> factorialG n
>   | n == 0    = 1
>   | otherwise = n * factorialG (n - 1)

> factP :: Integer -> Integer
> factP 0 = 1
> factP n = n * factP(n -1)
