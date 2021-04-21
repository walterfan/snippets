function sortArgs(a, b, c) {
    //return Array.from(arguments).sort(function (a, b) { return a - b; });
    var args = Array.prototype.slice.call(arguments);
    return args.sort();
}


var retArr = sortArgs(5, 3, 7);
console.log(retArr);

retArr = sortArgs(5, 3, 7, 1, 9, 8);
console.log(retArr);