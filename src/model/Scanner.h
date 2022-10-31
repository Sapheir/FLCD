#pragma once


#include <utility>

#include "SymbolTable.h"

class Scanner {
private:
    SymbolTable symbolTable;
    int currentLine = 1, index = 0;
    std::string program;
    std::vector<std::string> tokens;
    std::vector<std::pair<std::string, int>> pif;

    /**
     * Skips characters considered blank
     * @return true if a skip happened, otherwise false
     */
    bool skipWhitespace();

    /**
     * Skips comments which start with //
     * @return true if a skip happened, otherwise false
     */
    bool skipComment();

    /**
     * Checks if a string constant was found
     * @return true if a string constant was found, otherwise false
     */
    bool stringConstant();

    /**
     * Check if an int constant was found
     * @return true if an int constant was found, otherwise false
     */
    bool intConstant();

    /**
     * Checks if the current token is in the list of reserved tokens
     * @return true if match is found, otherwise false
     */
    bool tokenFromList();

    /**
     * Checks if an identifier was found
     * @return true if an identifier was found, otherwise false
     */
    bool identifier();

    /**
     * Processes the next token
     */
    void nextToken();

public:
    Scanner(std::string program, std::vector<std::string> tokens): program{std::move(program)}, tokens{std::move(tokens)} {}

    /**
     * Performs an entire program scan
     */
    void scan();

    /**
     * Prints the symbol table to a file
     */
    void outST();

    /**
     * Prints the PIF to a file
     */
    void outPIF();
};
