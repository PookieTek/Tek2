module Main where

import System.Environment
import ErrorHandler
import Tool

main = do {
    args <- getArgs;
    argsErrorHandler args;
    inputFile <- (readFile (getFilePath args));
    checkFile inputFile;
    putStrLn inputFile;
    return (0);
}
