#include "player.hpp"

namespace ariel {

    Player::Player(const std::string& name) : name(name) {}

    const std::string& Player::getName() const {
        return name;
    }

    void Player::addPoints(unsigned int point){
        this->points = this->points + point;
    }
    unsigned int Player::getPoints() const{
        return points;
    }

//    void Player::addResourceCard(std::shared_ptr<ResourceCard> card) {
//        resourceCards.push_back(card);
//    }
//
//    bool Player::hasResourceCards(ResourceCard::ResourceType type, unsigned int count) const {
//        unsigned int found = 0;
//        for (const auto& card : resourceCards) {
//            if (card->getResourceType() == type) {
//                found++;
//                if (found >= count) {
//                    return true;
//                }
//            }
//        }
//        return false;
//    }
//
//    bool Player::removeResourceCard(ResourceCard::ResourceType type) {
//        for (auto it = resourceCards.begin(); it != resourceCards.end(); ++it) {
//            if ((*it)->getResourceType() == type) {
//                resourceCards.erase(it);
//                return true;
//            }
//        }
//        return false;
//    }

}
