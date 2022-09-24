#include "../include/Parser.h"
#include "../include/tools.h"

Parser::Parser()
{
    printableChars = printableNumbers + ukrainianLetters + englishLetters + printableSymbols;
    lettersNumsUnderscore = ukrainianLetters + englishLetters + printableNumbers + wstring(L"_");
    printableLetters = ukrainianLetters + englishLetters;
}

bool Parser::isSpace(wchar_t symbol)
{
    return printableChars.find(symbol) == wstring::npos;
}

void Parser::skipSpaces()
{
    while(pos < src.size() && isSpace(src.at(pos))) {
        pos++;
    }
}

wchar_t Parser::readChar(bool toLower, bool allChars)
{
    if (dynamicSrc.size() > 0) {
        wchar_t result = dynamicSrc.back();
        dynamicSrc.pop_back();
        return result;
    }

    if (!allChars) {
        skipSpaces();
    }

    if (pos >= src.size()) {
        // end of script
        return endOfFile;
    }

    wchar_t symbol = src.at(pos++);
    if (toLower) {
        symbol = towlower(symbol);
    }

    return symbol;
}

void Parser::unreadChar(int numOfSteps)
{
    do {
        pos--;
        while (isSpace(src.at(pos))) {
            pos -= 1;
        }
        numOfSteps--;
    } while (numOfSteps > 0);
}

void Parser::fastForward(vector<wchar_t> terminators, wchar_t nestedMarker)
{
    bool inSingleQuotedStr = false;
    bool inDoubleQuotedStr = false;
    int depth = 0;

    wchar_t prevChar = L'\0';
    wchar_t symbol;
    while (symbol = readChar(false, true)) {
         if (symbol == L'\'') {
            if (!inSingleQuotedStr) {
                if (!inDoubleQuotedStr) {
                    inSingleQuotedStr = true;
                }
            } else if (prevChar != L'\\') {
                inSingleQuotedStr = false;
            }
        }

        if (symbol == L'"') {
            if (!inDoubleQuotedStr) {
                if (!inSingleQuotedStr) {
                    inDoubleQuotedStr = true;
                }
            } else if (prevChar != L'\\') {
                inDoubleQuotedStr = false;
            }
        }

        if (!inSingleQuotedStr && !inDoubleQuotedStr) {
            if (nestedMarker && symbol == nestedMarker) {
                depth++;
                readChar(false, true);
            } else if (inVector<wchar_t>(terminators, symbol)) {
                if (depth == 0) {
                    break;
                } else {
                    depth--;
                }
            }
        }

        prevChar = symbol;
    }
}

void Parser::skipBlockOrStatement()
{
    wchar_t symbol;
    if ((symbol = readChar()) == endOfFile) {
        // EOF is achieved
        return;
    }

    if (symbol != L'{') {
        // skip 1 statement
        fastForward({L';'});

    } else {
        // skip 1 code block
        fastForward({L'}'} , L'{');
    }
}

bool Parser::parseCharacterSequence(wchar_t symbol, wstring & buffer)
{
    if (printableLetters.find(symbol) != wstring::npos) {
        buffer += symbol;
        while (symbol = readChar(false, true)) {
            if (lettersNumsUnderscore.find(symbol) != wstring::npos) {
                buffer += symbol;
                continue;
            }
            if (!isSpace(symbol)) {
                unreadChar();
            }
            break;
        }
        return true;
    }
    return false;
}