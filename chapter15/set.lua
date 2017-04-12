--[ exercise 15.1 ]--

local ipairs = ipairs
local pairs = pairs;
local concat = table.concat;

local _ENV = {}

function new (l)
    local set = {}
    for _, v in ipairs(l) do set[v] = true end
    return set
end

function union (a, b)
    local res = new{}
    for k in pairs(a) do res[k] = true end
    for k in pairs(b) do res[k] = true end
    return res
end

function intersection (a, b)
    local res = new{}
    for k in pairs(a) do
        res[k] = b[k]
    end
    return res
end

function tostring (set)
    local l = {}
    for e in pairs(set) do
        l[#l + 1] = e
    end
    return '{' .. concat(l, ',') .. '}'
end

return _ENV
