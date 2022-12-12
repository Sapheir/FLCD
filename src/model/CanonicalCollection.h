#pragma once
#include <vector>
#include <map>
#include "State.h"

class CanonicalCollection {
public:
    std::map<std::pair<int, std::string>, int> adjacencyList;
    std::vector<State> states;

    void addState(const State &state);
    void connectStates(const int &firstStateIndex, std::string &symbol, const int &secondStateIndex);
};
