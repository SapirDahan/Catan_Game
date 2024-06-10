#pragma once

#include <random>

namespace ariel {

    /**
     * @brief Class representing a dice used in the game.
     */
    class Dice {
    public:
        /**
         * @brief Constructs a Dice object and initializes the random number generator and distribution.
         */
        Dice();

        /**
         * @brief Rolls the dice and returns a random number between 1 and 6.
         *
         * @return unsigned int The result of the dice roll.
         */
        unsigned int roll();

    private:
        std::mt19937 generator;  // Mersenne Twister random number generator
        std::uniform_int_distribution<unsigned int> distribution;  // Uniform distribution for numbers between 1 and 6
    };

}
