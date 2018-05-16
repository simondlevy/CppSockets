#!/usr/bin/env python3
'''
client.py

Simple Python socket client example with threading

Copyright Simon D. Levy 2018

MIT License
'''

RATE = 1 # Update frequency in Herz 

import socket

from hostport import hostport

if __name__ == '__main__':

    messages = ['one', 'two', 'three', 'four', 'five']
    messageId = 0

    host, port = hostport()

    sock = socket.socket()

    print('Attempting to connect to server %s:%d' % (host, port))

    try:
        sock.connect((host, port)) # Note tuple!
        print('Connected!')
    except socket.error: 
        print('Failed')

    while True:

        message = input('> ')

        print('Sending %s to server' % message)

        try:
            sock.send(message.encode('utf-8'))
        except socket.error:
            print('Failed to send')

        try:
            msg = sock.recv(80) # Maximum number of bytes we expect
            if len(msg) < 1:
                sock.close()
                sock = socket.socket()
                connected = False
            else:
                print('Server said: ' + msg.decode('utf-8')) # Python 3 requires decoding
                received = True

        except:
            print('Failed to receive')
