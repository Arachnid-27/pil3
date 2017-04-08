--[ exercise 13.2 ]--

Set = {}

function Set.len (a, b)
    local c = 0
    for k in pairs(a) do
        c = c + 1
    end
    return c
end

local mt = {
    __len = Set.len,
}

function Set.new (l)
    local set = {}
    setmetatable(set, mt)
    for _, v in ipairs(l) do set[v] = true end
    return set
end

s1 = Set.new{}
s2 = Set.new{10, 20, 30}
print(#s1, #s2)

