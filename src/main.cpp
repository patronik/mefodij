#include "../include/tools.h"
#include "../include/Interpreter.h"
#include <iostream>
#include <cwchar>

void init() {
    setlocale(LC_ALL, "en_US.utf8");
}

int main(int argc, char** argv) {
    try {
        init();
        if (argc > 1) {
            if (!fileExist(argv[1])) {
                throw runtime_error("Файлу '" + string(argv[1]) + "' не існує\n");
            }
            Interpreter interpreter{};
            wcout << interpreter.evaluate(readWideFile(argv[1]));
        } else {
            wcout << L"Вхідний файл відсутній\n";
        }
    } catch(const exception & e) {
       wcout << L"Помилка: " << e.what() << L'\n';
    }
    return 0;
}
