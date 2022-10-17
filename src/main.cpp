#include <cassert>
#include <iostream>
#include "data_structures/HashTable.h"

int main() {
    HashTable hashTable;

    std::cout << "Starting simple tests\n";
    assert(hashTable.add("abc") == true);
    assert(hashTable.contains("abc") == true);
    assert(hashTable.add("abc") == false);
    assert(hashTable.add("y") == true);

    assert(hashTable.remove("x") == false);
    assert(hashTable.remove("abc") == true);
    assert(hashTable.contains("abc") == false);
    assert(hashTable.add("abc") == true);
    assert(hashTable.contains("abc") == true);

    std::cout << "Finished simple tests\n";
    return 0;
}