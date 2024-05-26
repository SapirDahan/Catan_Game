#pragma once

#include "Card.hpp"
#include "CardType.hpp"

namespace ariel {

    class DevelopmentCard : public Card {
    public:
        DevelopmentCard(CardType type);
        CardType getType() const override;

    private:
        CardType type;
    };

    class KnightCard : public DevelopmentCard {
    public:
        KnightCard();
    };

    class VictoryPointCard : public DevelopmentCard {
    public:
        VictoryPointCard();
    };

    class RoadBuildingCard : public DevelopmentCard {
    public:
        RoadBuildingCard();
    };

    class YearOfPlentyCard : public DevelopmentCard {
    public:
        YearOfPlentyCard();
    };

    class MonopolyCard : public DevelopmentCard {
    public:
        MonopolyCard();
    };

}
