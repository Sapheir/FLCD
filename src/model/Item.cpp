#include "Item.h"

Item::Item(const std::string &lhs, const std::vector<std::string> &rhs, const int &dotPosition):
    lhs{lhs}, rhs{rhs}, dotPosition{dotPosition} {
}

std::string Item::toString() {
    std::string rhs1, rhs2;
    for (int i = 0; i<rhs.size(); i++) {
        if (i < dotPosition)
            rhs1 += rhs[i];
        else
            rhs2 += rhs[i];
    }
    return lhs + " -> " + rhs1 + "." + rhs2;
}

bool Item::operator<(const Item &item) const {
    return this->dotPosition < item.dotPosition;
}

bool Item::operator==(const Item &item) const {
    return lhs == item.lhs && dotPosition == item.dotPosition && rhs == item.rhs;
}
