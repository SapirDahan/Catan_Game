#pragma once

#include "Card.hpp"
#include "CardType.hpp"

namespace ariel {

    /**
     * @brief Class representing a resource card in the game.
     */
    class ResourceCard : public Card {
    public:
        /**
         * @brief Constructs a ResourceCard with a specific type.
         *
         * @param type The type of the resource card.
         */
        ResourceCard(CardType type);

        /**
         * @brief Gets the type of the resource card.
         *
         * @return CardType The type of the resource card.
         */
        CardType getType() const override;

    private:
        CardType type;  // The type of the resource card
    };

}
