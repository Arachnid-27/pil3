--[ exercise 7.2 ]--

function stepfromto (n, m, s)
    return function (state, cur)
               if cur + state.step > state.last then
                   return nil
               else
                   return cur + state.step
               end
           end, {last = m, step = s}, n - s
end

for i in stepfromto(1, 10, 2) do
    print(i)
end
