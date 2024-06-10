#pragma once

#include "Card.hpp"
#include "CardType.hpp"

namespace ariel {

    /**
     * @brief Class representing a development card in the game.
     */
    class DevelopmentCard : public Card {
    public:
        /**
         * @brief Constructs a DevelopmentCard with a specific card type.
         *
         * @param type The type of the development card.
         */
        DevelopmentCard(CardType type);

        /**
         * @brief Gets the type of the development card.
         *
         * @return CardType The type of the card.
         */
        CardType getType() const override;

    private:
        CardType type;  // The type of the development card
    };

    /**
     * @brief Class representing a Knight card, a specific type of development card.
     */
    class KnightCard : public DevelopmentCard {
    public:
        /**
         * @brief Constructs a KnightCard.
         */
        KnightCard();
    };

    /**
     * @brief Class representing a Victory Point card, a specific type of development card.
     */
    class VictoryPointCard : public DevelopmentCard {
    public:
        /**
         * @brief Constructs a VictoryPointCard.
         */
        VictoryPointCard();
    };

    /**
     * @brief Class representing a Road Building card, a specific type of development card.
     */
    class RoadBuildingCard : public DevelopmentCard {
    public:
        /**
         * @brief Constructs a RoadBuildingCard.
         */
        RoadBuildingCard();
    };

    /**
     * @brief Class representing a Year of Plenty card, a specific type of development card.
     */
    class YearOfPlentyCard : public DevelopmentCard {
    public:
        /**
         * @brief Constructs a YearOfPlentyCard.
         */
        YearOfPlentyCard();
    };

    /**
     * @brief Class representing a Monopoly card, a specific type of development card.
     */
    class MonopolyCard : public DevelopmentCard {
    public:
        /**
         * @brief Constructs a MonopolyCard.
         */
        MonopolyCard();
    };

}
