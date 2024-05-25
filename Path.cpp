#include "Path.hpp"

namespace ariel {

    Path::Path(unsigned int index, unsigned int intersection1, unsigned int intersection2)
            : index(index), intersection1(intersection1), intersection2(intersection2), owner(nullptr) {}

    unsigned int Path::getIndex() const {
        return index;
    }

    std::pair<unsigned int, unsigned int> Path::getIntersections() const {
        return {intersection1, intersection2};
    }

    Player* Path::getOwner() const {
        return owner;
    }

    bool Path::setOwner(Player* player) {
        if (owner != nullptr) {
            return false; // Path is already owned by another player
        }

        owner = player;
        return true;
    }

}
