/*
 * Author: Sapir Dahan
 * ID: 325732972
 * Mail: sapirdahan2003@gmail.com
 */

#include "Hexagon.hpp"

using namespace ariel;

/**
 * @brief Constructs a Hexagon object with a specific type, number, and coordinates.
 *
 * @param type The type of the hexagon, representing the resource it produces.
 * @param number The number associated with the hexagon for dice rolls.
 * @param x The x-coordinate of the hexagon.
 * @param y The y-coordinate of the hexagon.
 */
Hexagon::Hexagon(CardType type, unsigned int number, unsigned int x, unsigned int y) : type(type), number(number), x(x), y(y) {}

/**
 * @brief Gets the type of the hexagon.
 *
 * @return CardType The type of the hexagon.
 */
CardType Hexagon::getType() const { return type; }

/**
 * @brief Gets the number associated with the hexagon for dice rolls.
 *
 * @return unsigned int The number associated with the hexagon.
 */
unsigned int Hexagon::getNumber() const { return number; }

/**
 * @brief Gets the x-coordinate of the hexagon.
 *
 * @return unsigned int The x-coordinate of the hexagon.
 */
unsigned int Hexagon::getX() const { return x; }

/**
 * @brief Gets the y-coordinate of the hexagon.
 *
 * @return unsigned int The y-coordinate of the hexagon.
 */
unsigned int Hexagon::getY() const { return y; }
