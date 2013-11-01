import Data.Char

main = do
	content <- readFile("words.txt")
	putStrLn $ show $ map numbers $ words $ nice content

numbers = map (\c -> (ord c) - (ord 'A') + 1)
nice c = filter (/='"') $ map repl c


repl ',' = ' '
repl  s  =  s
