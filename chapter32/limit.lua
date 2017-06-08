--[ exercise 32.1 ]--

local limit = require "liblimit"
print(limit.getused(), limit.getlimit())
limit.setlimit(65535)
print(limit.getused(), limit.getlimit())
t = {}
print(limit.getused(), limit.getlimit())
