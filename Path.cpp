#include "Path.hpp"

Path::Path(int index, int intersection1, int intersection2)
        : index(index), owner(nullptr), intersections(intersection1, intersection2) {}

int Path::getIndex() const { return index; }
Player* Path::getOwner() const { return owner; }
void Path::setOwner(Player* owner) { this->owner = owner; }
std::pair<int, int> Path::getIntersections() const { return intersections; }
