#pragma once

#include <string>
#include <vector>
#include <memory>

namespace ariel {

    /**
     * @brief Class representing a player in the game.
     */
    class Player {
    public:
        /**
         * @brief Constructs a Player with a given name.
         *
         * @param name The name of the player.
         */
        Player(const std::string& name);

        /**
         * @brief Gets the name of the player.
         *
         * @return const std::string& The name of the player.
         */
        const std::string& getName() const;

        /**
         * @brief Adds points to the player's score.
         *
         * @param points The number of points to add.
         */
        void addPoints(unsigned int points);

        /**
         * @brief Gets the player's current score.
         *
         * @return unsigned int The player's current score.
         */
        unsigned int getPoints() const;

        /**
         * @brief Reduces points from the player's score.
         *
         * @param points The number of points to reduce.
         */
        void reducePoints(unsigned int points);

        /**
         * @brief Adds knights to the player's count.
         *
         * @param numOfKnightCards The number of knight cards to add.
         */
        void addKnights(unsigned int numOfKnightCards);

        /**
         * @brief Gets the player's current count of knight cards.
         *
         * @return unsigned int The player's current count of knight cards.
         */
        unsigned int getKnights() const;

    private:
        std::string name;  // The name of the player
        unsigned int points = 0;  // The player's current score
        unsigned int numOfKnightCards = 0;  // The player's current count of knight cards
    };

}
