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

function objectTest() {
        var peerId = 0;
        var midMap = {};
        var trnCvr = [{"mid": 0}, {"mid": 1}, {"mid": 2}];
        for (var i = 0; i < trnCvr.length; i++) {
            midMap[trnCvr[i].mid] = peerId++;
            weblog(trnCvr[i].mid, ": ", midMap[trnCvr[i].mid]);
            
        }
        for (var _peerId in midMap) {
            weblog("peerId: ", peerId, "_peerId:", _peerId);
        }
        weblog(midMap.hasOwnProperty(0), midMap.hasOwnProperty("0"));
        return midMap;
    
}