#include "../include/Engine.h"
#include "../include/tools.h"
#include <iostream>
#include <cwchar>

using namespace std;

void init() {
    setlocale(LC_ALL, "en_US.utf8");
}

char * getCmdOption(char ** begin, char ** end, const string & option)
{
    char ** itr = find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char** begin, char** end, const string& option)
{
    return find(begin, end, option) != end;
}

int main(int argc, char * argv[]) {
    try {
        init();
        if(cmdOptionExists(argv, argv + argc, "-f")) {
            Mefodij::Engine mefodij{};
            mefodij.evaluateFile(getCmdOption(argv, argv + argc, "-f"));
        } else if (cmdOptionExists(argv, argv + argc, "-r")) {
            Mefodij::Engine mefodij{};
            mefodij.evaluateCode(getCmdOption(argv, argv + argc, "-r"));
        } else {
            throw runtime_error(
                "Error: input is missing. Provide input file with \"-f\" or paste raw code with \"-r\"."
            );
        }
    } catch(const exception & e) {
       cerr << "Error: " << e.what() << '\n';
    }
    return 0;
}
