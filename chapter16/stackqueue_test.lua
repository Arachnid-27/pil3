--[ exercise 16.2 ]--

require 'stackqueue'

s = StackQueue:new()
print(s:isempty())
s:push(1)
print(s:top())
s:insertbottom(2)
print(s:top())
print(s:pop())
print(s:top())
print(s:pop())
print(s:isempty())
