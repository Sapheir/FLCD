#include <fstream>
#include <iostream>
#include <cassert>
#include "model/Scanner.h"
#include "model/FiniteAutomaton.h"

int main() {
    try {
//        std::ifstream programReader("..\\1a\\p1.cmm");
//        std::string line, program;
//        while (std::getline(programReader, line)) {
//            program += line + "\n";
//        }
//        programReader.close();
//
//        std::ifstream tokenReader("..\\1b\\token.in");
//        std::string token;
//        std::vector<std::string> tokens;
//        while (std::getline(tokenReader, token)) {
//            tokens.push_back(token);
//        }
//        tokenReader.close();
//        Scanner scanner{program, tokens};
//        try {
//            scanner.scan();
//        } catch (const std::runtime_error &e) {
//            std::cerr << e.what() << "\n";
//            return 0;
//        }
//        scanner.outST();
//        scanner.outPIF();
//        std::cout << "The program is lexically valid\n";
        FiniteAutomaton fa{"..\\fa.in"};
        assert(fa.checkAccepted("11") == true);
        assert(fa.checkAccepted("101") == true);
        assert(fa.checkAccepted("10001") == true);
        assert(fa.checkAccepted("111") == false);
        assert(fa.checkAccepted("01") == false);
        assert(fa.checkAccepted("00") == false);
        while (true) {
            std::cout << "1. Print states\n";
            std::cout << "2. Print alphabet\n";
            std::cout << "3. Print output states\n";
            std::cout << "4. Print in state\n";
            std::cout << "5. Print transitions\n";
            std::cout << "6. Check word\n";
            std::cout << "0. Exit\n";
            int option;
            std::cin >> option;
            switch (option) {
                case 1:
                    fa.printStates();
                    break;
                case 2:
                    fa.printAlphabet();
                    break;
                case 3:
                    fa.printOutputStates();
                    break;
                case 4:
                    fa.printInitialState();
                    break;
                case 5:
                    fa.printTransitions();
                    break;
                case 6: {
                    std::cout << "Word: ";
                    std::string word;
                    std::cin >> word;
                    std::cout << fa.checkAccepted(word) << "\n";
                    break;
                }
                default:
                    return 0;
            }
        }
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}