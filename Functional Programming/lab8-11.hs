import Data.Maybe
import Data.List
import qualified Data.List as List
import Data.Char
import Prelude hiding (lookup)
import Test.QuickCheck
import Test.QuickCheck.Gen
import Data.Monoid
import Data.Semigroup (Max (..), Min (..))
import Data.Foldable (foldMap, foldr)
import Data.Char (isUpper)
-- lab 8
type Nume = String
data Prop
    = Var Nume
    | F
    | T
    | Not Prop
    | Prop :|: Prop
    | Prop :&: Prop
    | Prop :->: Prop
    | Prop :<->: Prop
    deriving (Eq, Read)
infixr 2 :|:
infixr 3 :&:
infixr 4 :->:
infixr 5 :<->:

-- 8.1
--1
-- (P v Q) ^ (P ^ Q)
p1 :: Prop
p1 = (Var "P" :|: Var "Q") :&: (Var "P" :&: Var "Q")

--2
-- (P v Q) ^ (~P ^ !Q)
p2 :: Prop
p2 = (Var "P" :|: Var "Q") :&: ((Not (Var "P")) :&: Var "Q")

-- 8.2
instance Show Prop where
    show (Var x) = x
    show F = "False"
    show T = "True"
    show (Not p) = "(~" ++ show p ++ ")"
    show (p :|: q) = "(" ++ show p ++ "|" ++ show q ++ ")"
    show (p :&: q) = "(" ++ show p ++ "&" ++ show q ++ ")"

test_ShowProp :: Bool
test_ShowProp = show(Not(Var "P") :&: Var "Q") == "((~P)&Q)"

-- 8.3
type Env 
    = [(Nume, Bool)]

impureLookup :: Eq a => a -> [(a,b)] -> b
impureLookup a = fromJust . lookup a

eval :: Prop -> Env -> Bool
eval (Var p) e = impureLookup p e
eval F e = False
eval T e = True
eval (Not p) e = not (eval p e)
eval (p :|: q) e = (eval p e) || (eval q e)
eval (p :&: q) e = (eval p e) && (eval q e)
eval (p :->: q) e = eval ((Not p) :|: q) e
eval (p :<->: q) e = eval ((p :->: q) :&: (q :->: p)) e

test_eval = eval (Var "P" :|: Var "Q") [("P", True), ("Q", False)]

-- 8.4
variableAux :: Prop -> [Nume]
variableAux (Var p) = [p]
variableAux T = []
variableAux F = []
variableAux (Not p) = variableAux p
variableAux (p :|: q) = variableAux p ++ variableAux q 
variableAux (p :&: q) = variableAux p ++ variableAux q
variableAux (p :->: q) = variableAux p ++ variableAux q
variableAux (p :<->: q) = variableAux p ++ variableAux q

variable :: Prop -> [Nume]
variable p = nub(variableAux p)
test_variable = variable(Not (Var "P") :&: Var "Q") == ["P", "Q"]

-- 8.5
envs :: [Nume] -> [Env]
envs [] = [[]]
envs (x:xs) = [(x, val) : e | val <- [False, True], e <- envs xs]

test_envs = 
    envs ["P", "Q"]
    ==
    [ [ ("P",False)
      , ("Q",False)
      ]
    , [ ("P",False)
      , ("Q",True)
      ]
    , [ ("P",True)
      , ("Q",False)
      ]
    , [ ("P",True)
      , ("Q",True)
      ]
    ]

-- 8.6
satisfiabila :: Prop -> Bool
satisfiabila p = foldr (||) False (map(\x -> eval p x) (envs(variable p)))

test_satisfiabila1 = satisfiabila (Not (Var "P") :&: Var "Q") == True
test_satisfiabila2 = satisfiabila (Not (Var "P") :&: Var "P") == False

-- 8.7
valida :: Prop -> Bool
valida p = foldr (&&) True (map(\x -> eval p x) (envs(variable p)))

test_valida1 = valida (Not (Var "P") :&: Var "Q") == False
test_valida2 = valida (Not (Var "P") :|: Var "P") == True

-- 8.8
--drive claudia nu scriu asa ceva

-- 8.10
echivalenta :: Prop -> Prop -> Bool
echivalenta p1 p2 = foldr (&&) True [eval (p1 :<->: p2) (e1 ++ e2) | e1 <- envs(variable p1), e2 <- envs (variable p2)]


test_echivalenta1 =
    True
    ==
    (Var "P" :&: Var "Q") `echivalenta` (Not (Not (Var "P") :|: Not (Var "Q")))
test_echivalenta2 =
    False
    ==
    (Var "P") `echivalenta` (Var "Q")
test_echivalenta3 =
    True
    ==
    (Var "R" :|: Not (Var "R")) `echivalenta` (Var "Q" :|: Not (Var "Q"))






---------------------------------------------------------------------------------------------------------------------------------------

-- Lab 9
-- 9.1.1
data Expr = Const Int -- integer constant
          | Expr :+: Expr -- addition
          | Expr :*: Expr -- multiplication
           deriving Eq
data Operation = Add | Mult deriving (Eq, Show)

data Tree = Lf Int -- leaf
          | Node Operation Tree Tree -- branch
           deriving (Eq, Show)

instance Show Expr where
    show (Const x) = show x
    show (p :+: q) = "(" ++ show p ++ "+" ++ show q ++ ")"
    show (p :*: q) = "(" ++ show p ++ "*" ++ show q ++ ")"

-- 9.1.2
evalExp :: Expr -> Int
evalExp (Const x) = x
evalExp (x :+: y) = evalExp x + evalExp y
evalExp (x :*: y) = evalExp x * evalExp y

exp1 = ((Const 2 :*: Const 3) :+: (Const 0 :*: Const 5))
exp2 = (Const 2 :*: (Const 3 :+: Const 4))
exp3 = (Const 4 :+: (Const 3 :*: Const 3))
exp4 = (((Const 1 :*: Const 2) :*: (Const 3 :+: Const 1)) :*: Const 2)

test11 = evalExp exp1 == 6
test12 = evalExp exp2 == 14
test13 = evalExp exp3 == 13
test14 = evalExp exp4 == 16

-- 9.1.3
evalArb :: Tree -> Int
evalArb (Lf x) = x
evalArb (Node Add st dr) = evalArb st + evalArb dr
evalArb (Node Mult st dr) = evalArb st * evalArb dr

arb1 = Node Add (Node Mult (Lf 2) (Lf 3)) (Node Mult (Lf 0)(Lf 5))
arb2 = Node Mult (Lf 2) (Node Add (Lf 3)(Lf 4))
arb3 = Node Add (Lf 4) (Node Mult (Lf 3)(Lf 3))
arb4 = Node Mult (Node Mult (Node Mult (Lf 1) (Lf 2)) (Node Add (Lf 3)(Lf 1))) (Lf 2)

test21 = evalArb arb1 == 6
test22 = evalArb arb2 == 14
test23 = evalArb arb3 == 13
test24 = evalArb arb4 == 16

expToArb :: Expr -> Tree
expToArb (Const x) = Lf x
expToArb (x :+: y) = Node Add (expToArb x) (expToArb y)
expToArb (x :*: y) = Node Mult (expToArb x) (expToArb y)

-- 9.1.5
class MySmallCheck a where
     smallValues :: [a]
     smallCheck :: ( a -> Bool ) -> Bool
     smallCheck prop = and [ prop x | x <- smallValues ]

instance MySmallCheck Expr where
     smallValues = [exp1, exp2, exp3, exp4]

checkExp :: Expr -> Bool
checkExp exp = evalArb (expToArb exp) == evalExp exp

--smallCheck checkExp

-- 9.2.1
type Key = Int

type Value = String

class Collection c where
  cempty :: c 
  csingleton :: Key ->  Value -> c 
  cinsert:: Key -> Value -> c  -> c 
  cdelete :: Key -> c -> c 
  clookup :: Key -> c -> Maybe Value
  ctoList :: c  -> [(Key, Value)]
  ckeys :: c  -> [Key]
  cvalues :: c  -> [Value]
  cfromList :: [(Key,Value)] -> c
  ckeys cc = [fst x | x <- ctoList cc]
  cvalues cc = [snd x | x <- ctoList cc]
  cfromList [] = cempty
  cfromList ((k,v) : l) = cinsert k v (cfromList l)

-- 9.2.2
newtype PairList 
    = PairList { getPairList :: [(Key, Value)] }

instance Collection PairList where
  cempty = PairList []
  csingleton k v = PairList [(k, v)]
  cinsert k v (PairList l) = PairList ((k, v) : filter ((/= k).fst) l)
  cdelete k (PairList l) = PairList(filter (\x -> fst x /= k) l)
  clookup k = List.lookup k . getPairList
  ctoList = getPairList


data SearchTree 
  = Empty
  | Nod
      SearchTree  -- elemente cu cheia mai mica 
      Key                    -- cheia elementului
      (Maybe Value)          -- valoarea elementului
      SearchTree  -- elemente cu cheia mai mare
   deriving Show

instance Collection SearchTree where
    cempty = Empty
    csingleton k v = Nod Empty k (Just v) Empty
    cinsert k v Empty = Nod Empty k (Just v) Empty
    cinsert k v (Nod t1 kk vv t2)
        | k == kk = Nod t1 kk (Just v) t2
        | k < kk = Nod (cinsert k v t1) kk vv t2
        | k > kk = Nod t1 kk vv (cinsert k v t2) 
    cdelete k Empty = Empty
    cdelete k (Nod t1 kk vv t2)
        | k == kk = Nod t1 kk Nothing t2
        | k < kk = Nod (cdelete k t1) kk vv t2
        | k > kk = Nod t1 kk vv (cdelete k t2)
    clookup k Empty = Nothing
    clookup k (Nod t1 kk vv t2)
        | k == kk = vv
        | k < kk = clookup k t1
        | k > kk = clookup k t2
    ctoList Empty = []
    ctoList (Nod t1 k (Just v) t2) = (ctoList t1) ++ [(k,v)] ++ (ctoList t2)
    ctoList (Nod t1 k Nothing t2) = ctoList t1 ++ [] ++ ctoList t2

--------------------------------------------------------------------------------------------------------------------------------------
-- Lab 10

-- 10.1
semigroupAssoc :: (Eq m, Semigroup m) => m -> m -> m -> Bool
semigroupAssoc a b c = (a <> (b <> c)) == ((a <> b) <> c)

monoidLeftIdentity   :: (Eq m, Monoid m) => m -> Bool
monoidLeftIdentity a = (mempty <> a) == a

monoidRightIdentity   :: (Eq m, Monoid m) => m -> Bool
monoidRightIdentity a = (a <> mempty) == a

data Trivial = Trivial
  deriving (Eq, Show)

instance Semigroup Trivial where
  _ <> _ = Trivial

instance Monoid Trivial where
  mempty  = Trivial

instance Arbitrary Trivial where
  arbitrary = elements[Trivial]

type TrivAssoc = Trivial -> Trivial -> Trivial -> Bool
type TrivId    = Trivial -> Bool

-- 10.2
newtype BoolConj = BoolConj {getBoolC :: Bool}
  deriving (Eq, Show)

instance Semigroup BoolConj where 
    BoolConj a <> BoolConj b = BoolConj (a && b)

instance Monoid BoolConj where 
    mempty = BoolConj True

instance Arbitrary BoolConj where
  arbitrary = MkGen ( \s i -> BoolConj  ((unGen arbitrary) s i))
type BoolConjAssoc = BoolConj -> BoolConj -> BoolConj -> Bool
type BoolConjId    = BoolConj -> Bool

-- 10.3
newtype BoolDisj = BoolDisj {getBoolD :: Bool}
  deriving (Eq, Read, Show)

instance Semigroup BoolDisj where 
    BoolDisj a <> BoolDisj b = BoolDisj (a || b)
instance Monoid BoolDisj where 
    mempty = BoolDisj False

instance Arbitrary BoolDisj where
   arbitrary = MkGen ( \s i -> BoolDisj  ((unGen arbitrary) s i))
  
type BoolDisjAssoc = BoolDisj -> BoolDisj -> BoolDisj -> Bool
type BoolDisjId    = BoolDisj -> Bool

newtype Identity a = Identity a
  deriving (Eq, Show)

instance Semigroup a => Semigroup (Identity a) where
    Identity a <> Identity b = Identity (a <> b)

instance Monoid a => Monoid (Identity a) where
    mempty = Identity mempty

instance Arbitrary a => Arbitrary (Identity a) where
    arbitrary = MkGen ( \s i -> Identity  ((unGen arbitrary) s i))
   
        
type IdentityAssoc a = Identity a -> Identity a -> Identity a -> Bool
type IdentityId    a = Identity a -> Bool

-- 10.4
data Two a b = Two a b
  deriving (Eq, Show)

instance (Semigroup a, Semigroup b) => Semigroup (Two a b) where 
    Two x y <> Two z t = Two (x <> z) (y <> t)

instance (Monoid a, Monoid b) => Monoid (Two a b) where 
    mempty = Two mempty mempty

instance (Arbitrary a, Arbitrary b) => Arbitrary (Two a b) where
  arbitrary = MkGen ( \s i -> Two ((unGen (arbitrary)) s i) ((unGen (arbitrary)) s i)) 
  

type TwoAssoc a b = Two a b -> Two a b -> Two a b -> Bool
type TwoId    a b = Two a b -> Bool

data Or a b = Fst a | Snd b
  deriving (Eq, Show)

instance  Semigroup (Or a b) where 
    Fst _ <> x =  x
    y     <> _ =  y
 
instance (Arbitrary a, Arbitrary b) => Arbitrary (Or a b) where
  arbitrary = oneof [MkGen ( \s i -> Fst ((unGen arbitrary) s i)), MkGen ( \s i -> Snd ((unGen arbitrary) s i))]
                     
type OrAssoc a b = Or a b -> Or a b -> Or a b -> Bool


---------------------------------------------------------------------

-- Lab 11

-- 11.1.1

newtype Cnt = Cnt {getCnt :: Int}
  deriving (Eq, Read, Show)

instance Semigroup Cnt where 
    Cnt a <> Cnt b = Cnt (a + b)
instance Monoid Cnt where 
    mempty = Cnt 0

data L a = L {getList :: [a]} deriving (Eq, Read, Show)

instance Semigroup (L a) where
    L x <> L y = L (x ++ y)
instance Monoid (L a) where
    mempty = L []

elem :: (Foldable t, Eq a) => a -> t a -> Bool
elem v l = getBoolD (foldMap (\x -> BoolDisj (x == v)) l)

null :: (Foldable t, Eq a) => t a -> Bool
null t = getBoolC (foldMap (\x -> BoolConj False) t)

length :: (Foldable t) => t a -> Int
length t = getCnt (foldMap (\x -> Cnt 1) t)

toList :: (Foldable t) => t a -> [a]
toList t = getList (foldMap (\x -> L [x]) t)


-- 11.1.2
data Constant a b = Constant b

instance Foldable (Constant a) where
  foldr func el (Constant b) = func b el 

data Two a b = Two a b

instance Foldable (Two a) where
  foldr func el (Two el1 el2) = func el2 el

data Three a b c = Three a b c

instance Foldable (Three a b) where
  foldr func el (Three el1 el2 el3) = func el3 el

data Three' a b = Three' a b b

instance Foldable (Three' a) where
  foldr func el (Three' el1 el2 el3) = func el2 (func el3 el)

data Four' a b = Four' a b b b

instance Foldable (Four' a) where
  foldr func el (Four' el1 el2 el3 el4) = func el2 (func el3 (func el4 el))

data GoatLord a = NoGoat | OneGoat a | MoreGoats (GoatLord a) (GoatLord a) (GoatLord a)

instance Foldable GoatLord where
  foldr func el NoGoat = el
  foldr func el (OneGoat val) = func val el
  foldr func el (MoreGoats g1 g2 g3) = foldr func (foldr func (foldr func el g1) g2) g3

-- 11.1.3
-- ??????????

-- 11.2.1
newtype Identity a = Identity a

instance Functor Identity where
  fmap func (Identity val) = Identity (func val)
 
data Pair a = Pair a a

instance Functor Pair where
  fmap func (Pair val1 val2) = Pair (func val1) (func val2)
 
-- scrieți instanță de Functor pentru tipul Two de mai sus
instance Functor (Two a) where
  fmap func (Two el1 el2) = Two el1 (func el2)

-- scrieți instanță de Functor pentru tipul Three de mai sus
instance Functor (Three a b) where
  fmap func (Three el1 el2 el3) = Three el1 el2 (func el3)

-- scrieți instanță de Functor pentru tipul Three' de mai sus
instance Functor (Three' a) where
  fmap func (Three' el1 el2 el3) = Three' el1 (func el2) (func el3)

data Four a b c d = Four a b c d

instance Functor (Four a b c) where
  fmap func (Four el1 el2 el3 el4) = Four el1 el2 el3 (func el4)
 
data Four'' a b = Four'' a a a b

instance Functor (Four'' a) where
  fmap func (Four'' el1 el2 el3 el4) = Four'' el1 el2 el3 (func el4)
 
-- scrieți o instanță de Functor penru tipul Constant de mai sus
instance Functor (Constant a) where
  fmap func (Constant el) = Constant (func el)

  data Quant a b = Finance | Desk a | Bloor b

  instance Functor (Quant a) where
    fmap func Finance = Finance
    fmap func (Desk a) = Desk a
    fmap func (Bloor el) = Bloor (func el)
   
  data K a b = K a
  
  newtype Flip f a b = Flip (f b a) deriving (Eq, Show)
    -- pentru Flip nu trebuie să faceți instanță
  
  instance Functor (Flip K a) where
    fmap = undefined