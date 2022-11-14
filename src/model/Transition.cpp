#include "Transition.h"

#include <utility>

Transition::Transition(std::string from, std::string to, std::string label): from{std::move(from)}, to{std::move(to)}, label{std::move(label)} {
}

std::string Transition::toString() const {
    return from + " -> " + to + " : " + label;
}
