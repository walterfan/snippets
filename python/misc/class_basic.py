from Tkinter import *

class Message(object):

    CATEGORY_CHOICE = (
    (0, 'general'),
    (1, 'task'),
    (2, 'thinking'),
    (3, 'suggestion'),
    (4, 'question'),
    (5, 'bug'),
    (6, 'recommendation'),
    (7, 'reference'),
    )

    

    def __init__(self):
        self.category = 0
        print "---initialized---"

    def __del__(self):
        print "---deleted---"

    def get_category_name(self):
        return self.CATEGORY_CHOICE[self.category][1]

if __name__ == '__main__' :
    msg = Message()
    print msg.get_category_name()
    print dict(msg.CATEGORY_CHOICE)
    del msg