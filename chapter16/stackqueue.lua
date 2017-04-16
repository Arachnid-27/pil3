--[ exercise 16.2 ]--

require 'stack'

StackQueue = Stack:new()
StackQueue.bottom = 1
StackQueue.__index = StackQueue

local super = getmetatable(StackQueue)

function StackQueue:new ()
    local s = {}
    setmetatable(s, self)
    return s
end

function StackQueue:insertbottom (e)
    self.bottom = self.bottom - 1
    self[self.bottom] = e
end

function StackQueue:pop ()
    if #self ~= 0 then
        return super.pop(self)
    elseif self.bottom ~= 1 then
        print('you can not pop it!')
        return nil
    end
end

function StackQueue:top ()
    if #self ~= 0 then
        return super.top(self)
    elseif self.bottom ~= 1 then
        print('you can not get it!')
        return nil
    end
end

function StackQueue:isempty ()
    return super.isempty(self) and (self.bottom == 1)
end
