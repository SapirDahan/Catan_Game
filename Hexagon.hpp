/*
 * Author: Sapir Dahan
 * ID: 325732972
 * Mail: sapirdahan2003@gmail.com
 */

#pragma once

namespace ariel {

    class Hexagon {
    public:
        enum Type {
            Wood, Brick, Sheep, Wheat, Ore, Desert
        };

        Hexagon(Type type = Desert, unsigned int number = 0, unsigned int x = 0, unsigned int y = 0);

        Type getType() const;

        unsigned int getNumber() const;

        unsigned int getX() const;

        unsigned int getY() const;

    private:
        Type type;
        unsigned int number;
        unsigned int x;
        unsigned int y;
    };
}
