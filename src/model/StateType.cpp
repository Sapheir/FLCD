#include "StateType.h"

std::string stateTypeToString(const StateType &stateType) {
    switch (stateType) {
        case REDUCE:
            return "REDUCE";
        case SHIFT:
            return "SHIFT";
        case ACCEPT:
            return "ACCEPT";
        case SHIFT_REDUCE_CONFLICT:
            return "SHIFT_REDUCE_CONFLICT";
        case REDUCE_REDUCE_CONFLICT:
            return "REDUCE_REDUCE_CONFLICT";
    }
    return "";
}