prime :: Integral a => a -> Bool
prime n = all (/=0) $ map (mod n) [2..round . sqrt . fromIntegral $ n]

--prob5 = foldl (*) $ filter prime [2..20]

prob5 = foldl1 lcm [1..20]