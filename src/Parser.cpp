#include "../include/Parser.h"
#include "../include/tools.h"
#include "../include/Atom/AtomType.h"
#include "../include/Atom.h"

namespace Mefody {

    Parser::Parser()
    {
        printableChars = printableNumbers + ukrainianLetters + englishLetters + printableSymbols;
        lettersNumsUnderscore = ukrainianLetters + englishLetters + printableNumbers + wstring(L"_");
        printableLetters = ukrainianLetters + englishLetters;
        hexChars = L"0123456789ABCDEFabcdef";
        binChars = L"01";

        reservedKeywords = {
            AtomType::castInt, 
            AtomType::castDouble, 
            AtomType::castString, 
            AtomType::castArray, 
            AtomType::castBool, 
            AtomType::castNull,
            statementLem,
            statementConst,
            statementFunc,
            statementExit,
            statementIf,
            statementBreak,
            statementFor,
            statementPrint,
            statementImport,
            statementElse
        };
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

    void Parser::unreadChar(int numOfSteps, bool allChars)
    {
        do {
            pos--;
            if (!allChars) {
                while (isSpace(src.at(pos))) {
                    pos -= 1;
                }
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
                } else if (Mefody::Tools::inVector<wchar_t>(terminators, symbol)) {
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

    tuple<wstring, int, int> Parser::getLastLocation()
    {
        try {
            auto curEntry = sourceEntries.at(pos - 1);
            return {get<0>(curEntry), get<1>(curEntry), get<2>(curEntry)};   
        }
        catch (const out_of_range & oor) {
            throw runtime_error("Element at index '" + to_string(pos - 1) + "' does not exist.");
        }
    }

    void Parser::insertSource(wstring wfilename)
    {
        if (!Mefody::Tools::fileExist(Mefody::Tools::wideStrToStr(wfilename).c_str())) {
            throw runtime_error("File '" + Mefody::Tools::wideStrToStr(wfilename) + "' does not exist.");
        }

        wstring source = Mefody::Tools::readWideFile(Mefody::Tools::wideStrToStr(wfilename).c_str());

        src.insert(pos, source);

        vector<tuple<wstring, int, int, wchar_t>>::iterator prev;

        if (pos == 0) {
            for (int i = 0; i < source.size(); i++) {
                if (i == 0) {
                    sourceEntries.insert(
                        sourceEntries.begin(), 
                        {wfilename, 1, 1, source.at(i)}
                    );
                    prev = sourceEntries.begin();
                } else {
                    int line = 1;
                    int relPos = 1;
                    if (get<3>(*prev) == L'\n') {
                        line = get<1>(*prev) + 1;
                        relPos = 1;
                    } else {
                        line = get<1>(*prev);
                        relPos = get<2>(*prev) + 1;
                    }
                    sourceEntries.insert(
                        sourceEntries.begin() + i, 
                        {wfilename, line, relPos, source.at(i)}
                    );
                    prev = (sourceEntries.begin() + i);
                }
            }
        } else {
            // Find insert position
            for (int i = 0; i < source.size(); i++) {
                auto baseInsertPos = sourceEntries.begin() + pos;

                int line = 1;
                int relPos = 1;

                if (i > 0) {
                    prev = (baseInsertPos + i) - 1;
                    if (get<3>(*prev) == L'\n') {
                        line = get<1>(*prev) + 1;
                        relPos = 1;
                    } else {
                        line = get<1>(*prev);
                        relPos = get<2>(*prev) + 1;
                    }
                }

                sourceEntries.insert(
                    baseInsertPos + i, 
                    {
                        wfilename, 
                        line, 
                        relPos, 
                        source.at(i)
                    }
                );
            }
        }
    }

}