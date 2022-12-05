#pragma once


#include <string>
#include <map>
#include <vector>

class ProductionSet {
private:
    std::map<std::vector<std::string>, std::vector<std::vector<std::string>>> productions;
    static std::string getVectorString(const std::vector<std::string> &v);

public:
    ProductionSet();
    explicit ProductionSet(std::map<std::vector<std::string>, std::vector<std::vector<std::string>>> productions);
    std::vector<std::vector<std::string>> getProductionsOf(const std::vector<std::string> &lhs);
    std::vector<std::vector<std::string>> getProductionsOf(const std::string &lhs);
    std::map<std::vector<std::string>, std::vector<std::vector<std::string>>> getAllProductions();
    void addProduction(const std::vector<std::string> &lhs, const std::vector<std::string> &rhs);
    std::string toString();
};
