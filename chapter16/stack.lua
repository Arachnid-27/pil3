--[ exercise 16.1 ]--

Stack = {}
Stack.__index = Stack

function Stack:new ()
    local s = {}
    setmetatable(s, self)
    return s
end

function Stack:push (e)
    self[#self + 1] = e
end

function Stack:pop ()
    local e = self:top()
    if e then
        self[#self] = nil
    end
    return e
end

function Stack:top ()
    return self[#self]
end

function Stack:isempty ()
    return (#self == 0)
end
