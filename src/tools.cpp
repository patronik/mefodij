#include "../include/tools.h"

#include <stdexcept>

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
            // Decode UTF-8 directly. The browser runtime has no en_US.UTF-8
            // locale, so mbtowc() cannot be used for Ukrainian source text.
            static_assert(sizeof(wchar_t) >= 4, "Methodius expects a 32-bit wchar_t");

            if (src.size() >= 3
                && static_cast<unsigned char>(src[0]) == 0xEF
                && static_cast<unsigned char>(src[1]) == 0xBB
                && static_cast<unsigned char>(src[2]) == 0xBF) {
                src.erase(0, 3);
            }

            const unsigned char * ptr = reinterpret_cast<const unsigned char *>(src.data());
            const unsigned char * end = ptr + src.size();
            wstring result;
            result.reserve(src.size());

            while (ptr < end) {
                unsigned char lead = *ptr;
                unsigned int codePoint = 0;
                int length = 0;
                if (lead <= 0x7F) {
                    codePoint = lead;
                    length = 1;
                } else if ((lead & 0xE0) == 0xC0) {
                    codePoint = lead & 0x1F;
                    length = 2;
                } else if ((lead & 0xF0) == 0xE0) {
                    codePoint = lead & 0x0F;
                    length = 3;
                } else if ((lead & 0xF8) == 0xF0) {
                    codePoint = lead & 0x07;
                    length = 4;
                } else {
                    throw runtime_error("Invalid UTF-8 sequence.");
                }

                if (ptr + length > end) {
                    throw runtime_error("Truncated UTF-8 sequence.");
                }
                for (int i = 1; i < length; i++) {
                    if ((ptr[i] & 0xC0) != 0x80) {
                        throw runtime_error("Invalid UTF-8 sequence.");
                    }
                    codePoint = (codePoint << 6) | (ptr[i] & 0x3F);
                }

                bool overlong = (length == 2 && codePoint < 0x80)
                    || (length == 3 && codePoint < 0x800)
                    || (length == 4 && codePoint < 0x10000);
                bool surrogate = codePoint >= 0xD800 && codePoint <= 0xDFFF;
                if (overlong || surrogate || codePoint > 0x10FFFF) {
                    throw runtime_error("Invalid UTF-8 sequence.");
                }

                result.push_back(static_cast<wchar_t>(codePoint));
                ptr += length;
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
            return wstring(1, static_cast<wchar_t>(static_cast<unsigned char>(src)));
        }

        wstring readWideFile(const char * filename)
        {
            // Byte read plus UTF-8 decode. Wide file streams and named locales
            // are not available in the browser filesystem.
            ifstream in(filename, ios::in | ios::binary);
            if (!in) {
                throw runtime_error(string("File '") + filename + "' does not exist.");
            }
            string bytes((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
            return strToWideStr(bytes);
        }

        bool fileExist(const char * fileName)
        {
            ifstream infile(fileName);
            return infile.good();
        }
    }

}
