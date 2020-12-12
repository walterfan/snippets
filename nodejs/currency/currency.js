const rmbDollar = 0.15

function roundTwo(amount) {
    return Math.round(amount * 100)/100;
}

exports.rmbToDollar = rmb => roundTwo(rmb * rmbDollar);
exports.dollarToRmb = dollar => roundTwo(dollar/rmbDollar);

class Currency {
    constructor(rmbDollar) {
        this.rmbDollar = rmbDollar;
    }

    roundTwoDecimals(amount) {
        return Math.round(amount * 100)/100;
    }

    rmbToDollar(rmb) {
        return this.roundTwo(rmb * rmbDollar);
    } 
    dollarToRmb(dollar) { 
        return this.roundTwo(dollar/rmbDollar); 
    }
}

module.exports = Currency;