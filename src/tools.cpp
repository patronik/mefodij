#include "../include/tools.h"

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

wstring readWideFile(const char * filename)
{
    wifstream wif(filename);
    wif.imbue(locale("en_US.UTF-8"));
    wstringstream wss;
    wss << wif.rdbuf();
    return wss.str();
}