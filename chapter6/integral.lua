--[ exercise 6.1 ]--

function integral (f)        
    local n = 1e6
    return function (a, b)
               local s = 0
               local d = (b - a) / n
               local x = a
               for i = 1, n do
                   x = x + d
                   s = s + f(x) * d
               end
               return s
           end
end

f = integral(math.sin)
print(f(0, math.pi))
