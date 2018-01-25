#include "../src/range.h"

#include <iostream>

using namespace std;

int main(int argc, const char *argv[]) {
    cout << "range test 1:" << endl;
    for (const auto &i : xstl::Range(10)) {
        cout << i << ' ';
    }
    cout << endl;
    cout << "range test 2:" << endl;
    for (const auto &i : xstl::Range(10, 20)) {
        cout << i << ' ';
    }
    cout << endl;
    cout << "range test 3:" << endl;
    for (const auto &i : xstl::Range(10, 20, 2)) {
        cout << i << ' ';
    }
    cout << endl;
    cout << "range test 4:" << endl;
    for (const auto &i : xstl::Range<int>(1, [](int &v) {
            return (v *= 2) <= 10000;
        })) {
        cout << i << ' ';
    }
    cout << endl;
    return 0;
}
