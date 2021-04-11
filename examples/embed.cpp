#include <iostream>

#include "embed.h"

using namespace std;

XSTL_EMBED_STR(kCurSourceFile, "examples/embed.cpp");

int main(int argc, const char *argv[]) {
  cout << kCurSourceFile;
  return 0;
}
