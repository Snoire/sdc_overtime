#! /usr/bin/env lua

function values ()
    local i = 0
    return function () i = i + 1; return i end
end

v1 = values()
v2 = values()

print("v1: ", v1())
print("v2: ", v2())
print("v1: ", v1())
print("v1: ", v1())

