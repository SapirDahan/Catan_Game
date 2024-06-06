/*
 * Author: Sapir Dahan
 * ID: 325732972
 * Mail: sapirdahan2003@gmail.com
 */

#pragma once
#include "CardType.hpp"

namespace ariel {

    class Hexagon {
    public:
        Hexagon(CardType type, unsigned int number, unsigned int x, unsigned int y);

        CardType getType() const;

        unsigned int getNumber() const;

        unsigned int getX() const;

        unsigned int getY() const;

    private:
        CardType type;
        unsigned int number;
        unsigned int x;
        unsigned int y;
    };
}
