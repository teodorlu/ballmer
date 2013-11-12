evaluate :: Num a => [String] -> [a]
evaluate ("add":h1:h2:t) = ((read h1) + (read h2)):evaluate t

evaluate xs = [5, 5]

worker = do
	input <- getLine
	putStrLn $ show . evaluate . words $ input
	worker

main = worker
