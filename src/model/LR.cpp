#include "LR.h"

LR::LR(Grammar &grammar): grammar{grammar}, workingGrammar{this->grammar.getEnrichedGrammar()} {
    orderedProductions = workingGrammar.getProductionSet().getOrderedProductions();
}

std::string LR::getDotPrecededNonTerminal(const Item &item) {
    std::string term;
    if (item.dotPosition > 0 && item.dotPosition < item.rhs.size())
        term = item.rhs[item.dotPosition];
    if (grammar.getNonTerminals().find(term) == std::string::npos)
        return "";
    return term;
}

State LR::Closure(const Item &item) {
    std::set<Item> oldClosure, currentClosure;
    currentClosure.insert(item);
    do {
        oldClosure = currentClosure;
        std::set<Item> newClosure;
        for (const auto &it: currentClosure) {
            std::string nonTerminal = getDotPrecededNonTerminal(it);
            if (nonTerminal.empty())
                continue;
            for (auto &production: grammar.getProductionSet().getProductionsOf(nonTerminal)) {
                Item currentItem{nonTerminal, production, 0};
                newClosure.insert(currentItem);
            }
        }
        currentClosure = newClosure;
    } while (oldClosure.size() != currentClosure.size() || !std::equal(oldClosure.begin(), oldClosure.end(), currentClosure.begin()));
    return State{currentClosure};
}

State LR::goTo(const State &state, const std::string &element) {
    std::set<Item> result;
    for (auto &it: state.items) {
        std::string nonTerminal = it.dotPosition > 0 && it.dotPosition < it.rhs.size() ? it.rhs[it.dotPosition] : "";
        if (nonTerminal == element) {
            Item nextItem{it.lhs, it.rhs, it.dotPosition + 1};
            for (const auto &it2: Closure(nextItem).items) {
                result.insert(it2);
            }
        }
    }
    return State{result};
}

CanonicalCollection LR::canonicalCollection() {
    CanonicalCollection canonicalCollection;
    canonicalCollection.addState(Closure(Item{workingGrammar.getStartingSymbol(),
                                         workingGrammar.getProductionSet().getProductionsOf(workingGrammar.getStartingSymbol())[0], 0}));
    int i = 0;
    while (i < canonicalCollection.states.size()) {
        for (auto &symbol: canonicalCollection.states[i].getSymbolsSucceedingDot()) {
            State newState = goTo(canonicalCollection.states[i], symbol);
            int indexInStates = -1;
            for (int j = 0; j<canonicalCollection.states.size(); j++)
                if (canonicalCollection.states[j] == newState)
                    indexInStates = j;
            if (indexInStates == -1) {
                canonicalCollection.addState(newState);
                indexInStates = (int)canonicalCollection.states.size() - 1;
            }
            canonicalCollection.connectStates(i, symbol, indexInStates);
        }
        i++;
    }
    return canonicalCollection;
}
