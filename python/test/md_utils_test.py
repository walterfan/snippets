import os,sys,unittest
from shutil import copyfile


current_path = os.path.dirname(os.path.abspath(__file__))
lib_path = os.path.join(current_path, "../util")
sys.path.append(lib_path)

from md_utils import *



class TestMdUtils(unittest.TestCase):

    def test_list_to_md(self):
        print "#--- test_list_to_md ---"
        str_list = "abc,\ndef,ghi".split(',')
        md_str = list_to_md(str_list)
        print md_str
        
    
if __name__ == '__main__':
    unittest.main()