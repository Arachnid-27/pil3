--[ exercise 8.1 ]--

function loadwithprefix (prefix, chunk)
    local flag = false
    local f = chunk
    if type(chunk) ~= 'function' then
        local flag = false
        f = function ()
                if not flag then
                    flag = true
                    return chunk
                end
                return nil
            end
    end
    return load(function ()
                    if not flag then
                        flag = true
                        return prefix
                    end
                    return f()
                end)
end

f = loadwithprefix('return ', '3 + 4 * 2')
print(f())
f = loadwithprefix('return ', io.read)
print(f())
