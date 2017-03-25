--[ exercise 5.3 ]--

function rest (...)
    return _rest(...)
end

function _rest (_, ...)
    return ...
end

print(rest(1, 2, 3, 4, 5))
