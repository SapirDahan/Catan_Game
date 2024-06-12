/*
 * Author: Sapir Dahan
 * ID: 325732972
 * Mail: sapirdahan2003@gmail.com
 */

#pragma once

#include "player.hpp"
#include "CardType.hpp"
#include <memory>

namespace ariel {

    /**
     * @brief Abstract class representing a card in the game.
     */
    class Card {
    public:
        virtual ~Card() = default; // Virtual destructor for polymorphic cleanup

        /**
         * @brief Get the type of the card.
         *
         * This function is pure virtual and must be implemented by derived classes.
         *
         * @return CardType The type of the card.
         */
        virtual CardType getType() const = 0;
    };

}
