
import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

sock.connect(("127.0.0.1",12345))

while True:
  data_send = input(">")
  if data_send == "stop":
    break
  sock.sendall(data_send.encode() + b'\r\n')

  print(f"{sock.recv(1024)!r}")

sock.close()