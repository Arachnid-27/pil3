--[ exercise 9.1 ]--

function combine (arr, n, i, s, rs)
    n = n or #arr
    s = s or 1
    rs = rs or {}

    if n == 0 then
        local str = ''
        for _, v in ipairs(rs) do
            str = str .. v
        end
        coroutine.yield(str)
    else
        for i = i or 1, #arr - n + 1 do
            rs[s] = arr[i]
            combine(arr, n - 1, i + 1, s + 1, rs)
        end
    end
end

function combinations (arr, n)
    return coroutine.wrap(function () combine(arr, n) end)
end

for c in combinations({'a', 'b', 'c'}, 2) do
    print(c)
end
