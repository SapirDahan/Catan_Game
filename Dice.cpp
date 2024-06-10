#include "Dice.hpp"
#include <random>

namespace ariel {

    /**
     * @brief Constructs a Dice object and initializes the random number generator and distribution.
     */
    Dice::Dice() : generator(std::mt19937(std::random_device{}())), distribution(1, 6) {}

    /**
     * @brief Rolls the dice and returns a random number between 1 and 6.
     *
     * @return unsigned int The result of the dice roll.
     */
    unsigned int Dice::roll() {
        return distribution(generator);
    }

}
