#!/usr/bin/env python3
'''
server.py

Simple Python socket client example

Copyright Simon D. Levy 2018

MIT License
'''

import socket
import sys

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
    print('bind() failed with code ' + str(msg[0]) + ': ' + msg[1])

sock.listen(1) # handle up to 1 back-logged connection

sys.stdout.write('Waiting for client to connect ...')
sys.stdout.flush()

client, address = sock.accept()

print('Accepted connection')

while True:

    msg = input('> ').encode('utf-8')

    if len(msg) < 1:
        break

    try:
        client.send(msg)
    except:
        print('Failed to transmit')
        break

client.close()
sock.close
