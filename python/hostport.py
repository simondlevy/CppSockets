#!/usr/bin/env python3
'''
hostport.py

Command-line retriever for host, port

Copyright Simon D. Levy 2018

MIT License
'''
from sys import argv

def hostport():

    argc = len(argv)

    if argc < 2:
        print('Usage:   %s [HOST] PORT' % argv[0])
        print('Example: %s 192.168.2.1 5000' % argv[0])
        print('Example: %s 5000' % argv[0])
        exit(1)

    host = 'localhost' if argc < 3 else argv[1]
    port = int(argv[1] if argc < 3 else argv[2])

    return host, port

