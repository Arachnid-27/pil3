--[ exercise 18.5 ]--

function shuffle (a)
    for i = 1, #a do
        local t = math.random(i)
        a[i], a[t] = a[t], a[i]
    end
end

t = {1, 2, 3, 4, 5, 6, 7, 8}
shuffle(t)
for _, v in ipairs(t) do
    print(v)
end
