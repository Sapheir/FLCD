#pragma once


#include <string>
#include <vector>

class Item {
public:
    std::string lhs;
    std::vector<std::string> rhs;
    int dotPosition;

    bool operator <(const Item& item) const;
    bool operator ==(const Item& item) const;

    Item(const std::string &lhs, const std::vector<std::string> &rhs, const int &dotPosition);

    std::string toString();
};
