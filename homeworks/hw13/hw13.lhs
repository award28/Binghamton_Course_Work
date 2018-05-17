> hLen :: (Num u, Eq t) => ([t] -> u) -> [t] -> u 
> hLen = (\f x -> if x == [] then 0 else 1 + (f (tail x)))
> myLength ls = if ls == [] then 0 else 1 + myLength (tail ls)

hLen is not recursive because it does not call itself.

hLen is a HOF function because it takes a funciton as a param

    ...>hLen sum [4,5,6]
    12

    ...> hLen head [4,5,6]
    6

hLen will return 0 if the list is empty or 1 + what the past in function 
with the tail of the list returns.

    ...> hLen myLength [4,5,6]
    3

hLen and myLength are similar in that they both can be used for counting the 
length of a list. myLength is recursive, while hLen needs to be passed a
function that can count the remaining number of elements.

You can use n hLen functions consecutively with a random function and a list of
n elements to get the sum of the list. AKA:

    ...> hLen (hLen (hLen myLength)) [1,2,3]
    3

> factorial :: Integral a => a -> a
> factorial n = if n ==0 then 1 else n * (factorial (n - 1))

> hFact :: (Int->Int)->Int->Int
> hFact = \ f n -> (if n==0 then 1 else n * f (n-1))

> factorial' = hFact factorial'

    ...> :t factorial'
    factorial' :: p

> fix f = f (fix f )

    ...> :t fix
    fix :: (t -> t) -> t

The difference between

    > fix f = f (fix f )
    and
    > fix f = f fix f

is that the first one does not construct an 'infinite type' and the second one
does, so haskell can't construct it. An infinite type means that the type your 
function is trying to identify is itself to and so it trys to identify itself 
and is infinitely nested.

    ...> factorial 6
    720

    ...> hFact factorial 6
    720

    ...> factorial' 6
    720

    ...> fix hFact 6
    720
