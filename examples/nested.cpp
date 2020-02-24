#include <iostream>
#include <string>
#include <optional>
#include <cassert>

#include "nested.h"

using namespace std;

int main(int argc, const char *argv[]) {
  auto map = xstl::MakeNestedMap<string, optional<int>>();
  map->AddItem("James", 19);
  map->AddItem("Peter", 22);
  map->AddItem("Monica", 18);
  map->AddItem("Linda", 22);
  map = xstl::MakeNestedMap<string, optional<int>>(map);
  map->AddItem("Mary", 17);
  map->AddItem("Elizabeth", 15);
  map->AddItem("John", 16);
  map->AddItem("Robert", 15);
  auto age = map->GetItem("Linda");
  assert(!!age);
  cout << "Linda: " << *age << endl;
  age = map->GetItem("Robert");
  assert(!!age);
  cout << "Robert: " << *age << endl;
  return 0;
}
