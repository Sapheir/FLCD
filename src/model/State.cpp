#include <algorithm>
#include "State.h"
#include "ProductionSet.h"
#include "Grammar.h"

State::State(std::set<Item> &items): items{std::move(items)} {
    if (this->items.size() == 1 && (*this->items.begin()).rhs.size() == (*this->items.begin()).dotPosition && (*this->items.begin()).lhs == getEnrichedGrammarStartingSymbol())
        stateType = ACCEPT;
    else if (this->items.size() == 1 && (*this->items.begin()).rhs.size() == (*this->items.begin()).dotPosition)
        stateType = REDUCE;
    else if (!this->items.empty() && std::all_of(this->items.begin(), this->items.end(), [](const Item &item){return item.rhs.size() > item.dotPosition;}))
        stateType = SHIFT;
    else if (this->items.size() > 1 && std::all_of(this->items.begin(), this->items.end(), [](const Item &item){return item.rhs.size() == item.dotPosition;}))
        stateType = REDUCE_REDUCE_CONFLICT;
    else
        stateType = SHIFT_REDUCE_CONFLICT;
}

std::vector<std::string> State::getSymbolsSucceedingDot() {
    std::set<std::string> symbols;
    for (const auto &item: items) {
        if (item.dotPosition >= 0 && item.dotPosition < item.rhs.size())
            symbols.insert(item.rhs[item.dotPosition]);
    }
    std::vector<std::string> uniqueSymbols;
    std::copy(symbols.begin(), symbols.end(), std::back_inserter(uniqueSymbols));
    return uniqueSymbols;
}

std::string State::toString() {
    std::vector<std::string> itemStrings;
    for (auto item: items) {
        itemStrings.push_back(item.toString());
    }
    return stateTypeToString(stateType) + " - " + getVectorString(itemStrings);
}

bool State::operator==(const State &state) const {
    return stateType == state.stateType && items == state.items;
}
