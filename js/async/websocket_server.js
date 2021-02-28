var WebSocket = require("ws");
var WebSocketServer = WebSocket.Server;
var port = 3001;
var ws = new WebSocketServer({
    port: port
});

console.log("websocket server started on " + port);
ws.on("connection", function(socket) {
    console.log("Got client connection");
});