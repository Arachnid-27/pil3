--[ exercise 7.1 ]--

function fromto (n, m)
    return function (last, cur)
               if cur == last then
                   return nil
               else
                   return cur + 1
               end
           end, m, n - 1
end

for i in fromto(1, 10) do
    print(i)
end
