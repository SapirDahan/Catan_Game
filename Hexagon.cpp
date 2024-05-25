#include "Hexagon.hpp"

using namespace ariel;

Hexagon::Hexagon(Type type, unsigned int number, unsigned int x, unsigned int y) : type(type), number(number), x(x), y(y) {}

Hexagon::Type Hexagon::getType() const { return type; }
unsigned int Hexagon::getNumber() const { return number; }
unsigned int Hexagon::getX() const { return x; }
unsigned int Hexagon::getY() const { return y; }
