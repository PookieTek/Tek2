module Error where

import System.Environment
import System.Exit

raiseError a = do {
    print a;
    exitWith(ExitFailure 84)
}