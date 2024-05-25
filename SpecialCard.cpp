#include "SpecialCard.hpp"

namespace ariel {

    SpecialCard::SpecialCard(SpecialType type) : type(type) {}

    const char* SpecialCard::getType() const {
        switch (type) {
            case LargestArmy: return "LargestArmy";
            default: return "Unknown";
        }
    }

    SpecialCard::SpecialType SpecialCard::getSpecialType() const {
        return type;
    }

}
