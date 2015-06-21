Object = {}

function Object:clone()
	local object = {}
	for k, v in pairs(self) do
		object[k]=v
	end

	setmetatable(object, {__index = self})
	return object;
end

function Object:new(...)
	local object = {}
	setmetatable(object, {__index = self})
	object:initialize(...)
	return object
end

function Object:initialize(...)

end

Class = Object:new()

Point = Class:new()

function Point:initialize(x, y)
    self.x = x
    self.y = y
end

function Point:magnitude()
    return math.sqrt(self.x^2 + self.y^2)
end

p = Point:new(3,4)
print(p:magnitude())

Point3D = Point:clone()

function Point3D:initialize(x, y, z)
    Point:initialize(x, y)
    self.z = z
end

function Point3D:magnitude()
    return math.sqrt(self.x^2 + self.y^2 + self.z^2)
end

p3d = Point3D:new(1,2,3)
print(p3d.x ..", " ..p3d.y ..", " ..p3d.z)

print(p3d:magnitude())


