#pragma once

#include <utility>
#include "player.hpp"

namespace ariel {

    class Path {
    public:
        Path(unsigned int index, unsigned int intersection1, unsigned int intersection2);

        unsigned int getIndex() const;
        std::pair<unsigned int, unsigned int> getIntersections() const;
        Player* getOwner() const;
        bool setOwner(Player* player);

    private:
        unsigned int index;
        unsigned int intersection1;
        unsigned int intersection2;
        Player* owner; // Pointer to the owner of the path
    };

}