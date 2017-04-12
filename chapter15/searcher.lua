--[ exercise 15.3 ]--

function searcher (filename)
    local max
    local index
    local path = {}

    index = 1
    for p in string.gmatch(package.path, '([^;]+)') do
        path[index] = p
        index = index + 2
    end
    max = index

    index = 2
    for p in string.gmatch(package.cpath, '([^;]+)') do
        path[index] = p
        index = index + 2
    end
    max = (index > max) and index or max

    for index = 1, max do
        if path[index] then
            s = package.searchpath(filename, path[index])

            if s then
                if index % 2 == 1 then
                    return loadfile(s)
                else
                    return package.loadlib(s)
                end
            end
        end
    end
end

print(searcher('set')())
