--[ exercise 6.2 ]--

function newpoly(seq)
    return function(n)
               local i = #seq
               local s = 0
               local x = 1
               while i > 0 do
                   s = s + seq[i] * x
                   x = x * n
                   i = i - 1
               end
               return s
           end
end

f = newpoly({3, 0, 1})
print(f(0))
print(f(5))
print(f(10))
