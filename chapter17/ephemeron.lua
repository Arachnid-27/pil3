--[ exercise 17.1 ]--

et = {}
setmetatable(et, {__mode = 'k'})
key = {}
et[key] = function () return key end
key = nil

for k in pairs(et) do
    print(k)
end
collectgarbage('collect')
for k in pairs(et) do
    print(k)
end
