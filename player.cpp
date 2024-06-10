#include "player.hpp"

namespace ariel {

    /**
     * @brief Constructs a Player with a given name.
     *
     * @param name The name of the player.
     */
    Player::Player(const std::string& name) : name(name) {}

    /**
     * @brief Gets the name of the player.
     *
     * @return const std::string& The name of the player.
     */
    const std::string& Player::getName() const {
        return name;
    }

    /**
     * @brief Adds points to the player's score.
     *
     * @param point The number of points to add.
     */
    void Player::addPoints(unsigned int point) {
        this->points = this->points + point;
    }

    /**
     * @brief Reduces points from the player's score.
     *
     * @param point The number of points to reduce.
     */
    void Player::reducePoints(unsigned int point) {
        this->points = this->points - point;
    }

    /**
     * @brief Gets the player's current score.
     *
     * @return unsigned int The player's current score.
     */
    unsigned int Player::getPoints() const {
        return points;
    }

    /**
     * @brief Adds knights to the player's count.
     *
     * @param numOfKnightCards The number of knight cards to add.
     */
    void Player::addKnights(unsigned int numOfKnightCards) {
        this->numOfKnightCards = this->numOfKnightCards + numOfKnightCards;
    }

    /**
     * @brief Gets the player's current count of knight cards.
     *
     * @return unsigned int The player's current count of knight cards.
     */
    unsigned int Player::getKnights() const {
        return numOfKnightCards;
    }

}
