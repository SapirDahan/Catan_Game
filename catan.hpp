/*
 * Author: Sapir Dahan
 * ID: 325732972
 * Mail: sapirdahan2003@gmail.com
 */


#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include "ResourceCard.hpp"
#include "DevelopmentCard.hpp"
#include "SpecialCard.hpp"
#include "player.hpp"
#include "Path.hpp"
#include "board.hpp"
#include "Dice.hpp"

using namespace std;

namespace ariel {
    class Catan {
    private:
        Player turn;
        Board board;
        Player player1;
        Player player2;
        Player player3;
        std::vector<std::shared_ptr<Card>> cards;

    public:
        Catan(Player p1, Player p2, Player p3);
        void ChooseStartingPlayer() const;
        void printWinner() const;
        Board getBoard() const;
    };
}