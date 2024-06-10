#include "DevelopmentCard.hpp"

namespace ariel {

    /**
     * @brief Constructs a DevelopmentCard with a specific card type.
     *
     * @param type The type of the development card.
     */
    DevelopmentCard::DevelopmentCard(CardType type) : type(type) {}

    /**
     * @brief Gets the type of the development card.
     *
     * @return CardType The type of the card.
     */
    CardType DevelopmentCard::getType() const {
        return type;
    }

    /**
     * @brief Constructs a KnightCard, a specific type of development card.
     */
    KnightCard::KnightCard() : DevelopmentCard(CardType::Knight) {}

    /**
     * @brief Constructs a VictoryPointCard, a specific type of development card.
     */
    VictoryPointCard::VictoryPointCard() : DevelopmentCard(CardType::VictoryPoint) {}

    /**
     * @brief Constructs a RoadBuildingCard, a specific type of development card.
     */
    RoadBuildingCard::RoadBuildingCard() : DevelopmentCard(CardType::RoadBuilding) {}

    /**
     * @brief Constructs a YearOfPlentyCard, a specific type of development card.
     */
    YearOfPlentyCard::YearOfPlentyCard() : DevelopmentCard(CardType::YearOfPlenty) {}

    /**
     * @brief Constructs a MonopolyCard, a specific type of development card.
     */
    MonopolyCard::MonopolyCard() : DevelopmentCard(CardType::Monopoly) {}

}
