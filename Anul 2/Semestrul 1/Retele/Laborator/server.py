import socket
import struct
import os
import random
import string
import sys

def recv_short(data):
    return struct.unpack(">h", data)[0]

def recv_string(data):
    return data.decode()

def send_short(data):
    return struct.pack(">h", data)

def send_string(data):
    return data.encode()

def send_char(data):
    return struct.pack(">h", ord(data))

def main():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind(("127.0.0.1", 8888))

    s.listen(5)
    nr = 0
    while 1:
        conn1, addr1 = s.accept()

        print("Clientul 1 " + str(addr1) + " s-a inregistrat!!1!")

        conn2, addr2 = s.accept()

        print("Clientul 2 " + str(addr2) + " s-a inregistrat!!1!")

        nr += 1
        if os.fork() == 0:
            random_letter = random.choice(string.ascii_letters)[0]
            conn1.send(send_short(nr))
            conn2.send(send_short(nr))
            conn1.send(send_short(1))
            conn2.send(send_short(2))

            conn1.send(send_char(random_letter[0]))

            lungime1 = recv_short(conn1.recv(2))
            l1 = recv_string(conn1.recv(lungime1))
            jucator_castigator = 0

            ok = True

            if l1[0] != random_letter:
                ok = False
                conn2.send(send_short(-1))
                conn1.send(send_short(-1))
                jucator_castigator = 2
            while ok:
                conn2.send(send_short(lungime1))
                conn2.send(send_string(l1))

                lungime2 = recv_short(conn2.recv(2))
                l2 = recv_string(conn2.recv(lungime2))

                if len(l2) < 2 or l1[-2] != l2[0] or l1[-1] != l2[1]:
                    ok = False
                    jucator_castigator = 1
                    conn1.send(send_short(-1))
                    conn2.send(send_short(-1))
                    break

                conn1.send(send_short(lungime2))
                conn1.send(send_string(l2))

                lungime1 = recv_short(conn1.recv(2))
                l1 = recv_string(conn1.recv(lungime1))

                if len(l1) < 2 or l2[-1] != l1[1] or l2[-2] != l1[0]:
                    ok = False
                    jucator_castigator = 2
                    conn1.send(send_short(-1))
                    conn2.send(send_short(-1))

            conn1.send(send_short(jucator_castigator))
            conn2.send(send_short(jucator_castigator))

            conn1.close()
            conn2.close()
            sys.exit()
    s.close()

if __name__ == "__main__":
    main()
