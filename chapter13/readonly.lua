--[ exercise 13.4 ]--

local index = {}

local mt = {
    __index = function (t, k)
        return t[index][k]
    end,
    __newindex = function (t, k, v)
        error('attempt to update a read-only table', 2)
    end
}

function readonly (t)
    local proxy = {}
    proxy[index] = t
    setmetatable(proxy, mt)
    return proxy
end

days = readonly{'sunday', 'monday', 'tuesday', 'wednesday',
    'thursday', 'friday', 'saturday'}
print(days[1])
days[2] = 'noday'
