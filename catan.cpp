#include "catan.hpp"

using namespace std;

namespace ariel {
    // Constructor
    Catan::Catan(Player p1, Player p2, Player p3) : turn(p1), player1(p1), player2(p2), player3(p3) {
        // Create all the cards in the game

        // Add Resource Cards
        for (unsigned int i = 0; i < 19; ++i) {
            cards.push_back(std::make_shared<ResourceCard>(ResourceCard::Lumber));
        }
        for (unsigned int i = 0; i < 19; ++i) {
            cards.push_back(std::make_shared<ResourceCard>(ResourceCard::Brick));
        }
        for (unsigned int i = 0; i < 19; ++i) {
            cards.push_back(std::make_shared<ResourceCard>(ResourceCard::Wool));
        }
        for (unsigned int i = 0; i < 19; ++i) {
            cards.push_back(std::make_shared<ResourceCard>(ResourceCard::Grain));
        }
        for (unsigned int i = 0; i < 19; ++i) {
            cards.push_back(std::make_shared<ResourceCard>(ResourceCard::Ore));
        }

        // Add Development Cards
        for (unsigned int i = 0; i < 14; ++i) {
            cards.push_back(std::make_shared<KnightCard>());
        }
        for (unsigned int i = 0; i < 5; ++i) {
            cards.push_back(std::make_shared<VictoryPointCard>());
        }
        for (unsigned int i = 0; i < 2; ++i) {
            cards.push_back(std::make_shared<RoadBuildingCard>());
        }
        for (unsigned int i = 0; i < 2; ++i) {
            cards.push_back(std::make_shared<YearOfPlentyCard>());
        }
        for (unsigned int i = 0; i < 2; ++i) {
            cards.push_back(std::make_shared<MonopolyCard>());
        }

    }

    void Catan::ChooseStartingPlayer() const{
        cout << "The starting player is: " << turn.getName() << "!" << endl;
    }

//    void Catan::printWinner() const{
//        if(player1.getPoints() >= 10){
//            cout << player1.getName() << " is the winner!!!" << endl;
//        }
//
//        else if(player2.getPoints() >= 10){
//            cout << player2.getName() << " is the winner!!!" << endl;
//        }
//
//        else if(player3.getPoints() >= 10){
//            cout << player3.getName() << " is the winner!!!" << endl;
//        }
//
//        else{
//            cout << "The still go on!" << endl;
//        }
//
//    }

    Board Catan::getBoard() const{
        return board;
    }

    Player Catan::nextPlayer(){
        if(turn.getName() == player1.getName()){
            turn = player2;
            return player2;
        }

        else if(turn.getName() == player2.getName()){
            turn = player3;
            return player3;
        }
        else{
            turn = player1;
            return player1;
        }
    }
}
