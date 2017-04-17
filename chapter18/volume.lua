--[ exercise 18.2 ]--

function volume (height, angle)
    local r = height / (math.tan(math.rad(angle)))
    return math.pi * r * r * height / 3
end

print(volume(1, 45))
