/*
 * Author: Sapir Dahan
 * ID: 325732972
 * Mail: sapirdahan2003@gmail.com
 */

#pragma once

class Hexagon {
public:
    enum Type { Wood, Brick, Sheep, Wheat, Ore, Desert };

    Hexagon(Type type = Desert, int number = 0, int x = 0, int y = 0);

    Type getType() const;
    int getNumber() const;
    int getX() const;
    int getY() const;

private:
    Type type;
    int number;
    int x;
    int y;
};

