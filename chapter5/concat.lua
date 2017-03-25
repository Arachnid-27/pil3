--[ exercise 5.1 ]--

function concat (...)
    local rs = ''
    for _, v in ipairs{...} do
        rs = rs..v
    end
    return rs
end

print(concat('co', 'nc', 'at', '.l', 'ua'))
