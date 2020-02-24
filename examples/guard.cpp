#include <iostream>

#include "guard.h"

using namespace std;

xstl::Guard GenerateSomething() {
  std::cout << "header generated" << std::endl;
  return xstl::Guard([]() {
    std::cout << "footer generated" << std::endl;
  });
}

int main(int argc, const char *argv[]) {
  auto guard = GenerateSomething();
  std::cout << "content generated" << std::endl;
  return 0;
}
