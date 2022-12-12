#include "Grammar.h"

Grammar::Grammar(const std::string &filename) {
    std::vector<std::string> lines;
    std::ifstream in(filename);
    std::string line;
    while (std::getline(in, line)) {
        lines.push_back(line);
    }

    // non-terminals are on the first line and separated by spaces
    nonTerminals = splitInput(lines[0], " ");
    //terminals are on the second line and separated by spaces
    terminals = splitInput(lines[1], " ");
    //starting symbol is on the third line
    startingSymbol = lines[2];

    //the productionSet is on the remaining lines
    productionSet = ProductionSet{};
    for (int i = 3; i < lines.size(); i++) {
        std::vector<std::string> production = splitInput(lines[i]," -> ");
        std::vector<std::string> lhs = splitInput(production[0], " ");

        std::vector<std::string> rhs = splitInput(production[1], " ");
        rhs.erase(std::remove(rhs.begin(), rhs.end(), "epsilon"), rhs.end());
        productionSet.addProduction(lhs, rhs);
    }

    isEnriched = false;
}

bool Grammar::checkCFG() {
    auto productions = productionSet.getAllProductions();
    return std::all_of(productions.begin(), productions.end(), [&](auto production){
        if (production.first.size() != 1)
            return false;
        bool containsValue = std::find(nonTerminals.begin(), nonTerminals.end(), production.first[0]) != nonTerminals.end();
        if (!containsValue)
            return false;
        return true;
    });
}

std::vector<std::string> Grammar::splitInput(std::string &input, const std::string &delimiter) {
    size_t pos;
    std::string token;
    std::vector<std::string> split;
    while ((pos = input.find(delimiter)) != std::string::npos) {
        token = input.substr(0, pos);
        split.push_back(token);
        input.erase(0, pos + delimiter.length());
    }
    split.push_back(input);
    return split;
}

std::string Grammar::getVectorString(const std::vector<std::string> &v) {
    std::string s = "[";
    for (const auto &val: v)
        s += val + ",";
    s.pop_back();
    s += "]";
    return s;
}

std::string Grammar::getNonTerminals() {
    return getVectorString(nonTerminals);
}

std::string Grammar::getTerminals() {
    return getVectorString(terminals);
}

std::string Grammar::getStartingSymbol() {
    return startingSymbol;
}

ProductionSet Grammar::getProductionSet() {
    return productionSet;
}

Grammar::Grammar(std::vector<std::string> &nonTerminals, std::vector<std::string> &terminals,
                 std::string &startingSymbol, ProductionSet &productionSet):
                 nonTerminals{std::move(nonTerminals)}, terminals{std::move(terminals)}, startingSymbol{std::move(startingSymbol)}, productionSet{std::move(productionSet)}{
    isEnriched = true;
}

Grammar Grammar::getEnrichedGrammar() {
    if (isEnriched) {
        return *this;
    }
    std::vector<std::string> newNonTerminals = nonTerminals;
    newNonTerminals.push_back(getEnrichedGrammarStartingSymbol());
    Grammar newGrammar{newNonTerminals, terminals, startingSymbol, productionSet};
    newGrammar.productionSet.addProduction({getEnrichedGrammarStartingSymbol()}, {startingSymbol});
    return newGrammar;
}

std::string getEnrichedGrammarStartingSymbol() {
    return "S0";
}
