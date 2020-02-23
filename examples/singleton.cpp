#include <iostream>

#include "singleton.h"

using namespace std;

namespace {

class Test : public xstl::Singleton<Test> {
 public:
  void Hello() {
    std::cout << "hello!" << std::endl;
  }

 private:
  friend class xstl::Singleton<Test>;

  Test() {}
};

}  // namespace

int main(int argc, const char *argv[]) {
  Test::Get().Hello();
  return 0;
}
