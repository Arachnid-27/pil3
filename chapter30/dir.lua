--[ exercise 30.1 ]--

local dir = require "libdir"
for item in dir.open(".") do
    print(item)
end
