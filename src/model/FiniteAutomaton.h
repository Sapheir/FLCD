#pragma once


#include <vector>
#include "Transition.h"

class FiniteAutomaton {
private:
    std::vector<Transition> transitions;
    std::vector<std::string> states, alphabet, outputStates;
    std::string initialState;

    std::string trim(const std::string& str, const std::string& whitespace);
    std::vector<std::string> stringToVector(const std::string &s);
    std::string vectorToString(const std::vector<std::string> &v);

public:
    explicit FiniteAutomaton(const std::string &inputFileName);

    void readStates(std::string &line);
    void printStates();
    void readAlphabet(std::string &line);
    void printAlphabet();
    void readInitialState(std::string &line);
    void printInitialState();
    void readOutputStates(std::string &line);
    void printOutputStates();
    void readTransitions(std::string &line);
    void printTransitions();
    bool checkAccepted(const std::vector<std::string> &word);
    bool checkAccepted(const std::string &word);
};
