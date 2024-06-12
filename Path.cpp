/*
 * Author: Sapir Dahan
 * ID: 325732972
 * Mail: sapirdahan2003@gmail.com
 */

#include "Path.hpp"

namespace ariel {

    /**
     * @brief Constructs a Path with a specific index and two intersections it connects.
     *
     * @param index The index of the path on the board.
     * @param intersection1 The first intersection connected by the path.
     * @param intersection2 The second intersection connected by the path.
     */
    Path::Path(unsigned int index, unsigned int intersection1, unsigned int intersection2)
            : index(index), intersection1(intersection1), intersection2(intersection2), owner(nullptr) {}

    /**
     * @brief Gets the index of the path.
     *
     * @return unsigned int The index of the path.
     */
    unsigned int Path::getIndex() const {
        return index;
    }

    /**
     * @brief Gets the intersections connected by the path.
     *
     * @return std::pair<unsigned int, unsigned int> Pair of indices of the intersections connected by the path.
     */
    std::pair<unsigned int, unsigned int> Path::getIntersections() const {
        return {intersection1, intersection2};
    }

    /**
     * @brief Gets the owner of the path.
     *
     * @return Player* Pointer to the owner of the path.
     */
    Player* Path::getOwner() const {
        return owner;
    }

    /**
     * @brief Sets the owner of the path.
     *
     * @param player Pointer to the player who owns the path.
     * @return bool True if the owner was successfully set, false otherwise.
     */
    bool Path::setOwner(Player* player) {
        if (owner != nullptr) {
            return false; // Path is already owned by another player
        }

        owner = player;
        return true;
    }

}
