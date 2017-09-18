#include "../raii.h"

#include <iostream>

class Test {
public:
    Test(const int &&num) : num_(new int(num)) {
        std::cout << *num_ << std::endl;
    }
    ~Test() {}

    void Release() {
        delete num_;
        std::cout << "released" << std::endl;
    }

private:
    int *num_;
};

void TestRAII() {
    Test test(123);
    auto raii = xstl::MakeRAII(test, &Test::Release);
}

int main(void) {
    TestRAII();
    std::cout << "done" << std::endl;
    return 0;
}
