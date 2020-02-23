#include <iostream>

#include "style.h"

using namespace std;
using namespace xstl;

int main(int argc, const char *argv[]) {
  cout << xstl::style("Br") << "Colorful "
       << xstl::style("RI") << "console"
       << xstl::style("RUg") << " is "
       << xstl::style("Rp") << "awesome!"
       << xstl::reset << endl;
  return 0;
}
