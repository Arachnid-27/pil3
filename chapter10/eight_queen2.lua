--[ exercise 10.2 ]--

local N = 8

local function isplaceok (a, n, c)
    for i = 1, n - 1 do
        if (a[i] == c) or
           (n - i == c - a[i]) or
           (n - i == a[i] - c) then
           return false
        end
    end
    return true
end

local function printsolution (a)
    for i = 1, N do
        for j = 1, N do
            io.write(a[i] == j and 'x' or '-', '')
        end
        io.write('\n')
    end
    io.write('\n')
end

local function isnumberok (a, n, c)
    for i = 1, n - 1 do
        if a[i] == c then
            return false
        end
    end
    return true
end

local function permutation (a, n)
    if n > N then
        coroutine.yield(a)
    else
        for c = 1, N do
            if isnumberok(a, n, c) then
                a[n] = c
                permutation(a, n + 1)
            end
        end
    end
end

local function permutations (a, n)
    return coroutine.wrap(function () permutation(a, n) end)
end

local function ispermutationok (a)
    for i = 1, N do
        if not isplaceok(a, i, a[i]) then 
            return false
        end
    end
    return true
end

for a in permutations({}, 1) do
    if ispermutationok(a) then
        printsolution(a)
    end
end
