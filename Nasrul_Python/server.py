from ast import Num
import socket
from tabnanny import check 

s = socket.socket()

print("Socket made")
PORT = 1234

s.bind(('localhost', PORT))
print("Socket binded")

s.listen(3)
print("Waiting for connection")

def checkPalindrome(num):
    return num[::-1]

while True:
    c, addr = s.accept()
    num = c.recv(1024).decode()
    print(addr)
    print(f"Number: {num}")

    if num == checkPalindrome(num):
        c.send(bytes(f"Server: {num} is a palindrome number", 'utf-8'))
    else:
        c.send(bytes(f"Server: {num} is not a palindrome number", 'utf-8'))