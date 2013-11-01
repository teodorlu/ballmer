

main = putStrLn $ show $ words $ nice "\"Test\",\"Test2\""

nice c = filter (/='"') $ map repl c

repl ',' = ' '
repl  s  =  s
