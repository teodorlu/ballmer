evaluate :: Num a => [String] -> [a]
evaluate ("add":xs) = ((read h1) + (read h2)):evaluate t
	where (h1:h2:t) = evaluate xs

evaluate xs = [5, 5]

worker = do
	input <- getLine
	putStrLn $ show . evaluate . words $ input
	worker

main = worker
