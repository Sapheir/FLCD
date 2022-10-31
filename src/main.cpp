#include <fstream>
#include <iostream>
#include "model/Scanner.h"

int main() {
    try {
        std::ifstream programReader("..\\1a\\p1.cmm");
        std::string line, program;
        while (std::getline(programReader, line)) {
            program += line + "\n";
        }
        programReader.close();

        std::ifstream tokenReader("..\\1b\\token.in");
        std::string token;
        std::vector<std::string> tokens;
        while (std::getline(tokenReader, token)) {
            tokens.push_back(token);
        }
        tokenReader.close();
        Scanner scanner{program, tokens};
        try {
            scanner.scan();
        } catch (const std::runtime_error &e) {
            std::cerr << e.what() << "\n";
            return 0;
        }
        scanner.outST();
        scanner.outPIF();
        std::cout << "The program is lexically valid\n";
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}