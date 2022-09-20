#include "../include/Interpreter.h"
#include <iostream>
#include <cwchar>

void init() {
    setlocale(LC_ALL, "en_US.utf8");
}

int main() {
    init();
    Interpreter interpreter{};
    interpreter.evaluate(L"функція додати() { повернути 2 + 2 - 1; } друк додати() + 99; друк \"\nкінець програми\n\"");
    return 0;
}
