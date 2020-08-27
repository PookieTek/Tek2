module Tool where

myLength :: [a] -> Int
myLength [] = 0
myLength (_ : next) = 1 + myLength next

isNum :: String -> Bool
isNum [] = True
isNum (a : as) | a >= '0' && a <= '9' = isNum as
               | otherwise = False

isFloat :: String -> Int -> Bool
isFloat [] nbpoint = True
isFloat (a : as) nbpoint | a == '.' && nbpoint == 0 = isFloat as 1
                         | a >= '0' && a <= '9' = isFloat as nbpoint
                         | otherwise = False

getFilePath :: [String] -> FilePath
getFilePath (elem : next) | myLength next > 0 = getFilePath next 
                          | otherwise = elem

readColor :: [String] -> Int
readColor (color : _) = read color::Int

readConvergence :: [String] -> Float
readConvergence (_ : convergence : _) = read convergence::Float