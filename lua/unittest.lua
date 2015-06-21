package.path=package.path .. ";./?.lua;" .. "../third_party/luaunit/?.lua"

local LuaUnit = require('luaunit')

AlgoTest = {} -- class

function AlgoTest:setUp()
	print("--- setUp --")
end

function AlgoTest:tearDown()
	print("--- tearDown --")
end

function AlgoTest:TestCase1()
	local a = 2
	local b = 3
	assert( a + b == 5)
	print("--- test 1 end")
end

function AlgoTest:TestCase2()
    local a = 2
    local b = 3
    assert( a + b == 4)
	print("--- test 2 end")
end

print(" --- Execute Unit test ---")
LuaUnit:run("AlgoTest");
print("Executed " .. LuaUnit.result.testCount .. " cases, failed " .. LuaUnit.result.failureCount)
return LuaUnit.result.failureCount

