--[ exercise 12.4 ]--

function serialize (o)
    t = type(o)
    if t == 'number' then
        io.write(o)
    elseif t == 'string' then
        io.write(string.format('%q', o))
    elseif t == 'table' then
        io.write('{\n')
        for k, v in pairs(o) do
            if (type(k) == 'number') then
                io.write('  ', v)
            else
                io.write('  [')
                serialize(k)
                io.write('] = ')
                serialize(v)
            end
            io.write(',\n')
        end
        io.write('}\n')
    else
        error('cannot serialize a ' .. t)
    end
end

serialize{a=12, b='lua', key='another "one"', 14, 15, 16}
