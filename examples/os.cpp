#include <iostream>

#include "os.h"

using namespace std;

int main(int argc, const char *argv[]) {
  cout << "Compile platform info: ";
#if defined(XSTL_OS_64)
  cout << "64-bit ";
#elif defined(XSTL_OS_32)
  cout << "32-bit ";
#endif
#if defined(XSTL_OS_WINDOWS)
  cout << "Windows";
#elif defined(XSTL_OS_MACOS)
  cout << "macOS";
#elif defined(XSTL_OS_LINUX)
  cout << "Linux";
#endif
  cout << endl;
  return 0;
}
