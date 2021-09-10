const expect = require('chai').expect;
// import time_util file
const time_util = require('../time_util');
describe('time_util.js tests', () => {
    describe('time_util.add() Test', () => {
        it('should equal 2', () => {
            const result = time_util.add(1, 1);
            expect(result).to.equal(2);
        });
        it('should equal 4', () => {
            const result = time_util.add(2, 2);
            expect(result).to.equal(4);
        });
    });
    
    describe('time_util.multiply() Test', () => {
        it('should equal 3', () => {
            const result = time_util.multiply(3, 1);
            expect(result).to.equal(3);
        });
        it('should equal 10', () => {
            const result = time_util.multiply(5, 2);
            expect(result).to.equal(10);
        });
    });
    describe('time_util.toTimeFormat() Test', () => {
        it('should equal 03:04:05:123', () => {
            const result = time_util.toTimeFormat("30405.123");
            console.log("result=", result);
            expect(result).to.equal("03:04:05.123");
        });
        
    });
    
});
