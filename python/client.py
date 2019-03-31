#!/usr/bin/env python3
'''
client.py

Simple Python socket client example with threading

Copyright Simon D. Levy 2018

MIT License
'''

from sockets import SocketClient
from hostport import hostport

if __name__ == '__main__':

    messages = ['one', 'two', 'three', 'four', 'five']
    messageId = 0

    host, port = hostport()

    client = SocketClient(host, port)

    print('Attempting to connect to server %s:%d' % (host, port))

    client.openConnection()

    while True:

        message = input('> ')

        client.sendData(message.encode('utf-8'))

        msg = client.receiveData(80)

        print('Server said: ' + msg.decode('utf-8'))
