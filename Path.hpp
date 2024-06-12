/*
 * Author: Sapir Dahan
 * ID: 325732972
 * Mail: sapirdahan2003@gmail.com
 */

#pragma once

#include <utility>
#include "player.hpp"

namespace ariel {

    /**
     * @brief Class representing a path on the game board where players can build roads.
     */
    class Path {
    public:
        /**
         * @brief Constructs a Path with a specific index and two intersections it connects.
         *
         * @param index The index of the path on the board.
         * @param intersection1 The first intersection connected by the path.
         * @param intersection2 The second intersection connected by the path.
         */
        Path(unsigned int index, unsigned int intersection1, unsigned int intersection2);

        /**
         * @brief Gets the index of the path.
         *
         * @return unsigned int The index of the path.
         */
        unsigned int getIndex() const;

        /**
         * @brief Gets the intersections connected by the path.
         *
         * @return std::pair<unsigned int, unsigned int> Pair of indices of the intersections connected by the path.
         */
        std::pair<unsigned int, unsigned int> getIntersections() const;

        /**
         * @brief Gets the owner of the path.
         *
         * @return Player* Pointer to the owner of the path.
         */
        Player* getOwner() const;

        /**
         * @brief Sets the owner of the path.
         *
         * @param player Pointer to the player who owns the path.
         * @return bool True if the owner was successfully set, false otherwise.
         */
        bool setOwner(Player* player);

    private:
        unsigned int index;  // The index of the path
        unsigned int intersection1;  // The first intersection connected by the path
        unsigned int intersection2;  // The second intersection connected by the path
        Player* owner;  // Pointer to the owner of the path
    };

}
