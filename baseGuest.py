import socket as s
import json
import sys

def main():
    address = "127.0.0.1"
    port = 8826
    with s.socket(s.AF_INET, s.SOCK_STREAM) as sock:
        sock.connect((address, port))

        message = ""
        type = input("Login or signup? 0 or 1")
        message += type
        #{username: “user1”, password: “1234"}
        j = {}
        j['username'] = "user1"
        j['password'] = "1234"
        if type == '1':
            j['email'] = "email@gmail.com"

        message += str(len(json.dumps(j))).zfill(4)
        message += json.dumps(j)
        msg = ''.join(format(ord(x), '08b') for x in message)
        print(msg)
        binary = "00110000 00110000 00110000 00110100 00110001 01111011 00100010 01110101 01110011 01100101 01110010 01101110 01100001 01101101 01100101 00100010 00111010 00100000 00100010 01110101 01110011 01100101 01110010 00110001 00100010 00101100 00100000 00100010 01110000 01100001 01110011 01110011 01110111 01101111 01110010 01100100 00100010 00111010 00100000 00100010 00110001 00110010 00110011 00110100 00100010 01111101"
        print(binary == msg)
        print(message)
        sock.send(msg.encode())
        print(sock.recv(1000, 0))


if __name__ == "__main__":
    main()
