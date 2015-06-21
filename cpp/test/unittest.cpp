//unit test suite

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;
using namespace testing;
using ::testing::AtLeast;                     // #1

int main(int argc, char** argv) {
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  printf("--- unit test ---\n");
  InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
