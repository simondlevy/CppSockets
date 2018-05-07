#!/usr/bin/env python3
'''
server.py

Simple Python socket server example with threading

Copyright Simon D. Levy 2018

MIT License
'''

import socket
import sys
import threading


def talk(client):

    while True:

        try:
            msg = client.recv(80) # Maximum number of bytes we expect
        except:
            print('Failed to receive')
            break

        if len(msg) < 1:
            break

        print('Client said: ' + msg.decode('utf-8')) # Python 3 requires decoding


if __name__ == '__main__':

    if len(sys.argv) < 3:
        print('Usage:   %s <HOST> <PORT>' % sys.argv[0])
        print('Example: %s 137.113.118.3 20000' % sys.argv[0])
        exit(1)

    host = sys.argv[1]
    port = int(sys.argv[2])

    sock = socket.socket()

    try:
        sock.bind((host, port)) # Note tuple!
    except socket.error:
        print('bind() failed')
        exit(1)

    sock.listen(1) # handle up to 1 back-logged connection

    sys.stdout.write('Waiting for client to connect ...')
    sys.stdout.flush()

    client, address = sock.accept()

    print('Accepted connection')

    thread = threading.Thread(target = talk, args = (client,))
    thread.daemon = True
    thread.start()

    while True:

        msg = input('> ').encode('utf-8')  # Python3 requires encoding

        if len(msg) < 1:                   # Simple way of quitting on CTRL-C
            break

        try:
            client.send(msg)

        except:
            print('Failed to transmit')
            break

    client.close()
    sock.close
