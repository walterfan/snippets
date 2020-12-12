function print(value) {
    if(arguments.length < 2) {
        console.log(value);
        return;
    }
    let args = Array.from(arguments);
    console.log(args);
}

function printBoolean(value) {
    value? print(value, "=true"): print(value, "=false");
}


//this is context, "arguments" is parameter    



module.exports = {
    print: print,
    printBoolean: printBoolean
}