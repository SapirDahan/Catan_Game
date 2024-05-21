/*
 * Author: Sapir Dahan
 * ID: 325732972
 * Mail: sapirdahan2003@gmail.com
 */


#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "board.hpp"


using namespace std;

namespace ariel {
    class Player {
    private:
        vector<string> resources = {"wool", "brick", "wood", "oat", "iron"};
        vector<unsigned int> resourcesValues = {0, 0, 0, 0, 0};

        int points = 0;

        string name;

    public:
        Player(string name);
        string getName() const { return name;}
        int getPoints() const { return points;}
        void placeSettlement(vector<string> places, vector<int> placesNum, Board b);
        void placeRoad(vector<string> places, vector<int> placesNum, Board b);
        void rollDice();
        void endTurn();
        void trade(Player p, string give, string get, unsigned int giveAmount, unsigned int getAmount);
        void buyDevelopmentCard();
        void printPoints() const;
    };
}