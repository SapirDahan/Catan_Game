#pragma once

#include <vector>
#include <string>
#include "player.hpp"
#include "catan.hpp"

namespace ariel {

    /**
     * @brief Class representing the game logic and management.
     */
    class Game {
    public:
        /**
         * @brief Constructs a Game object and initializes the game.
         */
        Game();

        /**
         * @brief Destructor to clean up dynamically allocated memory.
         */
        ~Game();

        /**
         * @brief Starts the game by setting up players and initiating gameplay.
         */
        void start();

        /**
         * @brief Displays the current state of the game board.
         */
        void displayBoard() const;

        /**
         * @brief Sets the initial roads and settlements for players.
         */
        void setRoadsandSettlements();

        /**
         * @brief Sets the initial roads and settlements for players automatically.
         *
         * @note This function is for debug purposes only.
         */
        void setRoadsandSettlements_auto();

    private:
        Catan* catanGame;  // Pointer to the Catan game instance
        std::vector<Player*> players;  // List of players in the game
        unsigned int currentPlayerIndex;  // Index of the current player

        /**
         * @brief Welcomes players and sets up the game by initializing player objects.
         */
        void welcomeAndSetupPlayers();

        /**
         * @brief Advances the turn to the next player.
         */
        void nextPlayer();

        /**
         * @brief Shows the current status of the game, including player points and resources.
         */
        void showStatus();

        /**
         * @brief Displays the build menu for players to choose actions.
         */
        void buildMenu();
    };

} // namespace ariel
