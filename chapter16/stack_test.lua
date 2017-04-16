--[ exercise 16.1 ]--

require 'stack'

s = Stack:new()
print(s:isempty())
print(s:top())
s:push(1)
print(s:isempty())
print(s:top())
s:push(2)
print(s:pop())
print(s:pop())
print(s:isempty())
