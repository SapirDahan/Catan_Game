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

//        // Check if player has the required resources
//        if (player->hasResourceCards(ResourceCard::Brick, 1) && player->hasResourceCards(ResourceCard::Lumber, 1)) {
//            // Remove the required resources from the player
//            player->removeResourceCard(ResourceCard::Brick);
//            player->removeResourceCard(ResourceCard::Lumber);
//            owner = player;
//            return true;
//        }

        return false; // Player does not have the required resources
    }

}
