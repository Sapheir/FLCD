#pragma once


#include <string>

class Transition {
public:
    std::string from, to, label;
    Transition(std::string from, std::string to, std::string label);
    std::string toString() const;
};
