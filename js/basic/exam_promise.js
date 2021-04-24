var assert = require('assert');

const { resolve } = require("path");

function myDisplayer(some) {
    console.log("dispatcher: " , some);
}

let myPromise = new Promise(function(myResolve, myReject) {
    let x = 0;

    // The producing code (this may take some time)

    if (x == 0) {
        myResolve("OK");
    } else {
        myReject("Error");
    }
});

myPromise.then(
    function(value) {myDisplayer(value);},
    function(error) {myDisplayer(error);}
);


let start = new Date().getTime();
let log = (msg) => console.log(msg + " @ttl: " + (new Date().getTime() - start));

() {
log("mark 1");
let p = new Promise((res, rej)=> {
		log("mark 2");
		res("mark 5");
		log("mark 3");
	})
	
p.then((value)=>log(value));
log("mark 4");
}

var statsPromise = new Promise((resolve, reject) => {

    log("startPromise created");

    setTimeout(() => {
        log("To resolve startsPromise");
        resolve("done");

    }, 500);
});

statsPromise.then(value => {
    log("startsPromise resolved: " + value)
}); 
log("--- end ---");