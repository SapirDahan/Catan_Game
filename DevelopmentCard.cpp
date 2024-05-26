#include "DevelopmentCard.hpp"

namespace ariel {

    DevelopmentCard::DevelopmentCard(CardType type) : type(type) {}

    CardType DevelopmentCard::getType() const {
        return type;
    }

    KnightCard::KnightCard() : DevelopmentCard(CardType::Knight) {}

    VictoryPointCard::VictoryPointCard() : DevelopmentCard(CardType::VictoryPoint) {}

    RoadBuildingCard::RoadBuildingCard() : DevelopmentCard(CardType::RoadBuilding) {}

    YearOfPlentyCard::YearOfPlentyCard() : DevelopmentCard(CardType::YearOfPlenty) {}

    MonopolyCard::MonopolyCard() : DevelopmentCard(CardType::Monopoly) {}

}
