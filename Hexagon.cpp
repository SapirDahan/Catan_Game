#include "Hexagon.hpp"

Hexagon::Hexagon(Type type, int number, int x, int y) : type(type), number(number), x(x), y(y) {}

Hexagon::Type Hexagon::getType() const { return type; }
int Hexagon::getNumber() const { return number; }
int Hexagon::getX() const { return x; }
int Hexagon::getY() const { return y; }
