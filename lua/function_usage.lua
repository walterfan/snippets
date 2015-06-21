--[[
    Lua function support multi return values and variable number paramters	
--]]
package.path = package.path .. ";./?.lua"

require "base_util"

function trim_string(str)
	return (s:gsub("^%s*(.-)%s*$", "%1"))
end

-- trim whitespace from both ends of string
function trim(s)
   return s:find'^%s*$' and '' or s:match'^%s*(.*%S)'
end
  
-- trim whitespace from left end of string
function trim_left(s)
   return s:match'^%s*(.*)'
end
   
-- trim whitespace from right end of string
function trim_right(s)
   return s:find'^%s*$' and '' or s:match'^(.*%S)'
end


function merge_string(...)
    local strRet = '';
    local t={...}
	for i, v in ipairs(t) do
		strRet = strRet .. v
	end
    return strRet;
end

function split_string(d, p)
  local t={}
  for i in string.gmatch(d,p) do
    table.insert(t, i)
  end
  return t
end

function divide_string(str, sep)
    local i, j = string.find(str, sep)
    return string.sub(str, 1, i-1), string.sub(str, j+1,string.len(str))
end

local str = "Lua is a powerful, fast, lightweight, embeddable scripting language."
local ret = split_string(str, "%S+")
print_r(ret)
print(merge_string("one ", "tow ","three"))
local s1, s2 = divide_string("tom and jerry", "and")
print("s1=" .. trim(s1) ..", s2=" ..trim(s2))

