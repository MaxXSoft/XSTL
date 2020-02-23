#include <iostream>
#include <string>

#include "argparse.h"

using namespace std;

int main(int argc, const char *argv[]) {
  // set up argument parser
  xstl::ArgParser argp;
  argp.AddArgument<string>("input", "input file");
  argp.AddOption<bool>("help", "h", "show this message", false);
  argp.AddOption<bool>("version", "v", "show version info", false);
  argp.AddOption<bool>("option", "o", "an option", false);
  argp.AddOption<int>("number", "n", "a number", 42);
  argp.AddOption<string>("string", "s", "a string", "hello");
  // parse argument
  auto ret = argp.Parse(argc, argv);
  // check if need to exit program
  if (argp.GetValue<bool>("help")) {
    argp.PrintHelp();
    return 0;
  }
  else if (argp.GetValue<bool>("version")) {
    cout << "version 0.1" << endl;
    return 0;
  }
  else if (!ret) {
    cerr << "invalid input, run '";
    cerr << argp.program_name() << " -h' for help" << endl;
    return 1;
  }
  // print arguments
  cout << "input: " << argp.GetValue<string>("input") << endl;
  cout << "option: " << boolalpha << argp.GetValue<bool>("option") << endl;
  cout << "number: " << argp.GetValue<int>("number") << endl;
  cout << "string: " << argp.GetValue<string>("string") << endl;
  return 0;
}
