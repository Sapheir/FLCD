#pragma once


#include "Grammar.h"
#include "Item.h"
#include "State.h"
#include "CanonicalCollection.h"

class LR {
private:
    Grammar grammar, workingGrammar;
    std::vector<std::pair<std::string, std::vector<std::vector<std::string>>>> orderedProductions;
    std::string getDotPrecededNonTerminal(const Item &item);
    State Closure(const Item &item);
    State goTo(const State &state, const std::string &element);


public:
    explicit LR(Grammar &grammar);
    CanonicalCollection canonicalCollection();
};

