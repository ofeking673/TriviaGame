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
        
        sock.send(msg.encode())
        print(sock.recv(1000, 0))


if __name__ == "__main__":
    main()
