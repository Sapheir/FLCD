#pragma once

#include <string>

enum StateType {
    REDUCE,
    SHIFT,
    ACCEPT,
    SHIFT_REDUCE_CONFLICT,
    REDUCE_REDUCE_CONFLICT
};

std::string stateTypeToString(const StateType &stateType);
