#pragma once


#include <vector>
#include <string>

class HashTable {
private:
    std::vector<std::vector<std::string>> items;
    int size;
    int addedCount = 0;
    double loadFactor = 0.75;

    /**
     * Returns the hash of a given keyword calculated as the sum of char values modulo size
     */
    int hash(const std::string &keyword) const;

    /**
     * Used to resize the list which implements the hash table when the added count surpasses the load factor
     */
    void resize();
public:
    /**
     * Creates a new symbol table with a given size
     * @param size Size of the created symbol table
     */
    HashTable();

    /**
     * Checks if the symbol table contains a keyword
     * @param keyword Given keyword which is checked to exist in the symbol table
     * @return true if the keyword exists, otherwise false
     */
    bool contains(const std::string &keyword);

    /**
     * Adds a new keyword to the symbol table if it doesn't already exist
     * @param keyword Given keyword which will be inserted in the symbol table
     * @return true if the keyword was added, otherwise false if it was already in the symbol table
     */
    bool add(const std::string &keyword);

    /**
     * Removes a keyword from the symbol table if it exists
     * @param keyword Given keyword which will be removed from the symbol table
     * @return true if the keyword was removed, otherwise false if it was not found in the symbol table
     */
    bool remove(const std::string &keyword);

    /**
     * Returns a pair containing the key of the keyword and the index of the keyword in its specific list
     */
    std::pair<int, int> getPosition(const std::string &keyword);

    /**
     * Returns a string representation of the hash table
     */
    std::string toString();
};
