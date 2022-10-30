#include "../include/Engine.h"
#include "../include/tools.h"
#include <iostream>
#include <cwchar>

using namespace std;

void init() {
    setlocale(LC_ALL, "en_US.utf8");
}

int main(int argc, char** argv) {
    try {
        init();
        if (argc > 1) {
            Mefody::Engine mefody{};
            wcout << mefody.evaluateFile(argv[1]);
        } else {
            throw runtime_error("Input file is missing.");
        }
    } catch(const exception & e) {
       cerr << "Error: " << e.what() << '\n';
    }
    return 0;
}
