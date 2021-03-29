#include <iostream>
#include <memory>

#include "segfault.h"

using namespace std;

int main(int argc, const char *argv[]) {
  auto arr = make_unique<int[]>(1);
  arr[0] = 10;
  cout << "arr[0] = " << arr[0] << endl;
  // first try
  TRY_SEGFAULT {
    arr[0] = 11;
    cout << "#1 ended" << endl;
  }
  CATCH_SEGFAULT {
    cout << "segmentation fault #1!" << endl;
  }
  cout << "arr[0] = " << arr[0] << endl;
  // second try
  TRY_SEGFAULT {
    arr[-1000000] = 42;
    cout << "#2 ended" << endl;
  }
  CATCH_SEGFAULT {
    cout << "segmentation fault #2!" << endl;
  }
  cout << "arr[0] = " << arr[0] << endl;
  return 0;
}
