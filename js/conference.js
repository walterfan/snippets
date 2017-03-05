function Shape() {}

Shape.prototype.getName = function() {
	return "Shape";
};

//---- Rectangle ----

function Rectangle() {
	Shape.call(this);
}

Rectangle.prototype = new Shape()

Rectangle.prototype.constructor=Rectangle;

Rectangle.prototype.getName = function() {
	return "Rectangle";
};

//---- Circle ----
function Circle() {
	Shape.call(this);

}

Circle.prototype = new Shape()

Circle.prototype.constructor=Circle;

Circle.prototype.getName = function() {
	return "Circle";
};
