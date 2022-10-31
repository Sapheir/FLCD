cmake_minimum_required(VERSION 3.22)
project(FLCD)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(FLCD
        src/main.cpp
        src/data_structures/HashTable.h src/data_structures/HashTable.cpp
        src/model/SymbolTable.h src/model/SymbolTable.cpp
        src/model/Scanner.h src/model/Scanner.cpp)
