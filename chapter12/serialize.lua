--[ exercise 12.2 ]--

function serialize (o)
    n = n or 2
    t = type(o)
    if t == 'number' then
        io.write(o)
    elseif t == 'string' then
        io.write(string.format('%q', o))
    elseif t == 'table' then
        io.write('{\n')
        for k, v in pairs(o) do
            io.write('  [')
            serialize(k)
            io.write('] = ')
            serialize(v)
            io.write(',\n')
        end
        io.write('}\n')
    else
        error('cannot serialize a ' .. t)
    end
end

serialize{a=12, b='lua', key='another "one"'}
