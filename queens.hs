import System.Environment(getArgs)

placeQueens :: [Integer] -> [Integer] -> [[Integer]]
placeQueens placed [] 		 = [placed]
placeQueens placed remaining =
	let
		f placed choice remaining
			| illegalChoice placed choice = []
			| otherwise = (placeQueens (choice:placed) remaining)
	in
		foldl1 (++) $ zipWith (f placed) remaining (without remaining)

-- Returns a list of lists without one of the elements
without xs = map (\el -> filter (/= el) xs) xs

properPlaceQueens list = map (take 4) (placeQueens [] list)

illegalChoice placed choice = (any (==choice) $ zipWith (+) placed [1..])
	|| (any (==choice) $ zipWith (+) placed [-1,-2..])

kQueens :: Integer -> [[Integer]]
kQueens n = placeQueens [] [1..n]

-- Finds the number of solutions for each board
solutions = map (length . kQueens) [1..]

main = do
	args <- getArgs
	putStrLn $ show $ kQueens (read $ head args)
