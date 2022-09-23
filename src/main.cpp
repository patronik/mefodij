#include "../include/Interpreter.h"
#include <iostream>
#include <cwchar>

void init() {
    setlocale(LC_ALL, "en_US.utf8");
}

int main(int argc, char** argv) {
    init();
    if (argc > 1) {
         Interpreter interpreter{};
         wcout << interpreter.evaluate(readWideFile(argv[1]));
    } else {
        wcout << L"Вхідний файл відсутній\n";
    }
    return 0;
}
