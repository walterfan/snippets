const time_util = {};
time_util.add = (num1, num2) => num1 + num2;
time_util.multiply = (num1, num2) => num1 * num2;

time_util.toTimeFormat = function(timeStr) {
    var pieces = timeStr.split('.');
    if(pieces.length < 2) return pieces[0];
    var hhmmss = pieces[0];
    var ms = pieces[1];
    while(hhmmss.length < 6) {
        hhmmss = '0' + hhmmss;
    }
    return hhmmss.substr(0,2) + ":" + hhmmss.substr(2,2) + ":" + hhmmss.substr(4, 2) + "." + ms;

}


module.exports = time_util;
