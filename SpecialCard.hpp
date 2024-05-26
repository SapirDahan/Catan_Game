#pragma once

#include "Card.hpp"
#include "CardType.hpp"

namespace ariel {

    class SpecialCard : public Card {
    public:
        SpecialCard(CardType type);
        CardType getType() const override;

    private:
        CardType type;
    };

    class LargestArmyCard : public SpecialCard {
    public:
        LargestArmyCard();
    };

}
