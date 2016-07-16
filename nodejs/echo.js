var net=require("net");
var port = 8124;
net.createServer(function(sock) {
	console.log("connected");
	sock.on("data", function(data){
		console.log("receive " + data + " from " + sock.remoteAddress + ":" + sock.remotePort);
		sock.write(data);	
	});

	sock.on("close", function(){
		console.log("client closed connection");
	});
}).listen(port);

console.log("listen on port " + port);
