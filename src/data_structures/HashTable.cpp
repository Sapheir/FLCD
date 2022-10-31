#include <algorithm>
#include "data_structures/HashTable.h"

HashTable::HashTable() {
    this->size = 109;
    items.resize(this->size);
}

int HashTable::hash(const std::string &keyword) const {
    int sum = 0;
    for (const char &ch: keyword) {
        sum += (int) ch;
    }
    return abs(sum % this->size);
}

bool HashTable::contains(const std::string &keyword) {
    int key = hash(keyword);
    return std::find(items[key].begin(), items[key].end(), keyword) != items[key].end();
}

bool HashTable::add(const std::string &keyword) {
    if (contains(keyword)) {
        return false;
    }
    int key = hash(keyword);
    items[key].push_back(keyword);
    addedCount++;
    if (addedCount > size * loadFactor) {
        resize();
    }
    return true;
}

bool HashTable::remove(const std::string &keyword) {
    if (contains(keyword)) {
        int key = hash(keyword);
        items[key].erase(std::remove_if(items[key].begin(), items[key].end(),
                                        [keyword](const std::string &value) {
                                                    return value == keyword;
                                            }),
                         items[key].end());
        return true;
    }
    return false;
}

std::pair<int, int> HashTable::getPosition(const std::string &keyword) {
    if (contains(keyword)) {
        int key = hash(keyword), listIndex = 0;
        for (const std::string &value: items[key]) {
            if (value == keyword) {
                return {key, listIndex};
            } else {
                listIndex++;
            }
        }
    }
    return {-1, -1};
}

void HashTable::resize() {
    this->size *= 2;
    std::vector<std::vector<std::string>> oldItems = items;
    items.clear();
    items.resize(this->size);
    for (int i = 0; i<this->size/2; i++) {
        for (const auto &value: oldItems[i]) {
            this->add(value);
        }
    }
}

std::string HashTable::toString() {
    std::string stringHashTable;
    for (int i = 0; i<this->size; i++) {
        for (const auto &value: items[i]) {
            stringHashTable += std::to_string(i) + ": " + value + "\n";
        }
    }
    return stringHashTable;
}
