#pragma once
#include "player.hpp"
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

        Player *getOwner() const;

        bool setStructure(Structure structure, Player *owner);

        void addAdjacentHexagon(unsigned int hexagonX, unsigned int hexagonY);

        const std::vector<std::pair<unsigned int, unsigned int>> &getAdjacentHexagons() const;

    private:
        unsigned int index;
        Structure structure;
        Player *owner;
        std::vector<std::pair<unsigned int, unsigned int>> adjacentHexagons;
    };
}