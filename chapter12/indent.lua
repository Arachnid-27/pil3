--[ exercise 12.1 ]--

function serialize (o, n)
    n = n or 2
    t = type(o)
    if t == 'number' then
        io.write(o)
    elseif t == 'string' then
        io.write(string.format('%q', o))
    elseif t == 'table' then
        io.write('{\n')
        for k, v in pairs(o) do
            io.write(string.rep(' ', n), k, ' = ')
            serialize(v, string.len(k) + n + 5)
            io.write(',\n')
        end
        io.write(string.rep(' ', n - 2), '}')
        if n == 2 then
            io.write('\n')
        end
    else
        error('cannot serialize a ' .. t)
    end
end

serialize{a=12, b='lua', {1, 2, 3}, key={c='program', d=20}}
