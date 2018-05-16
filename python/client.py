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
        print('Connected!')
    except socket.error: 
        print('Failed')

    message = "I am the client!"
    print('Sending %s to server' % message)

    try:
        sock.send(message.encode('utf-8'))
    except socket.error:
        print('Failed')
