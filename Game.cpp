#include "Game.hpp"
#include <iostream>

namespace ariel {

    Game::Game() : currentPlayerIndex(0) {
        welcomeAndSetupPlayers();
        catanGame = std::make_shared<Catan>(*players[0], *players[1], *players[2]);
        catanGame->ChooseStartingPlayer();
        catanGame->handFirstCards();
    }

    void Game::welcomeAndSetupPlayers() {
        std::cout << "Welcome to Catan!" << std::endl;
        std::cout << "Please enter the names of 3 players:" << std::endl;

        for (int i = 1; i <= 3; ++i) {
            std::string name;
            std::cout << "Player " << i << ": ";
            std::cin >> name;
            players.push_back(std::make_shared<Player>(name));
        }
    }

    void Game::start() {
        unsigned int resultOfDice;
        unsigned int numOfRollingTheDice = 0;

        while (true) {
            std::cout << std::endl;
            std::cout << catanGame->checkTurn().getName() << ", it's your turn." << std::endl;
            std::cout << "Choose action: " << std::endl;
            std::cout << "1. Roll Dice" << std::endl;
            std::cout << "2. Build" << std::endl;
            std::cout << "3. Trade" << std::endl;
            std::cout << "4. Buy Development Card" << std::endl;
            std::cout << "5. Play Development Card" << std::endl;
            std::cout << "6. End Turn" << std::endl;
            std::cout << "7. End the Game" << std::endl;

            int choice;
            std::cin >> choice;

            switch (choice) {
                case 1:
                    if(numOfRollingTheDice < 1){
                        // Roll Dice logic here
                        resultOfDice = catanGame->rollDices();
                        std::cout << "Rolling dice... Result is: " << resultOfDice << std::endl;
                        numOfRollingTheDice++;
                    }
                    else{
                        std::cout << "You have already rolled the dices at this turn." << std::endl;
                    }

                    break;
                case 2:
                    buildMenu();
                    break;
                case 3:
                    // Trade logic here
                    std::cout << "Trading... (not implemented yet)" << std::endl;
                    break;
                case 4:
                    // Buy Development Card logic here
                    std::cout << "Buying development card... (not implemented yet)" << std::endl;
                    break;
                case 5:
                    // Play Development Card logic here
                    std::cout << "Playing development card... (not implemented yet)" << std::endl;
                    break;
                case 6:
                    catanGame->nextPlayer();
                    numOfRollingTheDice = 0;
                    break;
                case 7:
                    // check i someone won
                    cout << "Existing the game" << endl;
                    break;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;

            }

            if(choice == 7){
                break;
            }
        }
    }

    void Game::buildMenu() {
        std::cout << "Build Options: " << std::endl;
        std::cout << "1. Road" << std::endl;
        std::cout << "2. Settlement" << std::endl;
        std::cout << "3. City" << std::endl;
        int buildChoice;
        std::cin >> buildChoice;

        unsigned int index;
        switch (buildChoice) {

            case 1:
                std::cout << "Enter path index to place road: ";
                std::cin >> index;
                catanGame->placeRoad(catanGame->checkTurn(), index);

                break;

            case 2:
                std::cout << "Enter intersection index to place settlement: ";
                std::cin >> index;
                catanGame->placeSettlement(catanGame->checkTurn(),index);
                break;
            case 3:
                std::cout << "Enter intersection index to place city: ";
                std::cin >> index;
                catanGame->placeCity(catanGame->checkTurn(),index);

            default:
                std::cout << "Invalid build choice. Please try again." << std::endl;
        }
    }

    void Game::displayBoard() const {
//        Board board = catanGame->getBoard();
//        std::cout << "Board Status:" << std::endl;
//        for (const auto& hexagon : board.getHexagons()) {
//            std::cout << "Hexagon (" << hexagon.getX() << ", " << hexagon.getY() << ") - Type: " << hexagon.getType() << ", Number: " << hexagon.getNumber() << std::endl;
//        }
//        for (const auto& row : board.getIntersections()) {
//            for (const auto& intersection : row) {
//                std::cout << "Intersection " << intersection.getIndex() << " - Structure: " << intersection.getStructure() << ", Owner: " << (intersection.getOwner() ? intersection.getOwner()->getName() : "None") << std::endl;
//            }
//        }
//        for (const auto& path : board.getPaths()) {
//            std::cout << "Path " << path.getIndex() << " - Owner: " << (path.getOwner() ? path.getOwner()->getName() : "None") << std::endl;
//        }
    }

//    void Game::nextPlayer() {
//        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
//    }

    void Game::setRoadsandSettlements(){
//        std::cout << "Build Options: " << std::endl;
//        std::cout << "1. Road" << std::endl;
//        std::cout << "2. Settlement" << std::endl;
//        std::cout << "3. City" << std::endl;
//        int buildChoice;
//        std::cin >> buildChoice;
//
//        switch (buildChoice) {


        unsigned int index;
        bool buildSuccess;
        int counter;

        for(unsigned int i = 0; i < 3; i++){
            counter = 0;
            while(counter < 2){
                cout << "Player " << catanGame->checkTurn().getName() << "choose an index for your road: " << endl;
                std::cin >> index;
                buildSuccess = catanGame->placeRoad(catanGame->checkTurn(), index);

                if(buildSuccess){
                    counter++;
                }
            }
            counter = 0;

            while(counter < 2){
                cout << "Player " << catanGame->checkTurn().getName() << " choose an index for your settlement: " << endl;
                std::cin >> index;
                buildSuccess = catanGame->placeSettlement(catanGame->checkTurn(), index);

                if(buildSuccess){
                    counter++;
                }
            }

            catanGame->nextPlayer();
        }
    }
}
int main() {
    ariel::Game game;
    game.setRoadsandSettlements();
    game.start();
    return 0;
}

