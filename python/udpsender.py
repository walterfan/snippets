import socket
port = 12345
host = "localhost"
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.sendto("waltertest", (host, port))
