--[ exercise 17.4 ]--

local count = 0

local mt = {__gc = function () count = count - 1 end}
local a = {}

for i = 1, 10000 do
    count = count + 1
    a[i] = setmetatable({}, mt)
end

collectgarbage()
print(collectgarbage('count') * 1024, count)

a = nil

--[[
The first time the collector detects that an object with a finalizer is not
reachable, the collector resurrects the object and queues it to be finalized.
Once its finalizer runs, Lua marks the object as finalized.
]]--

collectgarbage()
print(collectgarbage('count') * 1024, count)

--[[
The next time the collector detects that the object is not reachable, it
deletes the object.
]]--

collectgarbage()
print(collectgarbage('count') * 1024, count)
