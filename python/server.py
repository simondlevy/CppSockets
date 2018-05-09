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
import time

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

    argc = len(sys.argv)

    if argc < 2:
        print('Usage:   %s <PORT>' % sys.argv[0])
        print('Usage:   %s <HOST> <PORT>' % sys.argv[0])
        print('Example: %s 20000' % sys.argv[0])
        print('Example: %s 137.113.118.3 20000' % sys.argv[0])
        exit(1)

    localhost = argc < 3

    host = 'localhost' if localhost else sys.argv[1] 

    port = int(sys.argv[1 if localhost else 2])

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

    messages = ['one', 'two', 'three', 'four', 'five']
    messageId = 0

    while True:

        try:
            client.send(messages[messageId].encode('utf-8'))

        except socket.error:
            print('Failed to transmit')
            break
  
        messageId = (messageId + 1) % len(messages)

        time.sleep(1)

    client.close()
    sock.close
