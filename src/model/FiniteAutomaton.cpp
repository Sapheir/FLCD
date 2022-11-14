#include "FiniteAutomaton.h"
#include <fstream>
#include <regex>
#include <iostream>

FiniteAutomaton::FiniteAutomaton(const std::string &inputFileName) {
    std::ifstream input(inputFileName);
    std::string line;
    while (std::getline(input, line)) {
        std::regex lineRegex{"^([a-z_]*)="};
        auto regexIt = std::sregex_iterator(line.begin(), line.end(), lineRegex);
        if (regexIt != std::sregex_iterator()) {
            std::string key = regexIt->str();
            key.pop_back();
            std::string value = line.substr(key.size() + 1);
            value.erase(std::remove_if(value.begin(), value.end(), [](const char &c) {return std::string("{}()").find(c) != std::string::npos;}), value.end());
            if (key == "states") {
                readStates(value);
            } else if (key == "alphabet") {
                readAlphabet(value);
            } else if (key == "in_state") {
                readInitialState(value);
            } else if (key == "out_states") {
                readOutputStates(value);
            } else if (key == "transitions") {
                readTransitions(value);
            }
        }
    }
}

std::string FiniteAutomaton::trim(const std::string& str,
                 const std::string& whitespace = " \t")
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return "";

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

void FiniteAutomaton::readStates(std::string &line) {
    size_t pos;
    std::string token;
    while ((pos = line.find(',')) != std::string::npos) {
        token = line.substr(0, pos);
        states.push_back(trim(token));
        line.erase(0, pos + 1);
    }
    states.push_back(trim(line));
}

void FiniteAutomaton::printStates() {
    std::cout << "States: ";
    for (int i = 0; i<states.size(); i++) {
        std::cout << states[i] << ", "[i == states.size()-1];
    }
    std::cout << "\n";
}

void FiniteAutomaton::readAlphabet(std::string &line) {
    size_t pos;
    std::string token;
    while ((pos = line.find(',')) != std::string::npos) {
        token = line.substr(0, pos);
        alphabet.push_back(trim(token));
        line.erase(0, pos + 1);
    }
    alphabet.push_back(trim(line));
}

void FiniteAutomaton::printAlphabet() {
    std::cout << "Alphabet: ";
    for (int i = 0; i<alphabet.size(); i++) {
        std::cout << alphabet[i] << ", "[i == alphabet.size()-1];
    }
    std::cout << "\n";
}

void FiniteAutomaton::readInitialState(std::string &line) {
    initialState = trim(line);
}

void FiniteAutomaton::printInitialState() {
    std::cout << "Initial state: " << initialState << "\n";
}

void FiniteAutomaton::readOutputStates(std::string &line) {
    size_t pos;
    std::string token;
    while ((pos = line.find(',')) != std::string::npos) {
        token = line.substr(0, pos);
        outputStates.push_back(trim(token));
        line.erase(0, pos + 1);
    }
    outputStates.push_back(trim(line));
}

void FiniteAutomaton::printOutputStates() {
    std::cout << "Output states: ";
    for (int i = 0; i<outputStates.size(); i++) {
        std::cout << outputStates[i] << ", "[i == outputStates.size()-1];
    }
    std::cout << "\n";
}

void FiniteAutomaton::readTransitions(std::string &line) {
    size_t pos;
    std::string token;
    while ((pos = line.find(';')) != std::string::npos) {
        token = line.substr(0, pos);
        size_t commaPos = token.find(',');
        std::string from = trim(token.substr(0, commaPos));
        std::string to = trim(token.substr(commaPos+1, token.find(',', commaPos+1)-commaPos-1));
        std::string label = trim(token.substr(token.find(',', commaPos+1)+1));
        transitions.emplace_back(Transition(from, to, label));
        line.erase(0, pos + 1);
    }
    size_t commaPos = line.find(',');
    std::string from = trim(line.substr(0, commaPos));
    std::string to = trim(line.substr(commaPos+1, line.find(',', commaPos+1)-commaPos-1));
    std::string label = trim(line.substr(line.find(',', commaPos+1)+1));
    transitions.emplace_back(Transition(from, to, label));
}

void FiniteAutomaton::printTransitions() {
    std::cout << "Transitions: ";
    for (const auto &transition: transitions) {
        std::cout << transition.toString() << " ";
    }
    std::cout << "\n";
}

bool FiniteAutomaton::checkAccepted(const std::vector<std::string> &word) {
    std::string currentState = initialState;
    for (const auto &letter: word) {
        bool found = false;
        for (const auto &transition: transitions) {
            if (transition.from == currentState && transition.label == letter) {
                currentState = transition.to;
                found = true;
                break;
            }
        }
        if (!found)
            return false;
    }
    for (const auto &out: outputStates) {
        if (out == currentState)
            return true;
    }
    return false;
}

bool FiniteAutomaton::checkAccepted(const std::string &word) {
    return checkAccepted(stringToVector(word));
}

std::vector<std::string> FiniteAutomaton::stringToVector(const std::string &s) {
    std::vector<std::string> v;
    for (const auto &c: s) {
        v.emplace_back(1, c);
    }
    return v;
}

std::string FiniteAutomaton::vectorToString(const std::vector<std::string> &v) {
    std::string s;
    for (const auto &str: v) {
        s += str;
    }
    return s;
}
