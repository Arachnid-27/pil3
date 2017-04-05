--[ exercise 11.1 ]--

Queue = {}

function Queue.new ()
    return {first = 0, last = 0}
end

function Queue.pushfirst (queue, value)
    queue.first = queue.first - 1
    queue[queue.first] = value 
end

function Queue.pushlast (queue, value)
    queue[queue.last] = value
    queue.last = queue.last + 1
end

function Queue.popfirst (queue)
    if queue.first == queue.last then error("queue is empty") end
    local value = queue[queue.first]
    queue[queue.first] = nil
    queue.first = queue.first + 1
    if queue.first == queue.last then
        queue.first = 0
        queue.last = 0
    end
    return value
end

function Queue.poplast (queue)
    if queue.first == queue.last then error("queue is empty") end
    queue.last = queue.last - 1
    local value = queue[queue.last]
    queue[queue.last] = nil
    if queue.first == queue.last then
        queue.first = 0
        queue.last = 0
    end
    return value
end

q = Queue.new()
print(q.first, q.last)
Queue.pushfirst(q, 1)
Queue.pushfirst(q, 1)
print(q.first, q.last)
Queue.poplast(q)
print(q.first, q.last)
Queue.poplast(q)
print(q.first, q.last)
