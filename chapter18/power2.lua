--[ exercise 18.1 ]--

function power2 (x)
    local n = math.log(x, 2)
    return math.ceil(n) == n
end

print(power2(1))
print(power2(2))
print(power2(3))
print(power2(4))
print(power2(5))
print(power2(6))
print(power2(7))
print(power2(8))
