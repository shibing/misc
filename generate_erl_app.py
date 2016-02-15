#!/usr/bin/python

import os
import sys

dirs = ['doc', 'ebin', 'include', 'priv', 'src'];

def generate(baseName):
    if not baseName:
        raise TypeError('app name should not emtpy')
    os.mkdir(baseName)
    for d in dirs:
        os.mkdir(os.path.join(baseName, d))


if __name__ == '__main__':
    if len(sys.argv) < 2:
        print('Usage: %s appname' %(sys.argv[0]))
        exit(-1)
    generate(sys.argv[1])
