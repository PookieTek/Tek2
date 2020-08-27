module ErrorHandler where

import Tool
import System.Exit
import System.IO

errorPrint :: String -> IO Int
errorPrint str = do {
    putStrLn str;
    exitWith (ExitFailure 84);
    return (84);
}

errorPrintUsage :: IO Int
errorPrintUsage = do {
    putStrLn "USAGE: ./imageCompressor n e IN\n";
    putStrLn "\tn\tnumber of colors in the final image";
    putStrLn "\te\tconvergence limit";
    putStrLn "\tIN\tpath to the file containing the colors of the pixels";
    exitWith (ExitFailure 84);
    return (84);
}

checkNumberColors :: [String] -> Bool
checkNumberColors (colors : next) | isNum colors == True = True
                                  | otherwise = False

checkConvergenceLimit :: [String] -> Bool
checkConvergenceLimit (colors : convergence : next) | isFloat convergence 0 == True = True
                                                    | otherwise = False

argsErrorHandler :: [String] -> IO Int
argsErrorHandler args | myLength args /= 3 = errorPrintUsage
                      | checkNumberColors args == False || readColor args < 1 = errorPrint "Error\nBad Input\nThe Number Of Colors Must Be A Positive Number"
                      | checkConvergenceLimit args == False || readConvergence args <= 0 = errorPrint "Error\nBad Input\nConvergence Limit Must Be A Positive Float"
                      | otherwise = do return (0)

checkFile :: String -> IO Int
checkFile input | checkChar input == False = errorPrint "Error\nBad File\nThe File Contains A Forbidden Character"
                | otherwise = do return (0)

checkChar :: String -> Bool
checkChar [] = True
checkChar (elem : next) | elem >= '0' && elem <= '9' = checkChar next
                        | elem == '\n' = checkChar next
                        | elem == ' ' = checkChar next
                        | elem == ',' = checkChar next
                        | elem == '(' || elem == ')' = checkChar next
                        | otherwise = False