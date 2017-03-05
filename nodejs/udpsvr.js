var PORT = 5060;
var HOST = '127.0.0.1';

var dgram = require('dgram');
var server = dgram.createSocket('udp4');

server.on('listening', function () {
	    var address = server.address();
		console.log('UDP Server listening on ' + address.address + ":" + address.port);
});

server.on('message', function (message, remote) {
	    console.log(remote.address + ':' + remote.port +' - ' + message);

		var okBuffer = new Buffer("\000\242\203\200\000\001\000\001\000\023\000\000\004_sip\004_udp\002qa\005webex\003com\000\000!\000\001\300\f\000!\000\001\000\000\002X\000\030\000\000\000\000\023\304\003sip\002qa\005webex\003com\000\300>\000\002\000\001\000\000\001`\000\v\bhftans01\300>\300>\000\002\000\001\000\000\001`\000\f\thflabns05\300>\300>\000\002\000\001\000\000\001`\000\f\thflabns03\300>\300>\000\002\000\001\000\000\001`\000\t\006hfns02\300>\300>\000\002\000\001\000\000\001`\000\t\006hfqans\300>\300>\000\002\000\001\000\000\001`\000\t\006sjns01\300>\300>\000\002\000\001\000\000");
//		var okBuffer = new Buffer("waltertest")
		server.send(okBuffer, 0, okBuffer.length, remote.port, remote.address, function(err, bytes){
		if (err){
			throw err;
		}
	});
			//print out to the server's console that we've successfully sent the response to the client
		console.log("OK sent to client");
});

server.bind(PORT, HOST);

