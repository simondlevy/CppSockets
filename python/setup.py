#!/usr/bin/env python

'''
setup.py - Python distutils setup file for sockets module.

Copyright (C) 2019 Simon D. Levy

MIT License
'''

#from distutils.core import setup
from setuptools import setup

setup (name = 'sockets',
    version = '0.1',
    description = 'Simple sockets in Python',
    packages = ['sockets'],
    author='Simon D. Levy',
    author_email='simon.d.levy@gmail.com',
    url='https://github.com/simondlevy/sockets',
    license='MIT',
    platforms='Linux; Windows; OS X'
    )
