#include "run_example.h"

using namespace std;

int lessNnum(const int& a, const int& b) {
    return a<b?a:b;
}

class LessNum {
public:
    int operator()(const int& a, const int& b) {
        return a<b?a:b;
    }
};

int std_function_test(int argc, char* argv[])
{
    int a{3};
    int b{4};
    std::function<int(const int x, const int y)> compare;
    compare = lessNnum;
    cout << compare(a, b) << endl;

    compare = LessNum();
    cout << compare(a, b) << endl;

    compare = [](int a, int b) { return a<b?a:b; };
    cout << compare(a, b) << endl;

    return 0;
}