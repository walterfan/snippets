from fabric.api import *
from fabric.context_managers import *
from fabric.contrib.console import confirm 
import os, subprocess, sys, json

lib_path = os.path.abspath(os.path.join('./util'))
sys.path.append(lib_path)
from md_utils import *

local_dir = os.getcwd()
    
@task
def unittest():
    local("python test/md_utils_test.py")


