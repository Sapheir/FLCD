#pragma once


#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "ProductionSet.h"

class Grammar {
private:
    std::vector<std::string> nonTerminals, terminals;
    std::string startingSymbol;
    ProductionSet productionSet;

    static std::string getVectorString(const std::vector<std::string> &v);
    static std::vector<std::string> splitInput(std::string &input, const std::string &delimiter);

public:
    explicit Grammar(const std::string &filename);
    std::string getNonTerminals();
    std::string getTerminals();
    std::string getStartingSymbol();
    ProductionSet getProductionSet();
    bool checkCFG();

};
