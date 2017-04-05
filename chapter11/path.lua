--[ exercise 11.3 ]--

function name2node (graph, name)
    local node = graph[name]
    if not node then
        node = {name = name, arcs = {}}
        graph[name] = node
    end
    return node
end

function label2arc (graph, label)
    local arc = graph[label]
    if not label then
        arc = {label = label}
        graph[label] = arc
    end
    return arc
end

function readgraph ()
    local graph = {}
    for line in io.lines() do
        local namefrom, label, nameto = string.match(line, "(%S+)%s+(%d+)%s+(%S+)")
        local from = name2node(graph, namefrom)
        local to = name2node(graph, nameto)
        local arc = {label = label, node = to}
        from.arcs[arc] = true
    end
    return graph
end

function findpath (curr, to, path, visited)
    path = path or {}
    visited = visited or {}
    if visited[curr] then
        return nil
    end
    visited[curr] = true
    path[#path + 1] = curr
    if curr == to then
        return path
    end
    for arc in pairs(curr.arcs) do
        local p = findpath(arc.node, to, path, visited)
        if p then return p end
    end
    path[#path] = nil
end

function printpath (path)
    for i = 1, #path do
        print(path[i].name)
        if (i + 1 <= #path) then
            for arc in pairs(path[i].arcs) do
                if arc.node == path[i + 1] then print(arc.label) end
            end
        end
    end
end

g = readgraph()
a = name2node(g, 'a')
b = name2node(g, 'b')
p = findpath(a, b)
if p then printpath(p) end
