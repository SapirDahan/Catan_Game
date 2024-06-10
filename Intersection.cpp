#include "Intersection.hpp"
#include "Hexagon.hpp"
#include <iostream>

using namespace ariel;

/**
 * @brief Constructs an Intersection with a specific index.
 *
 * @param index The index of the intersection on the board.
 */
Intersection::Intersection(unsigned int index) : index(index), structure(None), owner(nullptr) {}

/**
 * @brief Gets the index of the intersection.
 *
 * @return unsigned int The index of the intersection.
 */
unsigned int Intersection::getIndex() const { return index; }

/**
 * @brief Gets the structure built on the intersection.
 *
 * @return Structure The structure built on the intersection.
 */
Intersection::Structure Intersection::getStructure() const { return structure; }

/**
 * @brief Gets the owner of the structure on the intersection.
 *
 * @return Player* Pointer to the owner of the structure, or nullptr if there is no structure.
 */
Player* Intersection::getOwner() const {
    return structure != Structure::None ? owner : nullptr;
}


/**
 * @brief Adds an adjacent hexagon to the intersection.
 *
 * @param hexagonX The x-coordinate of the adjacent hexagon.
 * @param hexagonY The y-coordinate of the adjacent hexagon.
 */
void Intersection::addAdjacentHexagon(unsigned int hexagonX, unsigned int hexagonY) {
    adjacentHexagons.emplace_back(hexagonX, hexagonY);
}

/**
 * @brief Gets the hexagons adjacent to the intersection.
 *
 * @return const std::vector<std::pair<unsigned int, unsigned int>>& Vector of pairs representing the coordinates of adjacent hexagons.
 */
const std::vector<std::pair<unsigned int, unsigned int>>& Intersection::getAdjacentHexagons() const {
    return adjacentHexagons;
}

/**
 * @brief Sets the structure on the intersection and assigns an owner.
 *
 * @param newStructure The structure to be set on the intersection.
 * @param player Reference to the player who owns the structure.
 * @return bool True if the structure was successfully set, false otherwise.
 */
bool Intersection::setStructure(Structure newStructure, Player& player) {
    if (newStructure == Settlement) {
        if (structure == None) {
            structure = Settlement;
            this->owner = &player;
            return true;
        }
    } else if (newStructure == City) {
        if (structure == Settlement) {
            structure = City;
            return true;
        }
    }
    return false;
}

/**
 * @brief Checks if the intersection is adjacent to a specific hexagon.
 *
 * @param hex The hexagon to check adjacency with.
 * @return bool True if the intersection is adjacent to the hexagon, false otherwise.
 */
bool Intersection::isAdjacentTo(const Hexagon& hex) const {
    // Get the adjacency list for this intersection
    const auto& adjacencies = intersectionAdjacencies2[this->index];

    // Check if the given hexagon is in the adjacency list
    for (const auto& adjacency : adjacencies) {
        if (adjacency.first == hex.getX() && adjacency.second == hex.getY()) {
            return true;
        }
    }
    return false;
}
