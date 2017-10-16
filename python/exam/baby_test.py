#!/usr/bin/python
# check question for baby

def check_question(a):
    for key in a:
        print "%d. %s = %d" % (key, a[key], eval(a[key]))

def add_question(a, i, q):
    a[i] = q
    i = i +1
    return i

def exam_2013_07_12():
    print "== exam_2013_07_12 =="
    a ={}
    i = 1
    i = add_question(a, i, "6+6-2+5+8+5-3-1+6")
    i = add_question(a, i, "4+7-1+3+7+5-5+4-3")
    i = add_question(a, i, "3+2+3-8+4+6+5+6-1")
    i = add_question(a, i, "3+1+4-5+8-1+6+7-3")
    i = add_question(a, i, "4+3+8-3+2-4+6+6-2")
    i = add_question(a, i, "4+4-3+8-3+5+6+9+6")
    i = add_question(a, i, "5+8-3+5+6-1+7+6-1")
    i = add_question(a, i, "6+5+4-5+3+2+3-7+9")
    i = add_question(a, i, "3+4+8+4-6+8+6-5+8")
    i = add_question(a, i, "3+7+5+3+3+6+5-2+4")
    i = add_question(a, i, "6+3+2+3+6+9-8+6+4")
    i = add_question(a, i, "5+5+5+6-1+6-3+8+6")
    i = add_question(a, i, "6+9+4+2-1+4+8+2-3")
    i = add_question(a, i, "7+5+4+2+5+6-8+1+9")
    i = add_question(a, i, "6+2+4+8+9-7+8+4+6")
    i = add_question(a, i, "7+7-3+8-9+4+8+2+9")
    i = add_question(a, i, "1+2+9+3+7+5+4-1+6")
    i = add_question(a, i, "5+6+4+3-8+9+4+5-4")
    i = add_question(a, i, "6+7-1+5-2+6+2+8+9")
    i = add_question(a, i, "9+8-5+2-4+6+7+3+6")

    check_question(a)

def exam_2013_07_16():
    print "== exam_2013_07_16 =="
    a ={}
    i = 0; i= i+1
    i = add_question(a, i, "6+7-3+4+8+6-8+4+7+6")
    i = add_question(a, i, "8+6-3+5+7-2+8-7+6-5")
    i = add_question(a, i, "7+4-1+2+3-4+9+6-3+7")
    i = add_question(a, i, "8-6+9-1+7-2+3+4-1+9")
    i = add_question(a, i, "5+4+9-7+6+4+1-2+7+8")
    i = add_question(a, i, "3+9-1+9+4+5-8+6+9+5")
    i = add_question(a, i, "4+3+8-4+9+2+6-3+4+8")
    i = add_question(a, i, "3+4+6+7+8-7+5+4+2-1")
    i = add_question(a, i, "9-7+5+2+6+8-3+6-4+9")
    i = add_question(a, i, "8-6+9+7+8+1-6+7+2+4")
    check_question(a)

def exam_2013_07_21():
    print "== exam_2013_07_21 =="
    a ={}
    i = 0; i= i+1
    i = add_question(a, i, "97-72+37+29-80+54+19-63")
    i = add_question(a, i, "25+37-41+29+25+19-52+38")
    i = add_question(a, i, "54-23+39-50+16-31+26+59")
    i = add_question(a, i, "65+18-62+25+37-30+28-51")
    i = add_question(a, i, "15+19+38+19-40+16+13-80")
    i = add_question(a, i, "27-11+28+36+19-65+28+28")
    i = add_question(a, i, "53+17-50+39+26-11-52+49")
    i = add_question(a, i, "88-53+27+28-90+54+27-81")
    i = add_question(a, i, "35+19-12+29-61+38+24+18")
    i = add_question(a, i, "33+27+15-64+45+26-30+38")
    check_question(a)

def exam_2013_07_31():
    print "== exam_2013_07_31 =="
    a ={}
    i = 0; i= i+1
    i = add_question(a, i, "95-5-4-5-3-2-6-8-6-7-9-4")
    i = add_question(a, i, "85-6-9-4-3-7-8-6-3-7-6-9")
    i = add_question(a, i, "85-5-4-6-8-8-9-3-7-6-4-1")
    i = add_question(a, i, "82-1-4-5-7-4-6-3-9-6-3-4")
    i = add_question(a, i, "86-9-2-2-1-3-6-4-6-8-9-6")
    i = add_question(a, i, "88-5-2-4-4-2-1-8-6-9-5-6")
    i = add_question(a, i, "93-5-9-4-6-8-6-9-4-8-5-3")
    i = add_question(a, i, "47-5-4-2-3-2-3-6-5-8-6-2")
    i = add_question(a, i, "78-5-4-8-6-3-9-1-5-6-8-6")
    i = add_question(a, i, "99-5-7-6-3-8-3-8-6-8-6-3")

    check_question(a)

if __name__ == '__main__':
    exam_2013_07_12()
    exam_2013_07_16()
    exam_2013_07_21()
    exam_2013_07_31()