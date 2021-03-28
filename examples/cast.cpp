#include <iostream>
#include <cstddef>

#include "cast.h"

using namespace std;

namespace {

struct IntDouble {
  int i;
  double d;
};

struct FloatLong {
  float f;
  long l;
};

}  // namespace

int main(int argc, const char *argv[]) {
  IntDouble t = {42, 3.3};
  auto bytes = xstl::IntPtrCast<8>(&t);
  for (std::size_t i = 0; i < sizeof(IntDouble); ++i) {
    cout << hex << static_cast<int>(bytes[i]) << ' ';
  }
  cout << endl;
  auto fl = xstl::PtrCast<FloatLong>(&t);
  cout << fl->f << ", " << fl->l << endl;
  cout << hex << xstl::EndianCast(0x12345678u) << endl;
  return 0;
}
