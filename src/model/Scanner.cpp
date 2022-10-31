#include <regex>
#include <fstream>
#include <iostream>
#include "Scanner.h"

bool Scanner::skipWhitespace() {
    bool changed = false;
    while (index < program.size() && std::isspace(program[index])) {
        if (program[index] == '\n') {
            currentLine++;
            changed = true;
        }
        index++;
    }
    return changed;
}

bool Scanner::skipComment() {
    bool changed = false;
    std::string indexSubstr = program.substr(index, program.size()-index);
    if (indexSubstr.rfind("//", 0) == 0) {
        changed = true;
        while (index < program.size() && program[index] != '\n')
            index++;
    }
    return changed;
}

bool Scanner::stringConstant() {
    std::regex strConstantRegex{"^\"([a-zA-Z0-9_]*)\""};
    std::string indexSubstr = program.substr(index, program.size()-index);
    auto regexIt = std::sregex_iterator(indexSubstr.begin(), indexSubstr.end(), strConstantRegex);
    if (regexIt != std::sregex_iterator()) {
        pif.emplace_back("strConstant", -2);
        symbolTable.addStringConstant(regexIt->str());
        index += (int)regexIt->str().size()+1;
        return true;
    }

    strConstantRegex = std::regex{"^\"[^\"]+\""};
    regexIt = std::sregex_iterator(indexSubstr.begin(), indexSubstr.end(), strConstantRegex);
    if (regexIt != std::sregex_iterator()) {
        throw std::runtime_error("Lexical error: Invalid characters inside string on line " + std::to_string(currentLine));
    }

    strConstantRegex = std::regex{"^\""};
    regexIt = std::sregex_iterator(indexSubstr.begin(), indexSubstr.end(), strConstantRegex);
    if (regexIt != std::sregex_iterator()) {
        throw std::runtime_error("Lexical error: String not closed on line " + std::to_string(currentLine));
    }
    return false;
}

bool Scanner::intConstant() {
    std::regex intConstantRegex{"^([+-]?[1-9]\\d*|0)"};
    std::string indexSubstr = program.substr(index, program.size()-index);
    auto regexIt = std::sregex_iterator(indexSubstr.begin(), indexSubstr.end(), intConstantRegex);
    if (regexIt != std::sregex_iterator()) {
        std::string token = regexIt->str();
        if (!pif.empty()) {
            int lastValue = pif.back().second;
            if ((token[0] == '+' || token[0] == '-') && (lastValue == 0 || lastValue == -1 || lastValue == -2)) {
                return false;
            }
        }
        pif.emplace_back("intConstant", -1);
        symbolTable.addIntConstant(token);
        index += (int)regexIt->str().size();
        return true;
    }
    return false;
}

bool Scanner::tokenFromList() {
    std::string indexSubstr = program.substr(index, program.size()-index);
    for (const std::string &token: tokens) {
        if (indexSubstr.rfind(token, 0) == 0) {
            pif.emplace_back(token, 0);
            index += (int)token.size();
            return true;
        }
    }
    return false;
}

bool Scanner::identifier() {
    std::regex identifierRegex{"^([a-zA-Z_][a-zA-Z0-9_]*)"};
    std::string indexSubstr = program.substr(index, program.size()-index);
    auto regexIt = std::sregex_iterator(indexSubstr.begin(), indexSubstr.end(), identifierRegex);
    if (regexIt != std::sregex_iterator()) {
        std::string token = regexIt->str();
        symbolTable.addIdentifier(token);
        pif.emplace_back("identifier", symbolTable.getIdentifierPosition(token).first);
        index += (int)regexIt->str().size()+1;
        return true;
    }
    return false;
}

void Scanner::nextToken() {
    while (true) {
        if (!skipWhitespace() && !skipComment())
            break;
    }
    if (index == program.size())
        return;
    if (tokenFromList() || identifier() || stringConstant() || intConstant())
        return;
    throw std::runtime_error("Lexical error: Cannot classify token on line " + std::to_string(currentLine));
}

void Scanner::scan() {
    while (index < program.size())
        nextToken();
}

void Scanner::outST() {
    std::ofstream out("ST.out");
    out << symbolTable.toString();
    out.close();
}

void Scanner::outPIF() {
    std::ofstream out("PIF.out");
    for (const auto &p: pif) {
        out << p.first << " -> " << p.second << "\n";
    }
    out.close();
}
