const Bank = require('./bank');
const BankProxy = require('./bank_proxy');

const bank = new Bank();
const bankProxy = new BankProxy(bank);

bankProxy.deposit(4000);
bankProxy.withdraw(500);
bankProxy.deposit(300);
bankProxy.total();

proxyClass = {
    get: (target, key) => {
        console.log("read " + key + " through a proxy");
        return target[key];

    },
    set: (target, key, value) => {
        console.log("write " + key + " to " + value + " through a proxy");
        return target[key] = value;

    },
    apply: (target, thisArg, args) => {
        console.log("apply function  ", thisArg, args);
        console.time("-- begin --");
        const result = target.apply(thisArg, args);
        console.timeEnd("-- end --");
        return result;
    }
}
console.log("----------------------------------");
const bankAgent = new Proxy(bank, proxyClass);
bankAgent.cash  = 10000;
bankAgent.withdraw(8000);
var left = bankAgent.total();
console.log("left cash: ", left);