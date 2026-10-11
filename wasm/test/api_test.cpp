#include "mefodij_wasm.h"

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

namespace {

int failures = 0;

void expect(bool condition, const char * name)
{
    if (!condition) {
        std::cerr << "FAIL " << name << '\n';
        failures++;
    }
}

void expectEq(const std::string & actual, const std::string & expected, const char * name)
{
    if (actual != expected) {
        std::cerr << "FAIL " << name << "\n  expected: " << expected
                  << "\n  actual:   " << actual << '\n';
        failures++;
    }
}

bool contains(const std::string & text, const std::string & needle)
{
    return text.find(needle) != std::string::npos;
}

}

int main()
{
    mkdir("build", 0777);
    mkdir("build/api-test-tmp", 0777);
    if (chdir("build/api-test-tmp") != 0) {
        std::cerr << "FAIL could not enter the API test directory\n";
        return 1;
    }

    expect(mefodij_eval(nullptr) == 2, "null code status");
    expectEq(mefodij_error(), "Code is missing.", "null code error");

    expect(mefodij_write_file(nullptr, "a") == 2, "null path");
    expect(mefodij_write_file("a.txt", nullptr) == 2, "null contents");
    expect(mefodij_write_file("", "a") == 2, "empty path");

    const char badUtf8[] = {'\xff', '\0'};
    expect(mefodij_eval(badUtf8) == 1, "invalid utf-8 status");
    expect(contains(mefodij_error(), "UTF-8"), "invalid utf-8 message");

    expect(mefodij_eval("5 + 7 - 2 / 2 + 3 * 3;") == 0, "math status");
    expectEq(mefodij_result(), "20", "math result");
    expectEq(mefodij_output(), "", "math has no print");
    expectEq(mefodij_error(), "", "math has no error");

    expect(mefodij_eval("(ні && 1) || (0 || так);") == 0, "bool status");
    expectEq(mefodij_result(), "так", "bool result");

    expect(mefodij_eval("друк \"привіт\\n\"; друк \"світ\";") == 0, "print status");
    expectEq(mefodij_output(), "привіт\nсвіт", "print output");
    expectEq(mefodij_result(), "світ", "print result is the last value");

    expect(mefodij_eval("мем секрет = 41;") == 0, "define status");
    expect(mefodij_eval("секрет;") == 1, "fresh engine does not keep variables");
    expect(contains(mefodij_error(), "секрет"), "missing variable mentions the name");

    expect(mefodij_eval("'привіт'.довжина;") == 0, "length status");
    expectEq(mefodij_result(), "6", "length result");

    expect(mefodij_eval("'привіт світ' ~ '.*сві.*';") == 0, "regex status");
    expectEq(mefodij_result(), "так", "regex result");

    expect(mefodij_eval("друк \"до\"; 1 / 0;") == 1, "division status");
    expectEq(mefodij_output(), "до", "division keeps earlier output");
    expect(contains(mefodij_error(), "Division by zero."), "division error");

    expect(mefodij_eval("конст а = 1; а = 2;") == 1, "const status");
    expect(contains(mefodij_error(), "const"), "const error");

    expect(mefodij_eval("// лише коментар\n") == 0, "comment status");
    expectEq(mefodij_result(), "", "comment result");

    expect(mefodij_eval("імпорт \"немає.txt\";") == 1, "missing import status");
    expect(contains(mefodij_error(), "немає.txt"), "missing import names the file");

    const char * library =
        "функція додати(а, б) {\n"
        "    вихід а + б;\n"
        "}\n";
    expect(mefodij_write_file("lib/add.txt", library) == 0, "write library");
    expect(mefodij_eval("імпорт \"lib/add.txt\"; друк додати(20, 22);") == 0, "import status");
    expectEq(mefodij_output(), "42", "import output");

    expect(mefodij_write_file("lib/add.txt", "друк 7;") == 0, "overwrite library");
    expect(mefodij_eval("імпорт \"lib/add.txt\";") == 0, "reimport status");
    expectEq(mefodij_output(), "7", "reimport output");

    if (failures != 0) {
        std::cerr << failures << " failure(s)\n";
        return 1;
    }
    return 0;
}
