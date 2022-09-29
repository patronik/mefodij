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
                throw runtime_error("File '" + string(argv[1]) + "' does not exist.");
            }
            Interpreter interpreter{};
            wcout << interpreter.evaluate(readWideFile(argv[1]));
        } else {
            throw runtime_error("Input file is missing.");
        }
    } catch(const exception & e) {
       cerr << "Error: " << e.what() << '\n';
    }
    return 0;
}
