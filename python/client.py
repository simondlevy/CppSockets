#!/usr/bin/env python3
'''
client.py

Simple Python socket client example with threading

Copyright Simon D. Levy 2018

MIT License
'''

RATE = 1

import socket
import time
import fcntl
import os

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

                try:
                    msg = sock.recv(80) # Maximum number of bytes we expect
                    print('Server said: ' + msg.decode('utf-8')) # Python 3 requires decoding

                except:
                    continue

                try:
                    sock.send(messages[messageId].encode('utf-8'))

                except socket.error:
                    continue

                messageId = (messageId + 1) % len(messages)

            else:

                try:
                    sock.connect((host, port)) # Note tuple!
                    fcntl.fcntl(sock, fcntl.F_SETFL, os.O_NONBLOCK)
                    connected = True
                    print('Connected to server %s:%d' % (host, port))
                except socket.error: 
                    continue


    sock.close()
