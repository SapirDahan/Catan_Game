#pragma once

#include <random>

class Dice {
public:
    Dice();
    unsigned int roll();

private:
    std::mt19937 generator;
    std::uniform_int_distribution<unsigned int> distribution;
};
