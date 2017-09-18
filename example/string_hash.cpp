#include "../str_hash.h"

#include <iostream>

int main(void) {
    std::cout << std::hex << xstl::StringHash("Test string.") << std::endl;
    return 0;
}
