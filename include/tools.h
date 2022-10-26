#ifndef TOOLS_H
#define TOOLS_H

#include <string>
#include <algorithm>
#include <locale> 
#include <codecvt>
#include <vector>
#include <sstream>
#include <fstream>
namespace MefodyTools {
    using namespace std;

    bool isNumber(const wstring & src);
    bool isNumber(const wchar_t src);
    string wideStrToStr(wstring src);
    string wideStrToStr(wchar_t src);
    template <class T>
    bool inVector(vector<T> storage, T key)
    {
        return find(storage.begin(), storage.end(), key) != storage.end();   
    }
    wstring readWideFile(const char * filename);
    bool fileExist(const char * fileName);
};

#endif