'''
Classes for socket server, client

Copyright (C) 2019 Simon D. Levy
 
MIT License

'''
import socket
from sys import stdout

class SocketClient(object):

    def __init__(self, host, port):

        self.host = host
        self.port = port
       
        self.sock = socket.socket()
        self.connected = False

    def openConnection(self):

        stdout.write('Attempting to connect to %s:%d ... ' % (self.host, self.port))
        
        try:
            self.sock.connect((self.host, self.port))
            self.connected = True
            print('Connected')
            return True
        except:
            print('Unavailable')

        return False

    def closeConnection(self):

        self.sock.close()

    def sendData(self, buf):

        self.sock.send(buf)

    def receiveData(self, size):

        return self.sock.recv(size)

    def isConnected(self):

        return self.connected

class SocketServer(object):

    def __init__(self, host, port):

        self.host = host
        self.port = port

        self.sock = socket.socket()

        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

        try:
            self.sock.bind((host, port))
        except socket.error:
            print('bind() failed')

    def acceptConnection(self):

        # handle up to 1 back-logged connection
        self.sock.listen(1) 

        stdout.write('Waiting for client to connect ...')
        stdout.flush()

        self.client, addr = self.sock.accept()

        print('Got connection from %s' % addr[0])

    def closeConnection(self):

        self.client.close()
    
    def sendData(self, buf):

        self.client.send(buf)

    def receiveData(self, size):

        return self.client.recv(size)
