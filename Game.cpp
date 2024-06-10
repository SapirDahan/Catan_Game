#include "Game.hpp"
#include <iostream>

namespace ariel {

    Game::Game() : currentPlayerIndex(0) {
        welcomeAndSetupPlayers();
        catanGame = std::make_shared<Catan>(*players[0], *players[1], *players[2]);
        catanGame->handFirstCards();
        catanGame->ChooseStartingPlayer();
    }

    void Game::welcomeAndSetupPlayers() {
        std::cout << std::endl << "Welcome to Catan!" << std::endl;
        std::cout << std::endl << "Please enter the names of 3 players:" << std::endl;
        for (int i = 1; i <= 3; ++i) {
            std::string name;
            std::cout << "Player " << i << ": ";
            std::cin >> name;
            players.push_back(std::make_shared<Player>(name));
        }
        std::cout << std::endl;
    }

    void Game::start() {
        unsigned int resultOfDice;
        unsigned int numOfRollingTheDice = 0;

        // Distribute resources from adjacent hexagons to all players
        for(unsigned int i=2; i<=12; i++) {
            catanGame->distributeResources(i);
        }

        while (true) {
            std::cout << std::endl;
            std::cout << catanGame->checkTurn()->getName() << ", it's your turn." << std::endl << std::endl;
            std::cout << "Choose action: " << std::endl;
            std::cout << "1. Roll Dice" << std::endl;
            std::cout << "2. Build" << std::endl;
            std::cout << "3. Trade" << std::endl;
            std::cout << "4. Buy Development Card" << std::endl;
            std::cout << "5. Show status" << std::endl;
            std::cout << "6. End Turn" << std::endl;
            std::cout << "7. End the Game" << std::endl;

            int choice;
            std::cin >> choice;

            switch (choice) {
                case 1:
                    if(numOfRollingTheDice < 1){
                        numOfRollingTheDice++;
                        resultOfDice = catanGame->rollDices();
                        std::cout << std::endl << "Rolling dice... The result is: " << resultOfDice << std::endl;
                        catanGame->distributeResources(resultOfDice);
                    }
                    else{
                        std::cout << std::endl << "You have already rolled the dices at this turn." << std::endl;
                    }
                    if(resultOfDice == 7){
                        catanGame->handleSeven();
                    }
                    break;
                case 2:
                    buildMenu();
                    break;
                case 3:
                    catanGame->tradeCards(*catanGame->checkTurn());
                    break;
                case 4:
                    catanGame->buyDevCard(*catanGame->checkTurn());
                    break;
                case 5:
                    showStatus();
                    break;
                case 6:
                    catanGame->nextPlayer();
                    numOfRollingTheDice = 0;
                    break;
                case 7:
                    cout << "Existing the game" << endl;
                    exit(EXIT_SUCCESS);
                    break;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }
    }

    void Game::buildMenu() {
        std::cout << std::endl << "Build Options: " << std::endl;
        std::cout << "1. Road" << std::endl;
        std::cout << "2. Settlement" << std::endl;
        std::cout << "3. City" << std::endl;
        int buildChoice;
        std::cin >> buildChoice;

        unsigned int index;
        switch (buildChoice) {

            case 1:
                std::cout << std::endl << "Enter path index to place road: ";
                std::cin >> index;
                std::cout << std::endl;
                catanGame->placeRoad(*catanGame->checkTurn(), index);
                break;

            case 2:
                std::cout << std::endl << "Enter intersection index to place settlement: ";
                std::cin >> index;
                std::cout << std::endl;
                catanGame->placeSettlement(*catanGame->checkTurn(),index);
                break;

            case 3:
                std::cout << std::endl << "Enter intersection index to place city: ";
                std::cin >> index;
                std::cout << std::endl;
                catanGame->placeCity(*catanGame->checkTurn(),index);
                break;

            default:
                std::cout << "Invalid build choice. Please try again." << std::endl;
        }
    }

    void Game::showStatus(){
        std::cout << std::endl << "Status Options: " << std::endl;
        std::cout << "1. Cards of player 1" << std::endl;
        std::cout << "2. Cards of player 2" << std::endl;
        std::cout << "3. Cards of player 3" << std::endl;
        std::cout << "4. Show board" << std::endl;
        std::cout << "5. Show points" << std::endl;


        int statusChoice;
        std::cin >> statusChoice;

        switch (statusChoice) {

            case 1:
                catanGame->showPlayerCards(*players[0]);
                break;
            case 2:
                catanGame->showPlayerCards(*players[1]);
                break;
            case 3:
                catanGame->showPlayerCards(*players[2]);
                break;
            case 4:
                catanGame->displayBoard();
                break;
            case 5:
                catanGame->displayPoints();
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;;
        }
    }


    void Game::setRoadsandSettlements(){

        unsigned int index;
        bool buildSuccess;
        int counter;

        for(unsigned int i = 0; i < 3; i++){
            counter = 0;
            while(counter < 2){
                cout << endl << catanGame->checkTurn()->getName() << ", please choose an index for your road: ";
                std::cin >> index;
                buildSuccess = catanGame->placeRoad(*catanGame->checkTurn(), index);

                if(buildSuccess){
                    counter++;
                }
            }
            counter = 0;

            while(counter < 2){
                cout << endl << catanGame->checkTurn()->getName() << ", please choose an index for your settlement: ";
                std::cin >> index;
                buildSuccess = catanGame->placeSettlement(*catanGame->checkTurn(), index);

                if(buildSuccess){
                    counter++;
                }
            }
            catanGame->nextPlayer();
        }
        std::cout << std::endl << "Initial placements is completed." << std::endl;
        std::cout << std::endl << "Let the game begin!" << std::endl;
    }

    // @@@ For debug purposes only
    void Game::setRoadsandSettlements_auto(){

        catanGame->placeRoad(*catanGame->checkTurn(), 13);
        catanGame->placeRoad(*catanGame->checkTurn(), 41);
        catanGame->placeSettlement(*catanGame->checkTurn(), 10);
        catanGame->placeSettlement(*catanGame->checkTurn(), 29);

        catanGame->nextPlayer();

        catanGame->placeRoad(*catanGame->checkTurn(), 56);
        catanGame->placeRoad(*catanGame->checkTurn(), 52);
        catanGame->placeSettlement(*catanGame->checkTurn(), 40);
        catanGame->placeSettlement(*catanGame->checkTurn(), 44);

        catanGame->nextPlayer();

        catanGame->placeRoad(*catanGame->checkTurn(), 15);
        catanGame->placeRoad(*catanGame->checkTurn(), 58);
        catanGame->placeSettlement(*catanGame->checkTurn(), 13);
        catanGame->placeSettlement(*catanGame->checkTurn(), 42);
        catanGame->nextPlayer();

        std::cout << std::endl << "Initial placements is completed." << std::endl;
        std::cout << std::endl << "Let the game begin!" << std::endl;
    }

}


int main() {
    ariel::Game game;
    //game.setRoadsandSettlements();
    game.setRoadsandSettlements_auto();
    game.start();
    return 0;
}

