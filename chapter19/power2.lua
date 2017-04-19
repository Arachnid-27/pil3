--[ exercise 19.1 ]--

function power2 (x)
    return not bit32.btest(x, x - 1);
end

print(power2(1))
print(power2(2))
print(power2(3))
print(power2(4))
print(power2(5))
print(power2(6))
print(power2(7))
print(power2(8))
