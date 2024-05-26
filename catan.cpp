#include "catan.hpp"

using namespace std;

namespace ariel {
    // Constructor
    Catan::Catan(Player p1, Player p2, Player p3) : turn(p1), player1(p1), player2(p2), player3(p3), dice() {
        // Create all the cards in the game

        // Add Resource Cards
        for (unsigned int i = 0; i < 19; ++i) {
            cards.push_back(std::make_shared<ResourceCard>(CardType::Lumber));
        }
        for (unsigned int i = 0; i < 19; ++i) {
            cards.push_back(std::make_shared<ResourceCard>(CardType::Brick));
        }
        for (unsigned int i = 0; i < 19; ++i) {
            cards.push_back(std::make_shared<ResourceCard>(CardType::Wool));
        }
        for (unsigned int i = 0; i < 19; ++i) {
            cards.push_back(std::make_shared<ResourceCard>(CardType::Grain));
        }
        for (unsigned int i = 0; i < 19; ++i) {
            cards.push_back(std::make_shared<ResourceCard>(CardType::Ore));
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
        // Add Special Cards
        cards.push_back(std::make_shared<LargestArmyCard>());

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

    unsigned int Catan::rollDices(){
        return dice.roll() + dice.roll();
    }

    void Catan::handFirstCards() {
        Player players[] = {player1, player2, player3};

        for (const auto& player : players) {
            for (unsigned int i = 0; i < 4; ++i) {
                takeCard(player, CardType::Lumber);
                takeCard(player, CardType::Brick);
            }
            for (unsigned int i = 0; i < 2; ++i) {
                takeCard(player, CardType::Wool);
                takeCard(player, CardType::Grain);
            }

            std::cout << player.getName() << " has received the initial resource cards: 4 Lumber, 4 Bricks, 2 Wool, and 2 Grain." << std::endl;
            std::cout << player.getName() << " should now build two roads and two settlements using these cards." << std::endl;
        }
    }

    bool Catan::takeCard(Player player, CardType type) {
        std::shared_ptr<Card> card = findAvailableCard(type);
        if (card) {
            cardOwnership[card] = &player;
            return true;
        }
        std::cout << "No available card of type " << static_cast<int>(type) << " to take." << std::endl;
        return false;
    }

    bool Catan::returnCard(Player player, CardType type) {
        for (const auto& entry : cardOwnership) {
            std::shared_ptr<Card> card = entry.first;
            Player* owner = entry.second;
            if (card->getType() == type && owner->getName() == player.getName()) {
                cardOwnership.erase(card);
                return true;
            }
        }
        std::cout << "No card of type " << static_cast<int>(type) << " owned by " << player.getName() << " to return." << std::endl;
        return false;
    }

    std::shared_ptr<Card> Catan::findAvailableCard(CardType type) {
        for (const auto& card : cards) {
            if (card->getType() == type && cardOwnership.find(card) == cardOwnership.end()) {
                return card;
            }
        }
        return nullptr;
    }

    bool Catan::playerHasCards(Player player, CardType type, unsigned int amount) const {
        unsigned int count = 0;
        for (const auto& entry : cardOwnership) {

            if (entry.second->getName() == player.getName() && entry.first->getType() == type) {
                count++;
                if (count >= amount) {
                    return true;
                }
            }
        }
        return false;
    }

    bool Catan::placeRoad(Player  player, unsigned int pathIndex) {
        if(pathIndex >= board.getPathAdjacenciesSize()){
            std::cout << "Index out of bound." << std::endl;
            return  false;
        }
        Path path = board.getPath(pathIndex);
        if (path.getOwner() != nullptr) {
            std::cout << "This path is already owned by another player." << std::endl;
            return false;
        }
        if (!playerHasCards(player, CardType::Lumber, 1) || !playerHasCards(player, CardType::Brick, 1)) {
            std::cout << "The player does not have the required resources (1 Lumber and 1 Brick) to build a road." << std::endl;
            return false;
        }
        returnCard(player, CardType::Lumber);
        returnCard(player, CardType::Brick);
        path.setOwner(&player);
        std::cout << "Your road has been placed." << std::endl;

        return true;

    }



}
