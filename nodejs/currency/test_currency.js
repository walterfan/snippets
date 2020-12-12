const currency = require('./currency');

console.log('50 rmb equals this amount of US dollars:')
console.log(currency.rmbToDollar(50));

console.log('30 dollars equals this amount of rmb:')
console.log(currency.dollarToRmb(30));