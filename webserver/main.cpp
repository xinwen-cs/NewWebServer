#include <iostream>

#include "base/Thread.h"
#include "Util.h"

int main() {
    Thread([]() {}, "NewThread");
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
