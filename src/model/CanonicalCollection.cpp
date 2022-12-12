#include "CanonicalCollection.h"

void CanonicalCollection::connectStates(const int &firstStateIndex, std::string &symbol, const int &secondStateIndex) {
    adjacencyList[{firstStateIndex, std::move(symbol)}] = secondStateIndex;
}

void CanonicalCollection::addState(const State &state) {
    states.push_back(state);
}
