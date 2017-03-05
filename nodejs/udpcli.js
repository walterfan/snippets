var PORT = 5060;
var HOST = '127.0.0.1';

var dgram = require('dgram');
var message = new Buffer('Hello world');

var client = dgram.createSocket('udp4');

//When the client socket receives the message event, handle it with this handler
client.on('message', function(message, remote){
	console.log("Received from server: " + message);
});
//
////Send a message [message variable] to the host and port configured in the first two lines,
////logging as appropriate.
client.send(message, 0, message.length, PORT, HOST, function(err, bytes) {
	if (err) throw err;
	console.log('UDP message sent to ' + HOST +':'+ PORT);
});
