function countdown(seconds) {
    return new Promise(function(resolve, reject) {
        for(let i=seconds; i>=0; i--) {
            setTimeout(function() {
                if(i === 5) {
                    return reject(new Error("Reject the error for 5 seconds countdown"));
                }
                if(i>0) {
                    console.log(i + '...');
                } else {
                    resolve(console.log("Ready!"));
                }
            }, (seconds-i) * 1000);
        }
    })
}

countdown(3).then(
    function() {
        console.log("countdown completed successfully");
    },
    function(error) {
        console.log("countdown completed failed: " + error.message);
    }

);