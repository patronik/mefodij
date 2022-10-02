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

tuple<wstring, int, int> Parser::getLastLocation()
{
    int lastProccessedPos = pos - 1;
    if (srcData.count(lastProccessedPos) == 0) {
        throw runtime_error("Parser position '" + to_string(lastProccessedPos) + "' does not exist.");
    }

    auto lastProcessed = srcData[lastProccessedPos];
    
    int relativePos = 1;
    while(srcData.count(--lastProccessedPos) != 0) {
        auto processedData = srcData[lastProccessedPos];
        if (processedData.first < lastProcessed.first) {
            break;
        }
        relativePos++;
    }

    return {lastProcessed.second, lastProcessed.first, relativePos};
}

void Parser::insertSource(wstring wfilename)
{
    if (!fileExist(wideStrToStr(wfilename).c_str())) {
        throw runtime_error("File '" + wideStrToStr(wfilename) + "' does not exist.");
    }

    wstring source = readWideFile(wideStrToStr(wfilename).c_str());

    src.insert(pos, source);

    map<int, pair<int, wstring>> newSrcData;
    
    int srcIdx = 0;
    if (pos > 0) {
        srcIdx = 0;
        while (srcIdx < pos) {
            newSrcData[srcIdx] = srcData[srcIdx];
            srcIdx++;
        }
    }

    int b = 0;
    int  linesCnt = 0;
    while (b < source.size()) {
        srcIdx = b + pos;
        if (srcIdx == 0) {
            newSrcData[srcIdx] = {1, wfilename};
        } else if (srcIdx > 0) {
            if (src[srcIdx - 1] == L'\n') {
                newSrcData[srcIdx] = {
                    newSrcData[srcIdx - 1].first + 1, 
                    wfilename
                };
                linesCnt++;
            } else {
                newSrcData[srcIdx] = {
                    newSrcData[srcIdx - 1].first, 
                    wfilename
                };
            }
        }
        b++;
    }

    srcIdx = pos;
    while (srcIdx < srcData.size()) {
        pair<int, wstring> symbolData = srcData[srcIdx];
        newSrcData[srcIdx + source.size()] = {
            symbolData.first + linesCnt, 
            symbolData.second
        };
        srcIdx++;
    }

    srcData = newSrcData;

    /*
        for (const auto & tmp: srcData) {
            wchar_t s = src[tmp.first];
            if (s == L'\n') {
                s = L'n';
            }
            wcout << s 
                << " " 
                << tmp.second.first 
                << " " 
                << tmp.second.second 
                << "\n";
        }
        wcout << "\n\n\n";
    */
}