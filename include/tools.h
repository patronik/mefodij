#ifndef TOOLS_H
#define TOOLS_H

#include <string>
#include <algorithm>
#include <locale> 
#include <codecvt>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstring>

namespace Mefody {
    namespace Tools {
        using namespace std;

        bool isNumber(const wstring & src);
        bool isNumber(const wchar_t src);
        string wideStrToStr(wstring src);
        string wideStrToStr(wchar_t src);
        wstring strToWideStr(string src);
        wstring strToWideStr(char src);
        template <class T>
        bool inVector(vector<T> storage, T key)
        {
            return find(storage.begin(), storage.end(), key) != storage.end();   
        }
        wstring readWideFile(const char * filename);
        bool fileExist(const char * fileName);
        struct arrayCmp {
            bool operator()(const wstring& a, const wstring& b) const {
                if (isNumber(a) && isNumber(b)) {
                    return stoi(a) < stoi(b);
                }
                return a < b;
            }
        };
    };

}

#endif