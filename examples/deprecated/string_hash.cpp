#include <iostream>

#include "deprecated/str_hash.h"

using namespace std;

int main(void) {
  cout << hex << xstl::StringHash("Test string.") << endl;
  return 0;
}
