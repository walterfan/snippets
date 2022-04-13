function testSetTimeout(count, delay) {
    for(var i =0; i < count; i++){
        setTimeout(() => console.log(i), delay);
    }
    
    for(let j =0; j < count; j++){
        setTimeout(() => console.log(j), delay);
    }
}