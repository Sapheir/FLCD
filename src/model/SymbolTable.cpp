#include "SymbolTable.h"

void SymbolTable::addIdentifier(const std::string &name) {
    identifierHashTable.add(name);
}

void SymbolTable::addIntConstant(const std::string &constantInt) {
    intConstantsHashTable.add(constantInt);
}

void SymbolTable::addStringConstant(const std::string &constantString) {
    stringConstantsHashTable.add(constantString);
}

bool SymbolTable::hasIdentifier(const std::string &name) {
    return identifierHashTable.contains(name);
}

bool SymbolTable::hasIntConstant(const std::string &constantInt) {
    return intConstantsHashTable.contains(constantInt);
}

bool SymbolTable::hasStringConstant(const std::string &constantString) {
    return stringConstantsHashTable.contains(constantString);
}

std::pair<int, int> SymbolTable::getIdentifierPosition(const std::string &name) {
    return identifierHashTable.getPosition(name);
}

std::pair<int, int> SymbolTable::getIntConstantPosition(const std::string &constantInt) {
    return intConstantsHashTable.getPosition(constantInt);
}

std::pair<int, int> SymbolTable::getStringConstantPosition(const std::string &constantString) {
    return stringConstantsHashTable.getPosition(constantString);
}

bool SymbolTable::removeIdentifier(const std::string &name) {
    return identifierHashTable.remove(name);
}

bool SymbolTable::removeIntConstant(const std::string &constantInt) {
    return intConstantsHashTable.remove(constantInt);
}

bool SymbolTable::removeStringConstant(const std::string &constantString) {
    return stringConstantsHashTable.remove(constantString);
}

std::string SymbolTable::toString() {
    std::string stringSymbolTable;
    stringSymbolTable += "Identifiers: \n" + identifierHashTable.toString();
    stringSymbolTable += "Int constants: \n" + intConstantsHashTable.toString();
    stringSymbolTable += "String constants: \n" + stringConstantsHashTable.toString();
    return stringSymbolTable;
}
