#include <iostream>
#include "stdio.h"
#include <vector>

using namespace std;

int main()
{

    // lambdas captured by reference
    vector<int> vec{1,2,3,4,5};
    auto total = 0;
    auto accum = [&total](vector<auto> v) { for (auto i : v) {total += i;} return total;};
    auto res = accum(vec);
    cout << res;


    return 0;
}
