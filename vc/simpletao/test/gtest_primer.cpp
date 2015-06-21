#include <gtest/gtest.h>
#include "gmock/gmock.h"

int sum(int a, int b)
{
    return a+b;
}

TEST(SumTest, TestCase1)
{
    EXPECT_EQ(10, sum(4, 6));
    EXPECT_EQ(-15, sum(3, -18));
}

int gtest_primer(int argc, char* argv[])
{
    //testing::InitGoogleTest(&argc, argv);
	testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}