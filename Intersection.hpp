#pragma once
#include "player.hpp"
#include "Hexagon.hpp"
#include <vector>
#include <utility>

namespace ariel {

    class Intersection {
    public:
        enum Structure {
            None, Settlement, City
        };
        Intersection(unsigned int index);
        unsigned int getIndex() const;
        Structure getStructure() const;
        Player* getOwner() const;
        bool setOwner(Player* player);
        bool setStructure(Structure structure, Player& owner);
        void addAdjacentHexagon(unsigned int hexagonX, unsigned int hexagonY);
        const std::vector<std::pair<unsigned int, unsigned int>> &getAdjacentHexagons() const;
        bool isAdjacentTo(const Hexagon& hex) const;
        static void showIntersections(const std::vector<Intersection>& intersections);

    private:
        unsigned int index;
        Structure structure;
        Player *owner;
        std::vector<std::pair<unsigned int, unsigned int>> adjacentHexagons;
    };

    // Define intersection adjacencies
    const std::vector<std::vector<std::pair<unsigned int, unsigned int>>> intersectionAdjacencies2 = {{{0, 0}},
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


}