function objectKeyTypeTest() {
    'use strict'
    var key = 4;
    var testObj = { "1": "a", "2": "b", "3": "c"};
    testObj[1] = 'a1';
    testObj[key] = 'd';
    weblog(testObj[4], testObj['4']);
    weblog(testObj["1"], testObj['1'], testObj[1])
   
    

    const arr = ['a', 5, true];
    
    weblog("key of object ", Object.keys(arr));
    for(const key of Object.keys(arr)) {
        weblog(typeof key, key, );
    }

    weblog("key of arr ", arr);
    for(const key of arr.keys()) {
        weblog(typeof key, key);
    }
}

function regexTest() {
    weblog("/2/.test('2.0'):", /2/.test('2.0'));
    weblog("/shar/.test('share'):", /shar/.test('share'));
    weblog("/share/.test('sharing'):", /shar/.test('sharing'));
}