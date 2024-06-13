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
        Player turn;  // The player whose turn it is
        Board board;  // The game board
        Player player1;  // First player
        Player player2;  // Second player
        Player player3;  // Third player
        std::vector<Card*> cards;  // All cards in the game
        Dice dice;  // Dice object for rolling
        std::unordered_map<unsigned int, const Player*> cardOwnership;  // Map of card ownership

        /**
         * @brief Find an available card of a given type.
         *
         * @param type The type of the card.
         * @return unsigned int The index of the available card.
         */
        unsigned int findAvailableCard(CardType type);

        /**
         * @brief Helper function to handle the return of resource cards when a 7 is rolled.
         *
         * @param player The player who needs to return cards.
         */
        void handleReturnCardsForSeven(Player& player);

        const unsigned int cardNotAvailable = 1000; // Represent card not available

    public:
        /**
         * @brief Construct a new Catan game with three players.
         *
         * @param p1 The first player.
         * @param p2 The second player.
         * @param p3 The third player.
         */
        Catan(const Player& p1, const Player& p2, const Player& p3);

        ~Catan();  // Destructor to clean up dynamically allocated memory

        /**
         * @brief Choose the starting player randomly.
         */
        void ChooseStartingPlayer() const;

        /**
         * @brief Print the winner of the game.
         */
        void printWinner() const;

        /**
         * @brief Get the player whose turn it is.
         *
         * @return Player* Pointer to the current player.
         */
        Player* checkTurn() { return &turn; }

        /**
         * @brief Move to the next player's turn.
         *
         * @return Player The next player.
         */
        Player nextPlayer();

        /**
         * @brief Roll the dice.
         *
         * @return unsigned int The sum of the dice rolls.
         */
        unsigned int rollDices();

        /**
         * @brief Distribute the initial resource cards to the players.
         */
        void handFirstCards();

        /**
         * @brief Give a card to a player.
         *
         * @param player The player to give the card to.
         * @param type The type of card to give.
         * @return bool True if the card was successfully given, false otherwise.
         */
        bool takeCard(const Player& player, CardType type);

        /**
         * @brief Return a card from a player to the bank.
         *
         * @param player The player returning the card.
         * @param type The type of card to return.
         * @param amount The amount of cards to return.
         * @return bool True if the card was successfully returned, false otherwise.
         */
        bool returnCard(const Player& player, CardType type, unsigned int amount);

        /**
         * @brief Check if a player has a certain number of cards of a given type.
         *
         * @param player The player to check.
         * @param type The type of card to check.
         * @param amount The amount of cards to check for.
         * @return bool True if the player has the required amount of cards, false otherwise.
         */
        bool playerHasCards(const Player& player, CardType type, unsigned int amount) const;

        /**
         * @brief Place a road on the board for a player.
         *
         * @param player The player placing the road.
         * @param pathIndex The index of the path where the road is to be placed.
         * @return bool True if the road was successfully placed, false otherwise.
         */
        bool placeRoad(const Player& player, unsigned int pathIndex);

        /**
         * @brief Place a settlement on the board for a player.
         *
         * @param player The player placing the settlement.
         * @param intersectionIndex The index of the intersection where the settlement is to be placed.
         * @return bool True if the settlement was successfully placed, false otherwise.
         */
        bool placeSettlement(const Player& player, unsigned int intersectionIndex);

        /**
         * @brief Place a city on the board for a player.
         *
         * @param player The player placing the city.
         * @param intersectionIndex The index of the intersection where the city is to be placed.
         * @return bool True if the city was successfully placed, false otherwise.
         */
        bool placeCity(const Player& player, unsigned int intersectionIndex);

        /**
         * @brief Display the current state of the board.
         */
        void displayBoard() const;

        /**
         * @brief Show the cards held by a player.
         *
         * @param player The player whose cards are to be displayed.
         */
        void showPlayerCards(const Player& player) const;

        /**
         * @brief Convert a CardType to its string representation.
         *
         * @param cardType The type of the card.
         * @return std::string The string representation of the card type.
         */
        std::string cardTypeToString(CardType cardType) const;

        /**
         * @brief Display the points of all players.
         */
        void displayPoints();

        /**
         * @brief Add points to a player.
         *
         * @param player The player to add points to.
         * @param points The number of points to add.
         */
        void addPoints(const Player& player, unsigned int points);

        /**
         * @brief Distribute resources based on the dice result.
         *
         * @param diceResult The result of the dice roll.
         */
        void distributeResources(unsigned int diceResult);

        /**
         * @brief Allow a player to buy a development card.
         *
         * @param player The player buying the development card.
         * @return bool True if the card was successfully bought, false otherwise.
         */
        bool buyDevCard(const Player& player);

        /**
         * @brief Manage the Largest Army card.
         */
        void manageLargestArmyCard();

        /**
         * @brief Play a Monopoly card.
         */
        void playMonopolyCard();

        /**
         * @brief Take all cards of a specific type from all players and give them to the player who played the Monopoly card.
         *
         * @param player The player who played the Monopoly card.
         * @param type The type of card to take.
         */
        void takeMonopoly(const Player& player, CardType type);

        /**
         * @brief Play a Year of Plenty card.
         */
        void playYearOfPlentyCard();

        /**
         * @brief Check if a card type is a resource card.
         *
         * @param type The type of card.
         * @return bool True if the card type is a resource card, false otherwise.
         */
        bool isResourceCard(CardType type) const;

        /**
         * @brief Handle the event when a 7 is rolled on the dice.
         */
        void handleSeven();

        /**
         * @brief Count the number of resource cards held by a player.
         *
         * @param player The player whose cards are to be counted.
         * @return unsigned int The number of resource cards held by the player.
         */
        unsigned int countPlayerResourceCards(const Player& player) const;

        /**
         * @brief Show a menu for a player to return cards when a 7 is rolled.
         *
         * @param player The player returning cards.
         */
        void menuForDiceSeven(const Player& player);

        /**
         * @brief Allow a player to trade cards with another player.
         *
         * @param player The player initiating the trade.
         */
        void tradeCards(const Player &player);

        /**
     * @brief Retrieves the current state of the game board.
     *
     * @return Board The current game board.
     */
        Board getBoard();

    };
}
