#include <iostream>

#include "bitvalue.h"

using namespace std;

int main(int argc, const char *argv[]) {
  constexpr xstl::BitValue32 bv1 = {0b11011, 5}, bv2 = {0b011001, 6};
  static_assert(bv1(0));
  static_assert(!bv1(2));
  static_assert(bv2(3, 0) == 0b1001);
  static_assert((bv1 | bv2) == 0b11011011001);
  return 0;
}
