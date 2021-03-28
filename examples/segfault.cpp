#include <iostream>
#include <vector>

#include "segfault.h"

using namespace std;

int main(int argc, const char *argv[]) {
  vector<int> v = {10};
  cout << "v[0] = " << v[0] << endl;
  // first try
  TRY_SEGFAULT {
    *(v.data()) = 11;
  }
  CATCH_SEGFAULT {
    cout << "segmentation fault #1!" << endl;
  }
  cout << "v[0] = " << v[0] << endl;
  // second try
  TRY_SEGFAULT {
    *(v.data() + 10000) = 42;
  }
  CATCH_SEGFAULT {
    cout << "segmentation fault #1!" << endl;
  }
  cout << "v[0] = " << v[0] << endl;
  return 0;
}
