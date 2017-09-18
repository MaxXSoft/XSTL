#include "../argh.h"

#include <iostream>

using namespace std;

int main(int argc, const char *argv[]) {
    xstl::ArgumentHandler argh;
    argh.SetErrorHandler([](const string &v) { cout << "unknown: " << v << endl; });
    argh.AddHandler("h", [](const string &v) { cout << "help message" << endl; });
    argh.AddHandler("", [](const string &v) { cout << "file: " << v << endl; });
    argh.AddAlias("help", "h");
    argh.ParseArguments(argc, argv);
    return 0;
}
