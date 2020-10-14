#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>
#include <numeric>
#include <random>
#include <functional>
#include <boost/core/noncopyable.hpp>

using namespace std;

struct square {
  typedef void result_type;
  void operator() (int &x) { 
    x = x * x;
  }

};

void f(int& n1, int& n2, const int& n3)
{
    std::cout << "In function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
    ++n1; // increments the copy of n1 stored in the function object
    ++n2; // increments the main()'s n2
    // ++n3; // compile error
}


int function_demo(int argc, char* argv[])
{
    auto print = [](const int& n) { std::cout << " " << n; };
    vector<int> v = {1, 2, 3,4, 5};
    for_each(v.begin(), v.end(), print);
    printf("\n---------function object ----------\n");
    for_each(v.begin(), v.end(), square());
    for_each(v.begin(), v.end(), print);
    printf("\n-------- function binding -----------\n");

    int n1 = 1, n2 = 2, n3 = 3;
    std::function<void()> bound_f = std::bind(f, n1, std::ref(n2), std::cref(n3));
    n1 = 10;
    n2 = 11;
    n3 = 12;
    std::cout << "Before function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
    bound_f();
    std::cout << "After function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
    return 0;
}
