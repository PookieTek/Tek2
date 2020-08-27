module Main where

import System.Environment
import System.Exit
import Control.Monad
import Error
import Rule30
import Rule90
import Rule110
import Data.Char

getVal :: [String] -> String -> IO Int
defaultVal :: String -> IO Int
isNum :: String -> Bool

isNum a = all isDigit a;

defaultVal a = do {
    if a == "--rule"
        then return 0;
    else if a == "--start"
        then return 0;
    else if a == "--lines"
        then return 1234567891;
    else if a == "--window"
        then return 80;
    else if a == "--move"
        then return 0;
    else return 0;
}

checkError r s l w m = do {
    if r /= 30 && r /= 90 && r /= 110
        then raiseError "Please, Provide Rule (30, 90, 110)"
    else if s < 0
        then raiseError "Invalid Start (>= 0)" 
    else if l < 0
        then raiseError "Invalid Line (>= 0)"
    else if w <= 0
        then raiseError "Invalid Window (> 0)"
    else if (l > 150 && l /= 1234567891) || w > 1000 || s > 140 || m > 500
        then raiseError "Prevent Timed Out"
    else
        return "ok";
}

parse xs = do {
    if length xs < 2 
        then raiseError "Invalid Arguments";
    else return []
}

getVal [] a = do
    return 0

getVal (x:y:zs) a = do {
    if a == x
        then do {
            if isNum y == False && a /= "--move"
                then raiseError "Invalid Params";
            else return (read y::Int)
        }
    else if null x
        then (defaultVal a);
    else if null y
        then (defaultVal a);
    else if null zs
        then (defaultVal a);
    else if a /= x
        then getVal (y:zs) a
    else defaultVal a;
}

sendRule r s l w m = do {
    if r == 30
        then rule30 r s l w m;
    else if r == 90
        then rule90 r s l w m;
    else if r == 110
        then rule110 r s l w m;
    else return ()
}

main = do {
    a <- getArgs;
    parse a;
    rule <- getVal a "--rule";
    start <- getVal a "--start";
    lines <- getVal a "--lines";
    window <- getVal a "--window";
    move <- getVal a "--move";
    checkError rule start lines window move;
    sendRule rule start lines window move;
}