--[ exercise 29.1 29.2 29.3 ]--

array = require "libarray"

arr1 = array.new(50)
arr2 = array.new(100)

arr1:set(1, true)
arr1:set(4, true)
arr1:set(32, true)

arr2:set(1, true)
arr2:set(8, true)
arr2:set(16, true)
arr2:set(32, true)
arr2:set(64, true)
arr2:set(90, true)

arr3 = arr1:union(arr2)
arr4 = arr1:intersection(arr2)

print(arr1:size(), arr1)
print(arr2:size(), arr2)
print(arr3:size(), arr3)
print(arr4:size(), arr4)
