

main = do
	content <- readFile "words.txt"
	putStrLn $ show $ words $ nice content

nice c = (filter okay) . (map repl) $ c

okay '"' = False
okay  s  = True
repl ',' = ' '
repl  s  =  s
