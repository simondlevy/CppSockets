#!/usr/bin/env python3
'''
client.py

Simple Python socket client example with threading

Copyright Simon D. Levy 2018

MIT License
'''

RATE = 1 # Update frequency in Herz 

import socket
import time
import os
from sys import stdout

from hostport import hostport

if __name__ == '__main__':

    messages = ['one', 'two', 'three', 'four', 'five']
    messageId = 0

    host, port = hostport()

    sock = socket.socket()

    print('Attempting to connect to server %s:%d' % (host, port))

    try:
        sock.connect((host, port)) # Note tuple!
        connected = True
        print('Connected!')
    except socket.error: 
        print('Failed')

    '''
    start = time.time()
    prev = start

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
                    continue

                if received:
                    message = messages[messageId]
                    print('Sending %s to server' % message)
                    sock.send(message.encode('utf-8'))
                    messageId = (messageId + 1) % len(messages)

            else:


    sock.close()
    '''
