const words = ["bytesReceived","bytesSent","timestamp","rtt","packetLoss"];

var result = words.filter(word => word !== "timestamp");
result.unshift('timestamp')
console.log(result);
