'''
hostport.py

Command-line helper for sockets

Copyright Simon D. Levy 2018

MIT License
'''

import sys

def hostport():

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

    return host, port

