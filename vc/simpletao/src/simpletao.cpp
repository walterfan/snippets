/*
Please add gtestd.lib, ACEd.lib into path and library path
*/
#pragma warning ( disable : 4005 )

#include "stdafx.h"
#include <iostream>
#include <vector>
#include "IDGenerator.h"
#include "ace/OS.h"
#include "Dumper.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;
using namespace testing;
using ::testing::AtLeast;  

extern int reactor_test(int argc, char* argv[]);
extern int gtest_primer(int argc, char* argv[]);
extern void RefCtrlTest();
extern int thread_test(int argc, char* argv[]);
extern int ace_webcli_test(int argc, char *argv[]);
extern int ace_svr_test(int argc, char *argv[]);
extern int test_binarytree(int argc, char* argv[]);


int ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
#if 0
    int ret = ace_webcli_test(argc, argv);
    if(ret >= 0) {
        getchar();
        return ret;
    }
    ACE_Time_Value expiration = ACE_OS::gettimeofday();
    RefCtrlTest();
    vector<int> vec(10);
    fill(vec.begin(), vec.end(), 2012);
    CDumper<vector<int>, ostream> dumper;
    dumper.dump(vec, std::cout);
    test_binarytree(argc,argv);
#endif
    int selection;
    string input;
    bool done = false;
    string prompt =  "Welcome to the command console, what would you like to do?\n"
        "1. Run all test cases\n"
        "2. Run a test case\n"
        "3. Exit the program\n";
    while (!done )
    {   
        cout<<prompt<<endl;
        getline(cin, input);    //get input
        stringstream(input) >> selection; //extract selection integer
        if (selection == 1)
        {
            testing::InitGoogleMock(&argc, argv);
            RUN_ALL_TESTS();
            break;
        }
        else if (selection == 2)
        {
            cout << "Enter the name of the testcase: ";                
            getline(cin, input);
            input = "--gtest_filter=" + input;
            cout<< input <<endl;
            int nTestCase = 2;
            char* ppTestCases[2];
            ppTestCases[0] = argv[0];
            ppTestCases[1] = (char*)input.c_str();
            testing::InitGoogleMock(&nTestCase, ppTestCases);
            RUN_ALL_TESTS();
            break;
        }
        else if (selection == 3)
        {
            done = true;
        }
        else
        {
            cout << "Please enter a valid selection, 1, 2 or 3.\n" << endl;
        }
    }

    return 0;
}

