evaluate :: Num a => [String] -> [a]
evaluate ("add":h1:h2:t) = ((read h1) + (read h2)):evaluate t

worker = do
	input <- getLine
	putStrLn $ show . evaluate . words $ input
	worker

main = worker
