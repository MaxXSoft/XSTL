#include <iostream>

#include "deprecated/argh.h"

using namespace std;

int main(int argc, const char *argv[]) {
  xstl::ArgumentHandler argh;
  argh.SetErrorHandler([](const string &v) {
    cout << "unknown: " << v << endl;
    return 1;
  });
  argh.AddHandler("h", [](const string &v) {
    cout << "help message" << endl;
    return 1;
  });
  argh.AddHandler("", [](const string &v) {
    cout << "file: " << v << endl;
    return 0;
  });
  argh.AddAlias("help", "h");
  argh.ParseArguments(argc, argv);
  return 0;
}
