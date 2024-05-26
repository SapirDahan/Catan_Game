#include "SpecialCard.hpp"

namespace ariel {

    SpecialCard::SpecialCard(CardType type) : type(type) {}

    CardType SpecialCard::getType() const {
        return type;
    }

    LargestArmyCard::LargestArmyCard() : SpecialCard(CardType::LargestArmy) {}

}