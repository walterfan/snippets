--[[
a closure is a function plus all it needs to access its upvalues correctly. 

Closures provide a valuable tool in many contexts. 
As we have seen, they are useful as arguments to higher-order functions such as sort. 

Closures are valuable for functions that build other functions too, like the newCounter example;

Closures are useful for callback functions too


--]]

function newCounter ()
   local i = 0
   return function ()   -- anonymous function
       i = i + 1
       return i
    end
end
    
c1 = newCounter()
print(c1())  --> 1
print(c1())  --> 2

c2 = newCounter()
print(c2())  --> 1
print(c1())  --> 3
print(c2())  --> 2

--redefine math.sin with new version, keep the old version in a private variable; the only way to access it is through the new version. 
do
   local oldSin = math.sin
   local k = math.pi/180
   math.sin = function (x)
       return oldSin(x*k)
   end
end
