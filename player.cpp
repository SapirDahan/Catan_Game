#include "player.hpp"

namespace ariel {

    Player::Player(const std::string& name) : name(name) {}

    const std::string& Player::getName() const {
        return name;
    }

    void Player::addPoints(unsigned int point){
        this->points = this->points + point;
    }

    void Player::reducePoints(unsigned int point){
        this->points = this->points - point;
    }

    unsigned int Player::getPoints() const{
        return points;
    }

    void Player::addKnights(unsigned int numOfKnightCards){
        this->numOfKnightCards = this->numOfKnightCards + numOfKnightCards;
    }

    unsigned int Player::getKnights() const{
        return numOfKnightCards;
    }

}
