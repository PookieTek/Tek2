module Rule30 where

import System.Environment
import Control.Monad
import Error
import Data.Array

rule30 :: Int -> Int -> Int -> Int -> Int -> IO ()
initLine :: Int -> Int -> IO Int
arrInit :: String -> Int -> Int -> Int -> Int -> IO ()
nextLine :: String -> IO String
getCell :: String -> String -> Int -> Int -> Int -> Int -> IO String
getOneCell :: String -> String -> Int -> Int -> Int -> IO Int
intToIO :: Int -> Int -> IO Int
adaptWin :: Int -> Int
putSp :: Int -> IO ()
getCac :: String -> Int -> IO Int
setSp :: String -> String -> IO String
dispCell :: String -> Int -> Int -> Int -> IO ()
dispLine :: String -> Int -> Int -> Int -> IO ()

adaptWin a | a `mod` 2 == 0 = (a `div` 2)
            | otherwise = (a `div` 2) + 1

intToIO a b = do {
    return (a + b);
}


getOneCell a fol l m r = do {
    if ((l == 1 && m == 0 && r == 0) || (l == 0 && (m == 1 || r == 1)))
        then return 1;
    else return 0;
}

putSp a = do {
    if a > 0
        then do {
            putStr " ";
            putSp (a - 1);
        }
    else return ();
}

getCac (a:zs) l = do {
    if l < 0
        then return 0;
    else if l == 0
        then do {
            if a == '*'
                then return 1;
            else return 0;
        }
    else do {
        if (length zs) == 0
            then return 0;
        else do {
            res <- getCac zs (l - 1);
            return (res);
        }
    }
}

setSp a b = do {
    return (a ++ b);
}

getCell a fol l m r ln = do {
    if length fol == ln
        then do {
            return fol;
        }
    else do {
        res <- getOneCell a fol l m r;
        if res == 1
            then do {
                sp <- setSp fol "*";
                nr <- getCac a (length sp);
                res <- getCell a sp m r nr ln;
                return res;
            }
        else do {
            sp <- setSp fol " ";
            nr <- getCac a (length sp);
            res <- getCell a sp m r nr ln;
            return res;
        }
    }
}

nextLine a = do {
    fol <- getCell a "" 0 0 1 ((length a) + 2);
    return fol;
}

dispSp w = do {
    if w <= 0
        then do {
            return ();
        }
    else do {
        putStr " ";
        dispSp (w - 1);
    }
}

dispLine (a:zs) w lm l = do {
    if lm > 0
        then dispLine zs w (lm -1) (l -1)
    else if w > 0
        then do {
            putChar a;
            if l > 1
                then dispLine zs (w - 1) lm (l - 1);
            else return ();
        }
    else return ();
}

dispCell cell w m l = do {
    if (w >= l)
        then do {
            dispSp (m + (adaptWin (w - l)));
            putStr cell;
            dispSp ((w - l) `div` 2);
            putStrLn "";
        }
    else do {
        dispSp (m);
        dispLine cell w ((l - w) `div` 2) l;
        putStrLn "";
    }
}

arrInit cell line s w m = do {
    if s == 0
        then dispCell cell w m (length cell)
    else return ();
    if line > 1
        then do {
            fol <- nextLine cell;
            if s == 0
                then arrInit fol (line - 1) s w m;
            else arrInit fol (line - 1) (s - 1) w m;
        }
    else return ();
}

initLine s l = intToIO s l;

rule30 r s l w m  = do {
    line <- initLine s l;
    arrInit "*" line s w m;
}