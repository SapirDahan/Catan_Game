#include "Intersection.hpp"

Intersection::Intersection(int index) : index(index), structure(None), owner(nullptr) {}

int Intersection::getIndex() const { return index; }
Intersection::Structure Intersection::getStructure() const { return structure; }
Player* Intersection::getOwner() const { return owner; }

void Intersection::addAdjacentHexagon(int hexagonX, int hexagonY) {
    adjacentHexagons.emplace_back(hexagonX, hexagonY);
}
const std::vector<std::pair<int, int>>& Intersection::getAdjacentHexagons() const {
    return adjacentHexagons;
}
