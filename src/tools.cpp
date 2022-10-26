#include "../include/tools.h"

using namespace std;

bool MefodyTools::isNumber(const wstring& src)
{
    wstring::const_iterator it = src.begin();
    while (it != src.end() && isdigit(*it)) ++it;
    return !src.empty() && it == src.end();
}

bool MefodyTools::isNumber(const wchar_t src)
{
    return MefodyTools::isNumber(wstring{src});
}

string MefodyTools::wideStrToStr(wstring src)
{
    using convert_type = codecvt_utf8<wchar_t>;
    wstring_convert<convert_type, wchar_t> converter;
    return converter.to_bytes(src);
}

string MefodyTools::wideStrToStr(wchar_t src)
{
    return MefodyTools::wideStrToStr(wstring{src});
}

wstring MefodyTools::readWideFile(const char * filename)
{
    wifstream wif(filename);
    wif.imbue(locale("en_US.UTF-8"));
    wstringstream wss;
    wss << wif.rdbuf();
    return wss.str();
}

bool MefodyTools::fileExist(const char * fileName)
{
    ifstream infile(fileName);
    return infile.good();
}