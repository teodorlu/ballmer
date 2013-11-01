

main = do
	content <- getLine
	putStrLn $ nice content

nice c = (filter okay) . (map repl) $ c

okay '"' = False
okay  s  = True
repl ',' = ' '
repl  s  =  s
