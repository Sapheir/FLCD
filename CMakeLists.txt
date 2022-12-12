cmake_minimum_required(VERSION 3.22)
project(FLCD)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(FLCD
        src/main.cpp
        src/data_structures/HashTable.h src/data_structures/HashTable.cpp
        src/model/SymbolTable.h src/model/SymbolTable.cpp
        src/model/Scanner.h src/model/Scanner.cpp
        src/model/Transition.h src/model/Transition.cpp
        src/model/FiniteAutomaton.h src/model/FiniteAutomaton.cpp
        src/model/Grammar.h src/model/Grammar.cpp
        src/model/ProductionSet.h src/model/ProductionSet.cpp
        src/model/CanonicalCollection.h src/model/CanonicalCollection.cpp
        src/model/State.h src/model/State.cpp
        src/model/StateType.h
        src/model/Item.h src/model/Item.cpp src/model/LR.cpp src/model/LR.h src/model/StateType.cpp)
