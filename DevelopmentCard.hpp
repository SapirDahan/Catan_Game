#pragma once

#include "Card.hpp"

namespace ariel {

    class DevelopmentCard : public Card {
    public:
    };

    class KnightCard : public DevelopmentCard {
    public:
        const char* getType() const override { return "Knight"; }
    };

    class VictoryPointCard : public DevelopmentCard {
    public:
        const char* getType() const override { return "VictoryPoint"; }
    };

    class ProgressCard : public DevelopmentCard {
    public:
    };

    class YearOfPlentyCard : public ProgressCard {
    public:
        const char* getType() const override { return "YearOfPlenty"; }
    };

    class MonopolyCard : public ProgressCard {
    public:
        const char* getType() const override { return "Monopoly"; }
    };

    class RoadBuildingCard : public ProgressCard {
    public:
        const char* getType() const override { return "RoadBuilding"; }
    };

}