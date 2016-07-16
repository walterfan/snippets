var http = require("http");
var fs = require("fs");
var port = 10080;

http.createServer(function(req, res) {
	//var query = require("url").parse(req, url).query;
	//console.log("query:" + query);

	fs.readFile("message.json", "utf8", function(err, data) {
		res.writeHead(200, {"Content-Type": "text/json"});

		if(err)
			res.write("{\"error\": \"could not find or opoen file for reading\"}");
		else
			res.write(data);
		
		res.end();
	});

	
}).listen(port, function() {
	console.log("Server running on " + port);
});
