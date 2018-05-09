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
import time

def talk(sock):

    messages = ['one', 'two', 'three', 'four', 'five']
    messageId = 0

    while True:

        try:
            sock.send(messages[messageId].encode('utf-8'))

        except socket.error:
            break

        messageId = (messageId + 1) % len(messages)

        time.sleep(1)


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
