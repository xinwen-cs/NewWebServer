#include <iostream>

#include "base/Thread.h"

int main() {
    Thread([]() {}, "NewThread");
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
