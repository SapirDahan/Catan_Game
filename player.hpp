#pragma once

#include <string>
#include <vector>
#include <memory>

namespace ariel {

    class Player {
    public:
        Player(const std::string& name);
        const std::string& getName() const;
        void addPoints(unsigned int points);
        unsigned int getPoints() const;
        void reducePoints(unsigned int point);
        void addKnights(unsigned int numOfKnightCards);
        unsigned int getKnights() const;

    private:
        std::string name;
        unsigned int points = 0;
        unsigned int numOfKnightCards = 0;
    };

}
