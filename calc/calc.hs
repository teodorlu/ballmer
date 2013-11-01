evaluate :: Num a => [String] -> [a]
evaluate ("add":xs) = h + t
	where rest@(h:t) = evaluate xs

evaluate xs = [5, 5]

worker = do
	input <- getLine
	putStrLn $ show . evaluate . words $ input
	worker

main = worker
