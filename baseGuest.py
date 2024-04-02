import socket as s

def main():
    address = "127.0.0.1"
    port = 8826
    with s.socket(s.AF_INET, s.SOCK_STREAM) as sock:
        sock.connect((address, port))
        for i in range(5):
            sock.send("Hello".encode())
            data = sock.recv(10)
            print(data)



if __name__ == "__main__":
    main()
