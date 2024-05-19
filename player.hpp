/*
 * Author: Sapir Dahan
 * ID: 325732972
 * Mail: sapirdahan2003@gmail.com
 */


#pragma once
#include <string>
#include <vector>
#include "board.hpp"


using namespace std;

namespace ariel {
    class Player {
    private:
        int wool = 0;
        int brick = 0;
        int wood = 0;
        int oat = 0;
        int iron = 0;

        int points = 0;

    public:
        Player(string name);
        void placeSettelemnt(vector<string> places, vector<int> placesNum, Board b);
        void placeRoad(vector<string> places, vector<int> placesNum, Board b);
        void rollDice();
        void endTurn();
        void trade(Player p, string give, string get, int giveAmount, int getAmount);
        void buyDevelopmentCard();
        void printPoints();
    };
}