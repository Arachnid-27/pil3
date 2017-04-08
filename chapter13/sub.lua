--[ exercise 13.1 ]--

Set = {}

function Set.sub (a, b)
    local s = Set.new{}
    for k in pairs(a) do
        if not b[k] then
            s[k] = true
        end
    end
    return s
end

function Set.tostring (s)
    local l = {}
    for k in pairs(s) do
        l[#l + 1] = k
    end
    return '{' .. table.concat(l, ', ') .. '}'
end

local mt = {
    __sub = Set.sub,
    __tostring = Set.tostring
}

function Set.new (l)
    local set = {}
    setmetatable(set, mt)
    for _, v in ipairs(l) do set[v] = true end
    return set
end

s1 = Set.new{10, 20, 30}
s2 = Set.new{10, 40}
print(s1 - s2)
