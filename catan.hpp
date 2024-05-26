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
        std::unordered_map<std::shared_ptr<Card>, std::shared_ptr<Player>> cardOwnership;

        std::shared_ptr<Card> findAvailableCard(CardType type);


    public:
        Catan(Player p1, Player p2, Player p3);
        void ChooseStartingPlayer() const;
        void printWinner() const;
        Board getBoard() const;
        Player checkTurn() const{ return turn; }
        Player nextPlayer();
        unsigned int rollDices();
        void handFirstCards();
        bool takeCard(std::shared_ptr<Player> player, CardType type);
        bool returnCard(std::shared_ptr<Player> player, CardType type);
        bool playerHasCards(std::shared_ptr<Player> player, CardType type, unsigned int amount) const;

        bool placeSettlement(std::shared_ptr<Player> player, unsigned int intersectionIndex);
        bool placeRoad(std::shared_ptr<Player> player, unsigned int pathIndex);

    };
}