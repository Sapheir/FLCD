#pragma once


#include "data_structures/HashTable.h"

class SymbolTable {
private:
    HashTable identifierHashTable, intConstantsHashTable, stringConstantsHashTable;

public:
    void addIdentifier(const std::string &name);
    void addIntConstant(const std::string &constantInt);
    void addStringConstant(const std::string &constantString);

    bool hasIdentifier(const std::string &name);
    bool hasIntConstant(const std::string &constantInt);
    bool hasStringConstant(const std::string &constantString);

    bool removeIdentifier(const std::string &name);
    bool removeIntConstant(const std::string &constantInt);
    bool removeStringConstant(const std::string &constantString);

    std::pair<int, int> getIdentifierPosition(const std::string &name);
    std::pair<int, int> getIntConstantPosition(const std::string &constantInt);
    std::pair<int, int> getStringConstantPosition(const std::string &constantString);

    std::string toString();
};
