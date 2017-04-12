--[ exercise 15.1 ]--

set = require 'set'
s1 = set.new{10, 20, 30, 50}
s2 = set.new{40, 60}
s3 = set.union(s1, s2)
print(set.tostring(s3))
