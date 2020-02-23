#include <iostream>

#include "deprecated/raii.h"

using namespace std;

class Test {
 public:
  Test(const int &&num) : num_(new int(num)) { cout << *num_ << endl; }
  ~Test() {}

  void Release() {
    delete num_;
    cout << "released" << endl;
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
  cout << "done" << endl;
  return 0;
}
