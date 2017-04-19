--[ exercise 19.2 ]--

function weight (x)
    local s = 0
    while x ~= 0 do
        x = bit32.band(x, x - 1)
        s = s + 1
    end
    return s
end

print(weight(1))
print(weight(2))
print(weight(3))
print(weight(4))
print(weight(5))
print(weight(6))
print(weight(7))
print(weight(8))
