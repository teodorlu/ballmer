commaToSpace ',' = ' '
commaToSpace x = x

checkTriangles l = map commaToSpace $ filter (=='"') l

main = do
	content <- readFile "words.txt"  
	putStrLn $ checkTriangles content
