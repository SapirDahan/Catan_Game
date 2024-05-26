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

        while (true) {
            std::cout << std::endl;
            std::cout << players[currentPlayerIndex]->getName() << ", it's your turn." << std::endl;
            std::cout << "Choose action: " << std::endl;
            std::cout << "1. Roll Dice" << std::endl;
            std::cout << "2. Build" << std::endl;
            std::cout << "3. Trade" << std::endl;
            std::cout << "4. Buy Development Card" << std::endl;
            std::cout << "5. Play Development Card" << std::endl;
            std::cout << "6. End Turn" << std::endl;

            int choice;
            std::cin >> choice;

            switch (choice) {
                case 1:
                    // Roll Dice logic here
                    resultOfDice = catanGame->rollDices();
                    std::cout << "Rolling dice... Result is: " << resultOfDice << std::endl;
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
                    nextPlayer();
                    break;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
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
        bool buildSuccess;
        switch (buildChoice) {

            case 1:
                buildSuccess = false;
                while(!buildSuccess){
                    std::cout << "Enter path index to place road: ";
                    std::cin >> index;
//                    std::shared_ptr<Player> playerPtr = std::make_shared<Player>(catanGame->checkTurn());
//                    buildSuccess = catanGame->placeRoad(playerPtr, index);
                    buildSuccess = catanGame->placeRoad(catanGame->checkTurn(), index);
                }
                break;

            case 2:
                std::cout << "Enter intersection index to place settlement: ";
                std::cin >> index;
                //catanGame->placeSettlement(index);
                break;
            case 3:
                std::cout << "Enter intersection index to place city: ";
                std::cin >> index;
                //catanGame->placeSettlement(index);

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

    void Game::nextPlayer() {
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    }



}
int main() {
    ariel::Game game;
    game.start();
    return 0;
}

