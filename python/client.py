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
import fcntl
import os
from sys import stdout

from hostport import hostport

if __name__ == '__main__':

    messages = ['one', 'two', 'three', 'four', 'five']
    messageId = 0

    host, port = hostport()

    sock = socket.socket()

    connected = False

    start = time.time()
    prev = start

    while True:

        curr = time.time()

        if curr - prev > 1./RATE:

            prev = curr

            if connected:

                received = False

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

                print('Attempting to connect to server %s:%d' % (host, port))

                try:
                    sock.connect((host, port)) # Note tuple!
                    fcntl.fcntl(sock, fcntl.F_SETFL, os.O_NONBLOCK)
                    connected = True
                    print('Connected!')
                except socket.error: 
                    continue


    sock.close()
