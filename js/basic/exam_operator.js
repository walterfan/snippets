var a = "10";
var b = 10;
var c = null;
console.log(c == undefined); //true
console.log(a == b); //true
console.log(a === b); //false



console.log(typeof a);//string
console.log(typeof !!a, !!a)//boolean, true

console.log(c || 20);//20
console.log(c && 20);//null