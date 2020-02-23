#include <iostream>
#include <sstream>
#include <thread>

#include "progress.h"

using namespace std;

namespace {

xstl::Progress progress;

void Process(int index) {
  for (int percent = 0; percent < 100; ++percent) {
    progress.set_percent(index, percent / 100.f);
    this_thread::sleep_for(chrono::milliseconds((index + 1) * 50));
  }
  progress.set_percent(index, 1);
}

std::string GetTitle(int index) {
  ostringstream oss;
  oss << "Process " << index;
  return oss.str();
}

}  // namespace

int main(int argc, const char *argv[]) {
  constexpr int kProcCount = 5;
  thread asyns[kProcCount + 1];
  progress.set_count(kProcCount);
  for (int i = 0; i < kProcCount; ++i) {
    progress.set_title(i, GetTitle(i));
    asyns[i] = thread(&Process, i);
  }
  asyns[kProcCount] = progress.RefreshAsync();
  progress.Show();
  for (auto &&i : asyns) i.join();
  return 0;
}
