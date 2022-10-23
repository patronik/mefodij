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

    enum StateType {
      beforeStmt,
      inComment,
      inStmt,
      afterStmt,
      flowControl,
    }; 

    StateType state = beforeStmt;
    
    wchar_t endOfFile = L'\0';
    wstring printableNumbers{L"0123456789"};
    wstring ukrainianLetters{L"АаБбВвГгҐґДдЕеЄєЖжЗзИиІіЇїЙйКкЛлМмНнОоПпРрСсТтУуФфХхЦцЧчШшЩщЬьЮюЯя"};
    wstring englishLetters{L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"};
    wstring printableSymbols{L"!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"};
    wstring hexChars;
    wstring binChars;
    wstring lettersNumsUnderscore;
    wstring printableLetters;
    wstring printableChars;

    const wstring statementLem = L"лем";
    const wstring statementConst = L"конст";
    const wstring statementFunc = L"функція";
    const wstring statementExit = L"вихід";
    const wstring statementIf = L"умова";
    const wstring statementBreak = L"стоп";
    const wstring statementFor = L"цикл";
    const wstring statementPrint = L"друк";
    const wstring statementImport = L"імпорт";
    const wstring statementElse = L"або";

    // Current parser position
    int pos = 0;

    // Source code
    wstring src{};
    
    // Source code lines and files 
    vector<tuple<wstring, int, int, wchar_t>> sourceEntries{};

    // Dynamic source
    wstring dynamicSrc{};

    // Reserved keywords
    vector<wstring> reservedKeywords{};

    void insertSource(wstring wfilename);
    tuple<wstring, int, int> getLastLocation();
    bool isSpace(wchar_t symbol);
    void skipSpaces();
    wchar_t readChar(bool toLower = false, bool allChars = false);
    void unreadChar(int numOfSteps = 1, bool allChars = false);
    void fastForward(vector<wchar_t> terminators, wchar_t nestedMarker = L'\0');
    void skipBlockOrStatement();
    bool parseCharacterSequence(wchar_t symbol, wstring & buffer);

    public:
    Parser();
};

#endif