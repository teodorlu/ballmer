prime n = not $ any (==0) $ map (mod n) [2.. n-1]
main = putStrLn $ show $ map prime [1.. 20]

