#!/usr/bin/env python3
'''
client.py

Simple Python socket client example with threading

Copyright Simon D. Levy 2018

MIT License
'''

import socket
import sys
import threading

def talk(sock):

    while True:

        msg = input().encode('utf-8')  # Python3 requires encoding

        if len(msg) < 1:                   # Simple way of quitting on CTRL-C
            break

        try:
            sock.send(msg)

        except:
            break


if __name__ == '__main__':

    if len(sys.argv) < 3:
        print('Usage:   %s <HOST> <PORT>' % sys.argv[0])
        print('Example: %s 137.113.118.3 20000' % sys.argv[0])
        exit(1)

    host = sys.argv[1]
    port = int(sys.argv[2])

    sock = socket.socket()

    try:
        sock.connect((host, port)) # Note tuple!
    except socket.error: 
        print('connect() failed with code ' + str(msg[0]) + ': ' + msg[1])
        exit(1)

    print('Connected to server %s:%d' % (host, port))

    thread = threading.Thread(target = talk, args = (sock,))
    thread.daemon = True
    thread.start()

    while True:

        try:
            msg = sock.recv(80) # Maximum number of bytes we expect
        except:
            print('Failed to receive')
            break

        if len(msg) < 1:
            break

        print('Server said: ' + msg.decode('utf-8')) # Python 3 requires decoding

    sock.close()
