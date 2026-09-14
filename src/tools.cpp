#include "../include/tools.h"

namespace Mefodij {

    namespace Tools {
        using namespace std;

        bool isNumber(const wstring& src)
        {
            wstring::const_iterator it = src.begin();
            while (it != src.end() && isdigit(*it)) ++it;
            return !src.empty() && it == src.end();
        }

        bool isNumber(const wchar_t src)
        {
            return isNumber(wstring{src});
        }

        string wideStrToStr(wstring src)
        {
            string result;
            result.reserve(src.size());
            for (wchar_t wc : src) {
                unsigned int cp = static_cast<unsigned int>(wc);
                if (cp <= 0x7F) {
                    result.push_back(static_cast<char>(cp));
                } else if (cp <= 0x7FF) {
                    result.push_back(static_cast<char>(0xC0 | (cp >> 6)));
                    result.push_back(static_cast<char>(0x80 | (cp & 0x3F)));
                } else if (cp <= 0xFFFF) {
                    result.push_back(static_cast<char>(0xE0 | (cp >> 12)));
                    result.push_back(static_cast<char>(0x80 | ((cp >> 6) & 0x3F)));
                    result.push_back(static_cast<char>(0x80 | (cp & 0x3F)));
                } else {
                    result.push_back(static_cast<char>(0xF0 | ((cp >> 18) & 0x07)));
                    result.push_back(static_cast<char>(0x80 | ((cp >> 12) & 0x3F)));
                    result.push_back(static_cast<char>(0x80 | ((cp >> 6) & 0x3F)));
                    result.push_back(static_cast<char>(0x80 | (cp & 0x3F)));
                }
            }
            return result;
        }

        string wideStrToStr(wchar_t src)
        {
            return wideStrToStr(wstring{src});
        }

        wstring strToWideStr(string src)
        {
            // reset the conversion state
            mbtowc(nullptr, 0, 0); 

            const char* ptr = src.c_str();
            const char* end = ptr + strlen(ptr);

            wstring result;
            int ret;
            for (wchar_t wc; (ret = std::mbtowc(&wc, ptr, end-ptr)) > 0; ptr+=ret) {
                result.push_back(wc);
            }
            return result;
        }

        wstring to_wstring(double src)
        {
            wstringstream wstrs;
            wstrs << src;
            return wstrs.str();
        }

        wstring to_wstring(long src)
        {
            return std::to_wstring(src);
        }

        wstring to_wstring(int src)
        {
            return std::to_wstring(src);
        }

        wstring strToWideStr(char src) 
        {
            return strToWideStr(string(1, src));
        }

        wstring readWideFile(const char * filename)
        {
            wifstream wif(filename);
            wif.imbue(locale("en_US.UTF-8"));
            wstringstream wss;
            wss << wif.rdbuf();
            return wss.str();
        }

        bool fileExist(const char * fileName)
        {
            ifstream infile(fileName);
            return infile.good();
        }
    }

}
