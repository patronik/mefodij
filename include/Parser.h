#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>

using namespace std;

/**
 * Parser is responsible for reading, parsing and navigating through the code
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

    const wstring statementFunc = L"функція";
    const wstring statementReturn = L"повернути";
    const wstring statementIf = L"якщо";
    const wstring statementBreak = L"стоп";
    const wstring statementFor = L"цикл";
    const wstring statementPrint = L"друк";
    const wstring statementImport = L"імпорт";

    // Current parser position
    int pos = 0;

    // Source code
    wstring src{};
    
    // Source code lines and files 
    vector<tuple<wstring, int, int, wchar_t>> sourceEntries;

    // Dynamic source
    wstring dynamicSrc{};

    void insertSource(wstring wfilename);
    tuple<wstring, int, int> getLastLocation();
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