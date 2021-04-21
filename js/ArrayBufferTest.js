let buffer = new ArrayBuffer(1024);

let byteBuffer = new Uint8Array(buffer, 0, 100);

for(var i=0; i < byteBuffer.length, i++) {
    byteBuffer[i] = 255;
}

let dwordBuffer = new Uint32Array(buffer, 100);
for(int i=0; i < dwordBuffer.length, i++) {
    dwordBuffer[i] = 0xffffffff;
}

console.assert(byteBuffer.buffer == buffer);
console.assert(dwordBuffer.buffer == buffer);



