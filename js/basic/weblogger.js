//var publicApi = (function(){ ... })();

var weblogger = (function(){
    var logCount = 0;

    var logInterface = {
        count: function() {
            return ++logCount;
        }
    }

    return logInterface;
})();