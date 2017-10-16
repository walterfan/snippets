import os
import sys
import struct
import re
import logging
import subprocess
from shutil import copyfile

logging.basicConfig(stream=sys.stderr, level=logging.DEBUG)
logger = logging.getLogger(__name__)


def print_file(filepath):
    if os.path.isdir(filepath):
        print(filepath + " directory match")
    else:
        print(filepath + " match")            

def search_file(fileexp='.+', subdir='', filehandler = print_file):
    if subdir:
        path = subdir
    else:
        path = os.getcwd()
        
    regex = re.compile(fileexp)
        
    for root, dirs, names in os.walk(path):

        for dirname in dirs:
            result = regex.match(dirname)
            if result:
                filehandler(os.path.join(root, dirname))
        for filename in names:
            #print(os.path.join(root, filename))
            result = regex.match(filename)    
            if result:
                filehandler(os.path.join(root, filename))

