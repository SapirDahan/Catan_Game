#include "Dice.hpp"
#include <random>

Dice::Dice() : generator(std::mt19937(std::random_device{}())), distribution(1, 6) {}

unsigned int Dice::roll() {
    return distribution(generator);
}
