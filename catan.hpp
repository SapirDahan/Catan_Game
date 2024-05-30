/*
 * Author: Sapir Dahan
 * ID: 325732972
 * Mail: sapirdahan2003@gmail.com
 */


#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
#include "ResourceCard.hpp"
#include "DevelopmentCard.hpp"
#include "SpecialCard.hpp"
#include "player.hpp"
#include "Path.hpp"
#include "board.hpp"
#include "CardType.hpp"
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
        Dice dice;
        std::unordered_map<unsigned int, Player*> cardOwnership;

        unsigned int findAvailableCard(CardType type);


    public:
        Catan(Player p1, Player p2, Player p3);
        void ChooseStartingPlayer() const;
        void printWinner() const;
        Board getBoard() const;
        Player checkTurn() const{ return turn; }
        Player nextPlayer();
        unsigned int rollDices();
        void handFirstCards();
        bool takeCard(Player& player, CardType type);
        bool returnCard(Player player, CardType type, unsigned int amount);
        bool playerHasCards(Player player, CardType type, unsigned int amount) const;

        bool placeRoad(Player player, unsigned int pathIndex);
        bool placeSettlement(Player player, unsigned int intersectionIndex);
        bool placeCity(Player player, unsigned int intersectionIndex);



    };
}