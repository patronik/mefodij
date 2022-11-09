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
            using convert_type = codecvt_utf8<wchar_t>;
            wstring_convert<convert_type, wchar_t> converter;
            return converter.to_bytes(src);
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
