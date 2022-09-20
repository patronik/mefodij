#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

using namespace std;

/**
 * Parser is responsible for reading and navigating through the code
 */
class Parser
{
    protected:
    wchar_t endOfFile = L'\0';
    wstring printableNumbers{L"0123456789"};
    wstring ukrainianLetters{L"АаБбВвГгҐґДдЕеЄєЖжЗзИиІіЇїЙйКкЛлМмНнОоПпРрСсТтУуФфХхЦцЧчШшЩщЬьЮюЯя"};
    wstring englishLetters{L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"};
    wstring printableSymbols{L"!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"};
    wstring lettersNumsUnderscore;
    wstring printableLetters;
    wstring printableChars;

    // Source code
    wstring src{};

    // Current parser position
    int pos = 0;

    // Dynamic source
    wstring dynamicSrc{};

    bool isSpace(wchar_t symbol);
    void skipSpaces();
    wchar_t readChar(bool toLower = false, bool allChars = false);
    void unreadChar(int numOfSteps = 1);
    void fastForward(vector<wchar_t> terminators, wchar_t nestedMarker = L'\0');
    void skipBlockOrStatement();
    bool parseCharacterSequence(wchar_t symbol, wstring & buffer);
    public:
    Parser();
};

#endif