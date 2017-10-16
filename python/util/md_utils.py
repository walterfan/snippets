import os
import sys
import struct
import re
import logging

logging.basicConfig(stream=sys.stderr, level=logging.DEBUG)
logger = logging.getLogger(__name__)


def list_to_md(str_list):
    output = ""
    for str in str_list:
        output = output + "* %s \n" % str
    return output

def str_to_md_list(the_str, sep):
    str_list = the_str.split(sep)
    output = ""
    for str in str_list:
        output = output + "* %s \n" % str
    return output
