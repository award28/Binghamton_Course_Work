> map' f [] = []
> map' f (x:xs) = (f x):(map f xs)


> dot btoc atob a = btoc (atob a)


> triangularT 0 acc = acc
> triangularT n acc = triangularT (n - 1) (n + acc)

> triSeq = 0:1:[x + y | (x, y) <- zip (tail triSeq) [2..]]


> fdl f b [x] =  f b x
> fdl f b (x:xs) = f (fdl f b xs) x


> fMap :: (t -> u) -> [t] -> [u]

> fMap f [] = []
> fMap f s = foldr (\x xs -> (f x):xs) [] s
