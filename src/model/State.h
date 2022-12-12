#pragma once


#include <set>
#include "Item.h"
#include "StateType.h"

class State {
public:
    std::set<Item> items;
    StateType stateType;

    explicit State(std::set<Item> &items);
    std::vector<std::string> getSymbolsSucceedingDot();
    std::string toString();

    bool operator ==(const State& state) const;
};
