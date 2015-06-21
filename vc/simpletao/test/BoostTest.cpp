#include "gmock/gmock.h"
#include <string>
#include <iostream>

#include <boost/typeof/typeof.hpp>


using namespace std;
using namespace testing;

using ::testing::Return;
using ::testing::Mock;


vector<string> make_vector()
{
	vector<string> v(10);
	return v;
}

TEST(BoostTest, TypeofTest)
{
	cout<<"--- TypeofTest --"<<endl;
    
	BOOST_TYPEOF(2.0*3) x=3.0*2;
	BOOST_AUTO(v, make_vector());

    ASSERT_TRUE((int)x==6);
}