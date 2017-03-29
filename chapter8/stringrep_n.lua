--[ exercise 8.3 ]--

function stringrep_n (s, n)
    local r = 'local r = "" '
    for i = 1, n do
       r = r .. 'r = r .. "' .. s .. '" '
    end
    r = r .. 'return r'
    return r
end

print(load(stringrep_n('a', 10))())
