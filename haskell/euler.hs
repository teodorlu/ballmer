import Data.Char

main = do
	content <- readFile("words.txt")
	putStrLn $ show $ length $ filter isTriangleNum $ map sum $ map numbers $ words $ nice content

numbers = map (\c -> (ord c) - (ord 'A') + 1)
nice c = filter (/='"') $ map repl c

repl ',' = ' '
repl  s  =  s

triangle n = n * (n-1) `quot` 2

isTriangleNumR n i
	| triangle i  > n = False
	| triangle i == n = True
	| otherwise		  = isTriangleNumR n (i+1)

isTriangleNum n = isTriangleNumR n 1