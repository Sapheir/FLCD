#include <iostream>
#include "model/FiniteAutomaton.h"
#include "model/Grammar.h"

std::string getVectorVectorString(const std::vector<std::vector<std::string>> &v) {
    std::string s = "[";
    for (const auto &insideV: v) {
        s += "[";
        for (const auto &val: insideV)
            s += val + ",";
        s.pop_back();
        s += "],";
    }
    s.pop_back();
    s += "]";
    return s;
}

int main() {
    Grammar grammar{"..\\g2.in"};
    std::cout << "NonTerminals: " << grammar.getNonTerminals() << "\n";
    std::cout << "Terminals: " << grammar.getTerminals() << "\n";
    std::cout << "Starting symbol: " << grammar.getStartingSymbol() << "\n";
    std::cout << "Production set: " << grammar.getProductionSet().toString() << "\n";
    std::cout << (grammar.checkCFG() ? "CFG\n" : "Not CFG\n");
    while (true) {
        std::cout << "\nEnter a NonTerminal (or esc to quit): \n";
        std::string nonTerminal;
        std::cin >> nonTerminal;
        if (nonTerminal == "esc")
            break;
        auto productions = grammar.getProductionSet().getProductionsOf(nonTerminal);
        std::cout << (productions.empty() ? "No productions\n" : getVectorVectorString(productions));
    }
    return 0;
}