/*
 * Author: Sapir Dahan
 * ID: 325732972
 * Mail: sapirdahan2003@gmail.com
 */

#pragma once
#include "player.hpp"
#include "Hexagon.hpp"
#include <vector>
#include <utility>

namespace ariel {

    /**
     * @brief Class representing an intersection on the game board where players can build structures.
     */
    class Intersection {
    public:
        /**
         * @brief Enum representing the structure that can be built on an intersection.
         */
        enum Structure {
            None, Settlement, City
        };

        /**
         * @brief Constructs an Intersection with a specific index.
         * 
         * @param index The index of the intersection on the board.
         */
        Intersection(unsigned int index);

        /**
         * @brief Gets the index of the intersection.
         * 
         * @return unsigned int The index of the intersection.
         */
        unsigned int getIndex() const;

        /**
         * @brief Gets the structure built on the intersection.
         * 
         * @return Structure The structure built on the intersection.
         */
        Structure getStructure() const;

        /**
         * @brief Gets the owner of the structure on the intersection.
         * 
         * @return Player* Pointer to the owner of the structure.
         */
        Player* getOwner() const;

        /**
         * @brief Sets the structure on the intersection and assigns an owner.
         * 
         * @param structure The structure to be set on the intersection.
         * @param owner Reference to the player who owns the structure.
         * @return bool True if the structure was successfully set, false otherwise.
         */
        bool setStructure(Structure structure, Player& owner);

        /**
         * @brief Adds an adjacent hexagon to the intersection.
         * 
         * @param hexagonX The x-coordinate of the adjacent hexagon.
         * @param hexagonY The y-coordinate of the adjacent hexagon.
         */
        void addAdjacentHexagon(unsigned int hexagonX, unsigned int hexagonY);

        /**
         * @brief Gets the hexagons adjacent to the intersection.
         * 
         * @return const std::vector<std::pair<unsigned int, unsigned int>>& Vector of pairs representing the coordinates of adjacent hexagons.
         */
        const std::vector<std::pair<unsigned int, unsigned int>>& getAdjacentHexagons() const;

        /**
         * @brief Checks if the intersection is adjacent to a specific hexagon.
         * 
         * @param hex The hexagon to check adjacency with.
         * @return bool True if the intersection is adjacent to the hexagon, false otherwise.
         */
        bool isAdjacentTo(const Hexagon& hex) const;

        /**
        * @brief Gets the static list of intersection adjacencies.
        *
        * @return const std::vector<std::vector<std::pair<unsigned int, unsigned int>>>& Static vector of intersection adjacencies.
        */
        static const std::vector<std::vector<std::pair<unsigned int, unsigned int>>>& getIntersections();



    private:
        unsigned int index;  // The index of the intersection
        Structure structure;  // The structure built on the intersection
        Player* owner;  // The owner of the structure
        std::vector<std::pair<unsigned int, unsigned int>> adjacentHexagons;  // List of adjacent hexagons
    };


    // Define intersection adjacencies
    static const std::vector<std::vector<std::pair<unsigned int, unsigned int>>> intersectionAdjacencies = {{{0, 0}},
                                                                                                      {{0, 0}},
                                                                                                      {{0, 0}, {0, 1}},
                                                                                                      {{0, 1}},
                                                                                                      {{0, 1}, {0, 2}},
                                                                                                      {{0, 2}},
                                                                                                      {{0, 2}},
                                                                                                      {{1, 0}},
                                                                                                      {{0, 0}, {1, 0}},
                                                                                                      {{0, 0}, {1, 0}, {1, 1}},
                                                                                                      {{0, 0}, {0, 1}, {1, 1}},
                                                                                                      {{1, 2}, {0, 1}, {1, 1}},
                                                                                                      {{0, 1}, {1, 2}, {0, 2}},
                                                                                                      {{1, 3}, {1, 2}, {0, 2}},
                                                                                                      {{0, 2}, {1, 3}},
                                                                                                      {{1, 3}},
                                                                                                      {{2, 0}},
                                                                                                      {{1, 0}, {2, 0}},
                                                                                                      {{1, 0}, {2, 0}, {2, 1}},
                                                                                                      {{1, 0}, {1, 1}, {2, 1}},
                                                                                                      {{1, 1}, {2, 1}, {2, 2}},
                                                                                                      {{1, 1}, {1, 2}, {2, 2}},
                                                                                                      {{1, 2}, {2, 2}, {2, 3}},
                                                                                                      {{1, 2}, {1, 3}, {2, 3}},
                                                                                                      {{1, 3}, {2, 3}, {2, 4}},
                                                                                                      {{1, 3}, {2, 4}},
                                                                                                      {{2, 4}},
                                                                                                      {{2, 0}},
                                                                                                      {{2, 0}, {3, 0}},
                                                                                                      {{2, 0}, {2, 1}, {3, 0}},
                                                                                                      {{2, 1}, {3, 0}, {3, 1}},
                                                                                                      {{2, 1}, {2, 2}, {3, 1}},
                                                                                                      {{2, 2}, {3, 1}, {3, 2}},
                                                                                                      {{2, 2}, {2, 3}, {3, 2}},
                                                                                                      {{2, 3}, {3, 2}, {3, 3}},
                                                                                                      {{2, 3}, {2, 4}, {3, 3}},
                                                                                                      {{2, 4}, {3, 3}},
                                                                                                      {{2, 4}},
                                                                                                      {{3, 0}},
                                                                                                      {{3, 0}, {4, 0}},
                                                                                                      {{3, 0}, {3, 1}, {4, 0}},
                                                                                                      {{3, 1}, {4, 0}, {4, 1}},
                                                                                                      {{3, 1}, {3, 2}, {4, 1}},
                                                                                                      {{3, 2}, {4, 1}, {4, 2}},
                                                                                                      {{3, 2}, {3, 3}, {4, 2}},
                                                                                                      {{3, 3}, {4, 2}},
                                                                                                      {{3, 3}},
                                                                                                      {{4, 0}},
                                                                                                      {{4, 0}},
                                                                                                      {{4, 0}, {4, 1}},
                                                                                                      {{4, 1}},
                                                                                                      {{4, 1}, {4, 2}},
                                                                                                      {{4, 2}},
                                                                                                      {{4, 2}}};

} // namespace ariel