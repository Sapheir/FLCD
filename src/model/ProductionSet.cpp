#include "ProductionSet.h"

ProductionSet::ProductionSet() = default;

ProductionSet::ProductionSet(std::map<std::vector<std::string>, std::vector<std::vector<std::string>>> productions) {
    productions = std::move(productions);
}

std::vector<std::vector<std::string>> ProductionSet::getProductionsOf(const std::vector<std::string> &lhs) {
    return productions[lhs];
}

std::vector<std::vector<std::string>> ProductionSet::getProductionsOf(const std::string &lhs) {
    return getProductionsOf(std::vector<std::string>{lhs});
}

std::map<std::vector<std::string>, std::vector<std::vector<std::string>>> ProductionSet::getAllProductions() {
    return productions;
}

void ProductionSet::addProduction(const std::vector<std::string> &lhs, const std::vector<std::string> &rhs) {
    productions[lhs].push_back(rhs);
}

std::string ProductionSet::toString() {
    std::string s;
    for (const auto &it: productions) {
        std::string key = getVectorString(it.first);
        for (const auto &val: it.second)
            s += key + " -> " + getVectorString(val) + "\n";
    }
    return s;
}

std::vector<std::pair<std::string, std::vector<std::vector<std::string>>>> ProductionSet::getOrderedProductions() {
    std::vector<std::pair<std::string, std::vector<std::vector<std::string>>>> orderedProductions;
    for (const auto &it: productions) {
        orderedProductions.emplace_back(it.first[0], it.second);
    }
    return orderedProductions;
}

std::string getVectorString(const std::vector<std::string> &v) {
    std::string s = "[";
    for (const auto &val: v)
        s += val + ",";
    s.pop_back();
    s += "]";
    return s;
}

std::string getVectorString(const std::set<std::string> &s) {
    std::vector<std::string> v;
    std::copy(s.begin(), s.end(), std::back_inserter(v));
    return getVectorString(v);
}
