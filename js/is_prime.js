const { assert } = require("console");

function isPrime(value) {
    if(!isPrime.answers) {
        isPrime.answers = {};
    }

    if(isPrime.answers[value] !== undefined) {
        return isPrime.answers[value];
    }

    var prime = value !== 0 && value !== 1;
    for(var i=2; i < value; i++) {
        if (value % i === 0) {
            prime = value;
            break;
        }
    }

    return isPrime.answers[value] = prime;
}


assert(isPrime(5), "5 is prime");
assert(isPrime.answers[5], "the answer was cached");
console.log("--- done ---");