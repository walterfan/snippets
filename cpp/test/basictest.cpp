#include "gmock/gmock.h"
#include <string>
#include <iostream>

using namespace std;
using namespace testing;

using ::testing::Return;
using ::testing::Mock;



struct Session {

    uint32_t m_id = 0;

    std::string m_name;

    std::vector<std::string> m_tags;
};


int compare(int m, int n)
{
    return (m > n);
}

void bubble(int a[], int N)
{
    int i, j, t;
    for (i = N-1; i >= 0; i--)
    {
        for (j = 1; j <= i; j++)
        {
            if (compare(a[j-1], a[j]))
            {
                t = a[j-1];
                a[j-1] = a[j];
                a[j] = t;
            }
        }
    }
}

TEST(BasicTest, selfincrease1)
{

    int i = 0;
    cout<< i++ <<endl;
    cout<< i++ <<endl;
    cout<< i++ <<endl;
}
TEST(BasicTest, selfincrease2)
{

    int i = 0;
    cout<< ++i <<endl;
    cout<< ++i <<endl;
    cout<< ++i <<endl;
}

TEST(BasicTest, pointer)
{
    cout<<"--- BasicTest.pointer --"<<endl;

    int i;
    int arr[10] = {2,1,3,8,2,0,7,4,9,6};
    putchar('\n');
    for (i = 0; i < 10; i++)
    {
        printf("%d ", arr[i]);
    }
    bubble(arr,10);
    putchar('\n');

    for (i = 0; i < 10; i++)
    {
        printf("%d ", arr[i]);
    }
    putchar('\n');
}

TEST(BasicTest, testInit)
{

    Session s1{.m_id{1}, .m_name{"foo"}, .m_tags{"1"}};
    Session s2{.m_id=2, .m_name="bar", .m_tags={"2"}};



}