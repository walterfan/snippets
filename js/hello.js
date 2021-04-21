console.log('hello typescript');
var key = 'Delay';
var ret1 = (key === 'jitter' || key === 'avgJitterDelay' || key === 'outBW' || key === 'rtt' || key === 'inBW');
var ret2 = ['jitter', 'outBW', 'inBW', 'rtt', 'avgJitterDelay'].indexOf(key) != -1;
console.log(ret1, ret2);

