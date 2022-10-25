import socket
client = socket.socket()
PORT = 1234

client.connect(('localhost', PORT))
num = input('Enter the string to be checked\n')
num = str(num)

client.send(bytes(num, 'utf-8'))

res = client.recv(1024).decode()
print(res)