#!/usr/bin/env python3
'''
server.py

Simple Python socket server example with threading

Copyright Simon D. Levy 2018

MIT License
'''

from sockets import SocketServer
from threading import Thread
from sys import stdout
from time import sleep
from hostport import hostport

def talk(server):

    while True:

        msg = server.receiveData(80) # Maximum number of bytes we expect

        if len(msg) < 1:
            break

        print('Client said: ' + msg.decode('utf-8')) # Python 3 requires decoding

        sleep(.01)

if __name__ == '__main__':

    host, port = hostport()

    server = SocketServer(host, port)

    server.acceptConnection()

    thread = Thread(target = talk, args = (server,))
    thread.daemon = True
    thread.start()

    while True:

        stdout.write('> ')
        stdout.flush()
        message = input()

        server.sendData(message.encode('utf-8'))

        sleep(1)
  
    server.close()
