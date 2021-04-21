var color = "blue"; //global variable

changeColor();

console.log("color is " + color + ", background is " + background); //olor is red, background is undefined

if(true) {
    var background = "brown";
}

console.log("background is " + background); //background is brown

var arr = [];
for(var i = 0; i < 10; i ++) {
    arr.push(i);
}
console.log(arr); //arr conains numbers of 0 ~ 9
console.log(i); //i is 10

function changeColor() { //global function
    var anotherColor = "red"; //local variable in changeColor

    function swapColors() {
        var tempColor = anotherColor; //local variable in swapColor
        if(color !== tempColor) {
            color = tempColor;
        }
    }
    swapColors();
}

