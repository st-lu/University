import Data.Char
-- lab 1
maxim :: Int -> Int -> Int
maxim x y =
    if (x > y)
        then x
        else y

maxim3 :: Int -> Int -> Int -> Int
-- maxim3 x y z = 
--     if (x > y)
--         then if (x > z)
--                 then x
--                 else z
--         else if (y > z)
--                 then y
--                 else z
maxim3 x y z =
    let u = maxim x y
    in maxim u z

maxim4 :: Int -> Int -> Int -> Int -> Int
maxim4 x y z t =
    let
        u = maxim x y
        v = maxim z t
    in
        maxim u v

-- testMaxim4 :: Int -> Int -> Int -> Int -> Int -> Bool
testMaxim4 maxim4 x y z t =
    let u = maxim4 x y z t
    in u >= x && u >= y && u >= z && u >= t

data Alegere
    = Piatra
    | Foarfeca
    | Hartie
    deriving (Eq, Show)
data Rezultat
    = Victorie
    | Infrangere
    | Egalitate
    deriving (Eq, Show)
partida :: Alegere -> Alegere -> Rezultat
partida x y =
    if( x == y)
        then Egalitate
        else if (x == Piatra)
                then if (y == Hartie)
                        then Infrangere
                        else Victorie
                else if (x == Foarfeca)
                        then if (y == Hartie)
                                then Victorie
                                else Infrangere
                        else if (y == Piatra)
                                then Victorie
                                else Infrangere

--bv frt esti zeu
-------------------------------------------------------------------------------

--lab2
fibo :: Int -> Int
fibo n
    | n < 2 = n
    | otherwise = fibo(n - 1) + fibo(n - 2)

fibo2 :: Int -> Int
fibo2 0 = 0
fibo2 1 = 1
fibo2 n = fibo2(n-1) + fibo2(n-2)

fibonacciLiniar :: Integer -> Integer
fibonacciLiniar 0 = 0
fibonacciLiniar n = snd (fibonacciPereche n)
  where
    fibonacciPereche :: Integer -> (Integer, Integer)
    fibonacciPereche 1 = (0, 1)
    -- fibonacciPereche 2 = (1, 1)
    -- fibonacciPereche 3 = (1, 2)
    -- fibonacciPereche 4 = (2, 3)
    -- fibonacciPereche 5 = (3, 5)
    fibonacciPereche n = (snd(ceva), snd(ceva) + fst(ceva))
        where
            ceva = fibonacciPereche(n-1)

semiPare :: [Int] -> [Int]
semiPare [] = []
semiPare (h : t)
    | even h = div h 2 : semiPare t
    | otherwise = semiPare t

semiPare2 :: [Int] -> [Int]
semiPare2 l = [div x 2 | x <- l, even x]

inIntervalR :: Int -> Int -> [Int] -> [Int]
inIntervalR a b [] = []
inIntervalR a b (h:t)
    | h >= a && h <= b = h : inIntervalR a b t
    | otherwise = inIntervalR a b t


inIntervalC :: Int -> Int -> [Int] -> [Int]
inIntervalC a b l = [x | x <- l, x >= a && x <= b]

pozitiveC :: [Int] -> Int
pozitiveC l = length [x | x <- l, x > 0]

pozitiveR :: [Int] -> Int
pozitiveR [] = 0
pozitiveR (h:t)
    | h > 0 = 1 + pozitiveR t
    | otherwise = pozitiveR t

pozitiiImpareC :: [Int] -> [Int]
pozitiiImpareC l = [snd x | x <- zip l [0,1..], odd (fst x)]

aux :: [(Int, Int)] -> [Int]
aux [] = []
aux (h:t)
    | odd (snd h) = snd h : aux t
    | otherwise = aux t

pozitiiImpareR :: [Int] -> [Int]
pozitiiImpareR l = aux (zip l [0,1..])

-- digitToInt si isDigit din Data.Char
multDigitsC :: [Char] -> Int
multDigitsC l = product [digitToInt x | x <- l, isDigit x]

multDigitsR :: [Char] -> Int
multDigitsR [] = 1
multDigitsR (h:t)
    | isDigit h = (digitToInt h) * (multDigitsR t)
    | otherwise = multDigitsR t

discountC :: [Float] -> [Float]
discountC l = [x*0.75 | x <- l, (x*0.75) < 200]

discountR :: [Float] -> [Float]
discountR [] = []
discountR (h:t)
    | h*0.75 < 200 = h*0.75 : discountR t
    | otherwise = discountR t


-- ZEUS pe muntele olimp esti
------------------------------------------------------------------------

--lab 3

factori :: Int -> [Int]
factori n = [x | x <- [1..n], (n `mod` x) == 0]

prim :: Int -> Bool
prim n =
    if(length (factori n) == 2)
        then True
        else False

numerePrime :: Int -> [Int]
numerePrime n = [x | x <- [2..n], prim x]

myzip3 :: [Int] -> [Int] -> [Int] -> [(Int, Int, Int)]
myzip3 l1 l2 l3 = [(fst x, fst y, fst z) | x <- [1.. length l1] `zip` [0..], y <- [1.. length l2] `zip` [0..], z <- [1.. length l3] `zip` [0..], snd x == snd y && snd y == snd z]

firstEl :: [(a, b)] -> [a]
firstEl l = map fst l

sumList :: [[Int]] -> [Int]
sumList l = map sum l

aux1 :: Int -> Int
aux1 x
    | even x = div x 2
    | otherwise = x*2

pre12 :: [Int] -> [Int]
pre12 l = map aux1 l

--3.4.1
f341 :: Char -> [[Char]] -> [[Char]]
f341 ch l = [snd x | x <- (map (ch `elem`) l) `zip` l, fst x == True]

--3.4.2
f342 :: [Int] -> [Int]
f342 l = map (\x -> x^2) (filter odd l)

--3.4.3
-- f343 :: [Int] -> [Int]
-- f343 l = [(fst x)^2 | x <- l `zip` [0..], odd (snd x)]

pozImp :: (Int, Int) -> Bool
pozImp x
    | odd (snd x) = True
    | otherwise = False

putere :: (Int, Int) -> Int
putere x = fst x ^ 2

f343 :: [Int] -> [Int]
f343 l = map putere (filter pozImp (l `zip` [0..]))

--3.4.4
f344 :: [[Char]] -> [[Char]]
f344 l = [filter (`elem` "AEIOUaeiou") x | x <- l]


----------------------------------------------------------------------------------------

--lab 4

ciurAux::[Int]->Int->Int->[Int]
ciurAux l j i
    | j > i = []
    | j == 2 = 2 : ciurAux [2] 3 i
    | filter (\x -> ((j `mod` x)==0)) l == [] = j:(ciurAux l (j+1) i)
    | True = ciurAux l (j+1) i

ciur::Int->[Int]
ciur i = ciurAux [] 2 i

ordonataNatC [] = True
ordonataNatC [x] = True
ordonataNatC (x:xs) = and [fst x < snd x | x <- zip (x:xs) (tail (x:xs))]

ordonataNatR [] = True
ordonataNatR [x] = True
ordonataNatR (x:xx:xs) = (x < xx) && ordonataNatR(xx:xs) 

ordonare :: Int -> Int -> Bool
ordonare a b
    | a < b = True
    | otherwise = False

divizibilitate :: Int -> Int -> Bool
divizibilitate a b
    | b `mod` a == 0 = True
    | otherwise = False

lexicografic :: [Char] -> [Char] -> Bool
lexicografic a b
    | a < b = True
    | otherwise = False

ordonata :: [a] -> (a -> a -> Bool) -> Bool
ordonata l f = and [f (fst x) (snd x) | x <- zip l (tail l)]

(*<*) :: (Int, Int) -> (Int, Int) -> Bool
(*<*) (a, b) (c, d)
    | a < c && b < d = True
    | otherwise = False

compuneList :: (b -> c) -> [(a -> b)] -> [(a -> c)]
compuneList f l = map (f .) l

aplicaList :: a -> [(a -> b)] -> [b]
aplicaList ex l = [f ex| f <- l]

--------------------------------------------------------------------------------------------
--lab 4 foldr

--definitie foldr
foldr_ :: (a -> b -> b) -> b -> ([a] -> b)
foldr_ op unit = f
    where
        f [] = unit
        f (a:as) = a `op` f as
--final def

produsRec :: [Int] -> Int
produsRec [] = 1
produsRec (x:xs) = x * produsRec xs

produsFold :: [Int] -> Int
produsFold l = foldr (*) 1 l 

andR :: [Bool] -> Bool
andR [] = True
andR (x:xs) = x && andR xs

andF :: [Bool] -> Bool
andF l = foldr (&&) True l

concatR :: [[a]] -> [a]
concatR [] = []
concatR (x:xs) = x ++ concatR xs

concatF :: [[a]] -> [a]
concatF l = foldr (++) [] l

rmChar :: Char -> String -> String
rmChar ch l = [x | x <- l, x /= ch]

rmCharR :: String -> String -> String
rmCharR _ [] = []
rmCharR l (x:xs)
    | x `elem` l = rmCharR l xs
    | otherwise = x : rmCharR l xs

rmCharF l1 l2 = foldr (rmChar) l2 l1

-----------------------------------------------------------------------------------------------------------

-- lab 5

-- foldr
-- ex 1
semn :: [Int] -> [Char]
semn [] = []
semn (x:xs)
    | x <= 9 && x >= -9 && x > 0 = "+" ++ semn xs
    | x == 0 = "0" ++ semn xs
    | x <= 9 && x >= -9 && x < 0 = "-" ++ semn xs
    | otherwise = semn xs

semnF :: [Int] -> [Char]
semnF = foldr op unit
    where
        unit = ""
        a `op` l
            | a <= 9 && a >= -9 && a > 0 = "+" ++ l
            | a == 0 = "0" ++ l
            | a <= 9 && a >= -9 && a < 0 = "-" ++ l
            | otherwise = l

-- Matrici
-- ex 1
lungimi :: [[a]] -> [Int]
lungimi [] = []
lungimi (x:xs) = length x : lungimi xs

corect :: [[a]] -> Bool
corect [] = True
corect (h:t) = and [x == length h | x <- (lungimi (h:t))]

-- ex 2
--varianta de sclavi care nu stiu ca exista operatorul !!
indicei :: [a] -> [(a, Int)]
indicei l = zip l [0..]

indicej :: [[a]] ->[[(a, Int)]]
indicej l = [ x `zip` [0..] | x <- l]

auxj :: [(a, Int)] -> Int -> a
auxj l j = head [fst x | x <-l, snd x == j]

auxi :: [([(a, Int)], Int)] -> Int -> Int -> a
auxi l i j = auxj (head [fst x | x <- l, snd x == i]) j

el :: [[a]] -> Int -> Int -> a
el l i j = auxi (indicei (indicej l)) i j

--varianta de iq 700 cand afli de operatorul !!
elsmart :: [[a]] -> Int -> Int -> a
elsmart l i j = (l !! i) !! j

--ex 3
tuplu3 :: [([a], Int)] -> [[(a, Int, Int)]]
tuplu3 l = [ zip3 (fst x) [(snd x), (snd x)..] [0..] | x <- l]

transforma :: [[a]] -> [[(a, Int, Int)]]
transforma l = tuplu3 (indicei l)

------------------------------------------------------------------------------------------------------------------------------------------

-- lab 6

data Fruct
    = Mar String Bool
    | Portocala String Int

ePortocalaDeSicilia :: Fruct -> Bool
ePortocalaDeSicilia (Portocala soi _)
    | soi == "Tarocco" = True
    | soi == "Moro" = True
    | soi == "Sanguinello" = True
    | otherwise = False
ePortocalaDeSicilia _ = False

--[Mar "Ionatan" False, Portocala "Sanguinello" 10, Portocala "Valencia" 22, Mar "Golden Delicious" True, Portocala "Sanguinello" 15, Portocala "Moro" 12, Portocala "Tarocco" 3, Portocala "Moro" 12, Portocala "Valencia" 2, Mar "Golden Delicious" False, Mar "Golden" False, Mar "Golden" True]
nrFeliiSicilia ::[Fruct] -> Int
nrFeliiSicilia ((Mar _ _) : xs) = nrFeliiSicilia xs
nrFeliiSicilia [] = 0
nrFeliiSicilia ((Portocala soi felii) : xs)
    | soi == "Tarocco" || soi == "Moro" || soi == "Sanguinello" = felii + nrFeliiSicilia xs
    | otherwise = nrFeliiSicilia xs

nrMereViermi :: [Fruct] -> Int
nrMereViermi ((Mar _ tip) : xs)
    | tip == True = 1 + nrMereViermi xs
    | otherwise = nrMereViermi xs
nrMereViermi ((Portocala _ _) : xs) = nrMereViermi xs
nrMereViermi [] = 0

data Linie = L [Int]
    -- deriving Show
data Matrice = M [Linie]

verifica :: Matrice -> Int -> Bool
verifica (M m) nr = foldr (&&) True [sum x == nr | (L x) <- m]

verificaF :: Matrice -> Int -> Bool
verificaF (M m) nr = foldr (&&) True [(foldr (+) 0 x) == nr | (L x) <- m]

-- show matrice????

instance Show Linie where
    show (L l) = foldr (++) "" (map (\x ->( (show x)++" ")) l)

instance Show Matrice where
    show (M l) = foldr (++) "" (map (\x ->( (show x)++"\n")) l)

-- doarPozN (M [L[1,2,3], L[4,5], L[2,3,6,8], L[8,5,3]]) 3
-- doarPozN (M [L[1,2,-3], L[4,5], L[2,3,6,8], L[8,5,3]]) 3
doarPozN :: Matrice -> Int -> Bool
doarPozN (M m) nr = foldr (&&) True [ length x == length (filter (>0) x) | (L x) <- m, length x == nr]

-- yuck
-------------------------------------------------------------------------------------------------------------------------------

-- simulare

-- 1.a

fSim :: Char -> Bool
fSim ch
    | isAlpha ch == False = error "eroare"
    | ord(toLower(ch)) < ord('m') = True
    | otherwise = False

-- 1.b

gSim :: String -> Bool
gSim l = (length [x | x <- l, isAlpha x == True, fSim x == True]) > (length [x | x <- l, isAlpha x == True, fSim x == False])

--1.c
aux1c :: String -> Int
aux1c "" = 0
aux1c (x:xs)
    | isAlpha x == False = aux1c xs
    | fSim x == True = 1 + aux1c xs
    | otherwise = (-1) + aux1c xs

hSim :: String -> Bool
hSim "" = False
hSim l 
    | aux1c l > 0 = True
    | otherwise = False

-- 2.a
c :: [Int] -> [Int]
c l = [fst x | x <- l `zip` (tail l), fst x == snd x]

-- 2.b
d :: [Int] -> [Int]
aux2b [] = []
aux2b (x:xs)
    | fst x == snd x = fst x : aux2b xs
    |otherwise = aux2b xs
d l = aux2b (l `zip` tail l)

-- 2.c
prop_cd l = c l == d l


---------------------------------------------------------------------------------
--simulare but oops i did it again by britney spears is playing in the background

--1
--a
f1a :: Char -> Bool
f1a l 
    | isAlpha l == True && ord(toUpper l) > ord('M') = False
    | isAlpha l == True && ord(toUpper l) <= ord('M') = True
    | otherwise = error "eroare"

--b
f1b :: [Char] -> Bool
f1b l = length([x | x <- l, isAlpha x == True, f1a x == True]) > length([x | x <- l, isAlpha x == True, f1a x == False])

--c
f1caux :: [Char] -> Int
f1caux [] = 0
f1caux (l:xs)
    | isAlpha l == True && ord(toUpper l) > ord('M') = -1 + f1caux xs
    | isAlpha l == True && ord(toUpper l) <= ord('M') = 1 + f1caux xs
    | otherwise = f1caux xs

f1c :: [Char] -> Bool
f1c l = (f1caux l) > 0



--2

--a
f2a :: [Int] -> [Int]
f2a l = [fst x | x <- l `zip` (tail l), fst x == snd x]

--b
f2b :: [Int] -> [Int]
f2b [] = []
f2b [x] = []
f2b (x:y:xs)
    | x == y = x : f2b (y:xs)
    | otherwise = f2b (y:xs)

--c
testf2ab :: [Int] -> Bool
testf2ab l = (f2b l) == (f2a l) 

test1f2ab :: Bool
test1f2ab = (testf2ab [3,1,1,3,3,5]) && (f2b [3,1,1,3,3,5] == [1,3])

test2f2ab :: Bool
test2f2ab = (testf2ab [3,3,1,3,1]) && (f2b [3,3,1,3,1] == [3])

test3f2ab :: Bool
test3f2ab = (testf2ab [4,4,4]) && (f2b [42] == [])
-----------------------------------------------------------------------------------------------

-- 1.1
-- exemple: ".abc!12", "abcd", ".!()?"
sl11aux :: [(Char, Int)] -> [Int]
sl11aux [] = []
sl11aux (x:xs) 
    | (fst x) `elem` ".?!:,()" = snd x : sl11aux xs
    | otherwise = sl11aux xs

sl11 :: [Char] -> [Int]
sl11 l = sl11aux (l `zip` [0..])

-- 1.2
-- exemple "..ab..1..", "12345", "a"
sl12 :: [Char] -> [Int]
sl12 l = [ snd x | x <- l `zip` [0..], (fst x) `elem` ".?!:,()"]

-- 1.3
-- exemple "ana.ana", "..1()", ".?!:,()"
ordsl13 :: (Char, Int) -> Bool
ordsl13 x 
    | (fst x) `elem` ".?!:,()" = True
    | otherwise = False
sl13 :: [Char] -> [Int]
sl13 l = map snd (filter ordsl13 (l `zip` [0..]))

-- 1.4

-- 2
sl2 :: [Char] -> [Char]
sl2 [] = []
sl2 [x] = [x]
sl2 (x:xx:xs)
    | x == ' ' && xx == ' ' = sl2 (xx:xs)
    | x == ' ' && xx == '-' = sl2 (xx:xs)
    | x == '-' && xx == ' ' = x : sl2 (xs)
    | otherwise = x : sl2(xx:xs)

-- sl2aux :: [(Char, Char)] -> [Char]
-- sl2aux [] = []
-- sl2aux [x] = [(fst x), (snd x)]
-- sl2aux (x:xs)
--     | (fst x) == '-' && (snd x) == ' ' = sl2aux (xs)
--     | (fst x) == ' ' && (snd x) == '-' = snd x : sl2aux (xs)
--     | (fst x) /= ' ' && (snd x) == ' ' = (fst x) : sl2aux xs
--     | (fst x) == ' ' && (snd x) /= ' ' = (snd x) : sl2aux xs
--     | (fst x) /= ' ' && (snd x) /= ' ' = (fst x) : sl2aux (xs)
--     | otherwise = sl2aux xs

-- sl2 :: [Char] -> [Char]
-- sl2 l = sl2aux (l `zip` tail l)
-- sl2 :: [Char] -> [Char]
-- sl2 l = [ fst x | x <- l `zip` (tail l), (sl2aux x) == True]