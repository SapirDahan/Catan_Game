/*
 * Author: Sapir Dahan
 * ID: 325732972
 * Mail: sapirdahan2003@gmail.com
 */

#include "Game.hpp"
#include <iostream>

namespace ariel {

    /**
     * @brief Constructs a Game object and initializes the game.
     */
    Game::Game() : currentPlayerIndex(0), catanGame(nullptr) {
        welcomeAndSetupPlayers(); // Set up players and welcome them to the game
        catanGame = new Catan(*players[0], *players[1], *players[2]); // Initialize the Catan game with the players
        catanGame->handFirstCards(); // Hand out initial cards to players
        catanGame->ChooseStartingPlayer(); // Choose the starting player
    }

    /**
     * @brief Destructor to clean up dynamically allocated memory.
     */
    Game::~Game() {
        delete catanGame; // Delete the Catan game instance
        for (auto player : players) {
            delete player; // Delete each player
        }
    }

    /**
     * @brief Welcomes players and sets up the game by initializing player objects.
     */
    void Game::welcomeAndSetupPlayers() {
        std::cout << std::endl << "Welcome to Catan!" << std::endl;
        std::cout << std::endl << "Please enter the names of 3 players:" << std::endl;
        for (int i = 1; i <= 3; ++i) {
            std::string name;
            std::cout << "Player " << i << ": ";
            std::cin >> name;
            players.push_back(new Player(name)); // Create a new player and add to the list
        }
        std::cout << std::endl;
    }

    /**
     * @brief Starts the game by setting up the board and managing player turns.
     */
    void Game::start() {
        unsigned int resultOfDice;
        unsigned int numOfRollingTheDice = 0;

        // Distribute resources from adjacent hexagons to all players
        for (unsigned int i = 2; i <= 12; i++) {
            catanGame->distributeResources(i);
        }

        // Main game loop
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
                    if (numOfRollingTheDice < 1) {
                        numOfRollingTheDice++;
                        resultOfDice = catanGame->rollDices(); // Roll the dice
                        std::cout << std::endl << "Rolling dice... The result is: " << resultOfDice << std::endl;
                        catanGame->distributeResources(resultOfDice); // Distribute resources based on the dice result
                    } else {
                        std::cout << std::endl << "You have already rolled the dice this turn." << std::endl;
                    }
                    if (resultOfDice == 7) {
                        catanGame->handleSeven(); // Handle special case when 7 is rolled
                    }
                    break;
                case 2:
                    buildMenu(); // Show build options
                    break;
                case 3:
                    catanGame->tradeCards(*catanGame->checkTurn()); // Manage trading of cards
                    break;
                case 4:
                    catanGame->buyDevCard(*catanGame->checkTurn()); // Buy development card
                    break;
                case 5:
                    showStatus(); // Show the current status of the game
                    break;
                case 6:
                    catanGame->nextPlayer(); // Move to the next player
                    numOfRollingTheDice = 0;
                    break;
                case 7:
                    std::cout << "Exiting the game" << std::endl;
                    exit(EXIT_SUCCESS); // Exit the game
                    break;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }
    }

    /**
     * @brief Displays the build menu for players to choose actions.
     */
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
                catanGame->placeRoad(*catanGame->checkTurn(), index); // Place a road
                break;
            case 2:
                std::cout << std::endl << "Enter intersection index to place settlement: ";
                std::cin >> index;
                std::cout << std::endl;
                catanGame->placeSettlement(*catanGame->checkTurn(), index); // Place a settlement
                break;
            case 3:
                std::cout << std::endl << "Enter intersection index to place city: ";
                std::cin >> index;
                std::cout << std::endl;
                catanGame->placeCity(*catanGame->checkTurn(), index); // Place a city
                break;
            default:
                std::cout << "Invalid build choice. Please try again." << std::endl;
        }
    }

    /**
     * @brief Shows the current status of the game, including player points and resources.
     */
    void Game::showStatus() {
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
                catanGame->showPlayerCards(*players[0]); // Show cards of player 1
                break;
            case 2:
                catanGame->showPlayerCards(*players[1]); // Show cards of player 2
                break;
            case 3:
                catanGame->showPlayerCards(*players[2]); // Show cards of player 3
                break;
            case 4:
                catanGame->displayBoard(); // Display the current board
                break;
            case 5:
                catanGame->displayPoints(); // Display the points of all players
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    /**
     * @brief Sets the initial roads and settlements for players.
     */
    void Game::setRoadsandSettlements() {
        unsigned int index;
        bool buildSuccess;
        int counter;

        for (unsigned int i = 0; i < 3; i++) {
            counter = 0;
            while (counter < 2) {
                std::cout << std::endl << catanGame->checkTurn()->getName() << ", please choose an index for your road: ";
                std::cin >> index;
                buildSuccess = catanGame->placeRoad(*catanGame->checkTurn(), index); // Place road

                if (buildSuccess) {
                    counter++;
                }
            }
            counter = 0;

            while (counter < 2) {
                std::cout << std::endl << catanGame->checkTurn()->getName() << ", please choose an index for your settlement: ";
                std::cin >> index;
                buildSuccess = catanGame->placeSettlement(*catanGame->checkTurn(), index); // Place settlement

                if (buildSuccess) {
                    counter++;
                }
            }
            catanGame->nextPlayer(); // Move to the next player
        }
        std::cout << std::endl << "Initial placements are completed." << std::endl;
        std::cout << std::endl << "Let the game begin!" << std::endl;
    }

    /**
     * @brief Sets the initial roads and settlements for players automatically
     */
    void Game::setRoadsandSettlements_auto() {
        // Automatically place roads and settlements for debugging
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

        std::cout << std::endl << "Initial placements are completed." << std::endl;
        std::cout << std::endl << "Let the game begin!" << std::endl;
    }

}

int main() {
    ariel::Game game;
    //game.setRoadsandSettlements(); // Uncomment this line to manually set roads and settlements
    game.setRoadsandSettlements_auto(); // Automatically set roads and settlements for debug purposes
    game.start(); // Start the game
    return 0;
}
