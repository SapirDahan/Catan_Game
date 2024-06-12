/*
 * Author: Sapir Dahan
 * ID: 325732972
 * Mail: sapirdahan2003@gmail.com
 */

#pragma once

#include "Card.hpp"
#include "CardType.hpp"

namespace ariel {

    /**
     * @brief Class representing a special card in the game.
     */
    class SpecialCard : public Card {
    public:
        /**
         * @brief Constructs a SpecialCard with a specific type.
         *
         * @param type The type of the special card.
         */
        SpecialCard(CardType type);

        /**
         * @brief Gets the type of the special card.
         *
         * @return CardType The type of the special card.
         */
        CardType getType() const override;

    private:
        CardType type;  // The type of the special card
    };

    /**
     * @brief Class representing the Largest Army card, which is a specific type of special card.
     */
    class LargestArmyCard : public SpecialCard {
    public:
        /**
         * @brief Constructs a LargestArmyCard.
         */
        LargestArmyCard();
    };

}
