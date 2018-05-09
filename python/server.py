#!/usr/bin/env python3
'''
server.py

Simple Python socket server example with threading

Copyright Simon D. Levy 2018

MIT License
'''

import socket
import threading
import sys

from hostport import hostport

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

    host, port = hostport()

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

        message = input('> ')

        try:
            client.send(message.encode('utf-8'))

        except socket.error:
            print('Failed to transmit')
            break
  
    client.close()
    sock.close
