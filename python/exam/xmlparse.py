import os
import mistune
import codecs
import sys
import struct
import re
import json
import logging
import subprocess
import xml.etree.ElementTree as ET


def parse(test_result_file):
    tree = ET.parse(test_result_file)
    root = tree.getroot()

    for child in root.findall("testsuite"):
        if len(child): 
            for subchild in child:
                if len(subchild): 
                    for grantchild in subchild:
                        print grantchild.tag

if __name__ == '__main__':
    parse("./TestResult.xml")