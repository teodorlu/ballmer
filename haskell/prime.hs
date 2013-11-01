prime n = not $ any (==0) $ map (mod (round n)) [2.. round (sqrt $ (n-1))]
main = putStrLn $ show $ zip [1..] $ map prime [1.. 20]
