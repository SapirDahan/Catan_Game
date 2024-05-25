#pragma once

#include <vector>
#include <memory>
#include <string>
#include "player.hpp"
#include "catan.hpp"

namespace ariel {

    class Game {
    public:
        Game();
        void start();
        void displayBoard() const;


    private:
        std::shared_ptr<Catan> catanGame;
        std::vector<std::shared_ptr<Player>> players;
        unsigned int currentPlayerIndex;

        void welcomeAndSetupPlayers();
        void nextPlayer();

        void placeSettlement(unsigned int intersectionIndex);
        void placeRoad(unsigned int pathIndex);
        void buildMenu();
    };

} // namespace ariel
