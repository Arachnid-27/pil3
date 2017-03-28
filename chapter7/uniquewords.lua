--[ exercise 7.3 ]--

function uniquewords ()
    local line = io.read()
    local pos = 1
    local table = {}
    return function ()
               while line do
                   local s, e = string.find(line, "%w+", pos)
                   if s then
                       local word = string.sub(line, s, e)
                       pos = e + 1
                       if not table[word] then
                           table[word] = 1
                           return string.sub(line, s, e)
                       end
                   else
                       line = io.read()
                       pos = 1
                  end
               end
               return nil
           end
end

for s in uniquewords() do
    print(s)
end
