/*
 * Author: Sapir Dahan
 * ID: 325732972
 * Mail: sapirdahan2003@gmail.com
 */

#pragma once
#include "CardType.hpp"

namespace ariel {

    /**
     * @brief Class representing a hexagon tile in the game, which produces a specific resource.
     */
    class Hexagon {
    public:
        /**
         * @brief Constructs a Hexagon object with a specific type, number, and coordinates.
         *
         * @param type The type of the hexagon, representing the resource it produces.
         * @param number The number associated with the hexagon for dice rolls.
         * @param x The x-coordinate of the hexagon.
         * @param y The y-coordinate of the hexagon.
         */
        Hexagon(CardType type, unsigned int number, unsigned int x, unsigned int y);

        /**
         * @brief Gets the type of the hexagon.
         *
         * @return CardType The type of the hexagon.
         */
        CardType getType() const;

        /**
         * @brief Gets the number associated with the hexagon for dice rolls.
         *
         * @return unsigned int The number associated with the hexagon.
         */
        unsigned int getNumber() const;

        /**
         * @brief Gets the x-coordinate of the hexagon.
         *
         * @return unsigned int The x-coordinate of the hexagon.
         */
        unsigned int getX() const;

        /**
         * @brief Gets the y-coordinate of the hexagon.
         *
         * @return unsigned int The y-coordinate of the hexagon.
         */
        unsigned int getY() const;

    private:
        CardType type;  // The type of the hexagon, representing the resource it produces
        unsigned int number;  // The number associated with the hexagon for dice rolls
        unsigned int x;  // The x-coordinate of the hexagon
        unsigned int y;  // The y-coordinate of the hexagon
    };
}
