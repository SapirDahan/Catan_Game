/*
 * Author: Sapir Dahan
 * ID: 325732972
 * Mail: sapirdahan2003@gmail.com
 */

#include "catan.hpp"
#include "Intersection.hpp"
#include "Hexagon.hpp"
#include "CardType.hpp"
#include <numeric>

using namespace std;

namespace ariel {

    // Constructor
    Catan::Catan(const Player &p1, const Player &p2, const Player &p3) : turn(p1), player1(p1), player2(p2),
                                                                         player3(p3), dice() {

        // Add Resource Cards
        for (unsigned int i = 0; i < 19; ++i) {
            cards.push_back(new ResourceCard(CardType::Lumber));
        }
        for (unsigned int i = 0; i < 19; ++i) {
            cards.push_back(new ResourceCard(CardType::Brick));
        }
        for (unsigned int i = 0; i < 19; ++i) {
            cards.push_back(new ResourceCard(CardType::Wool));
        }
        for (unsigned int i = 0; i < 19; ++i) {
            cards.push_back(new ResourceCard(CardType::Grain));
        }
        for (unsigned int i = 0; i < 19; ++i) {
            cards.push_back(new ResourceCard(CardType::Ore));
        }

        // Add Development Cards
        for (unsigned int i = 0; i < 14; ++i) {
            cards.push_back(new KnightCard());
        }
        for (unsigned int i = 0; i < 5; ++i) {
            cards.push_back(new VictoryPointCard());
        }
        for (unsigned int i = 0; i < 2; ++i) {
            cards.push_back(new RoadBuildingCard());
        }
        for (unsigned int i = 0; i < 2; ++i) {
            cards.push_back(new YearOfPlentyCard());
        }
        for (unsigned int i = 0; i < 2; ++i) {
            cards.push_back(new MonopolyCard());
        }

        // Add Special Cards
        cards.push_back(new LargestArmyCard());
    }

    // Destructor
    Catan::~Catan() {
        for (Card *card: cards) {
            delete card;
        }
    }

    /**
     * @brief Displays the name of the starting player.
     */
    void Catan::ChooseStartingPlayer() const {
        cout << endl << "The starting player is: " << turn.getName() << "!" << endl;
    }

    /**
     * @brief Advances to the next player's turn.
     *
     * @return Player The next player.
     */
    Player Catan::nextPlayer() {
        // Check if the player has won
        if (turn.getPoints() >= minPointsToWin) {
            cout << endl << turn.getName() << " is the winner with " << turn.getPoints() << " victory points!!!" << endl;
            cout << endl << "GAME OVER!" << endl;
            exit(EXIT_SUCCESS);
        }

        // Rotate to the next player
        if (turn.getName() == player1.getName()) {
            turn = player2;
            return player2;
        }

        else if (turn.getName() == player2.getName()) {
            turn = player3;
            return player3;
        }

        else {
            turn = player1;
            return player1;
        }
    }

    /**
     * @brief Rolls two dice and returns the sum of their results.
     *
     * @return unsigned int The sum of the two dice rolls.
     */
    unsigned int Catan::rollDices() {
        // Roll two dice and sum the results
        return dice.roll() + dice.roll();
    }

    /**
     * @brief Hands out the initial resource cards to each player.
     */
    void Catan::handFirstCards() {
        // Array of players for easy iteration
        Player players[] = {player1, player2, player3};

        // Distribute initial resource cards to each player
        for (unsigned int i = 0; i < 3; ++i) {
            // Each player gets 4 Lumber and 4 Bricks
            for (unsigned int j = 0; j < 4; ++j) {
                takeCard(players[i], CardType::Lumber);
                takeCard(players[i], CardType::Brick);
            }
            // Each player gets 2 Wool and 2 Grain
            for (unsigned int j = 0; j < 2; ++j) {
                takeCard(players[i], CardType::Wool);
                takeCard(players[i], CardType::Grain);
            }
        }

        cout << "Each player has received the initial resource cards: 4 Lumber, 4 Bricks, 2 Wool, and 2 Grain." << endl;
        cout << "Before the game begins, each player shall build two roads and two settlements using these cards."
             << endl;
    }

    /**
     * @brief Takes a card of a specific type and assigns it to a player.
     *
     * @param player The player who takes the card.
     * @param type The type of card to be taken.
     * @return bool True if the card was successfully taken, false otherwise.
     */
    bool Catan::takeCard(const Player &player, CardType type) {
        unsigned int cardNumber = findAvailableCard(type);

        // Check if the card is available
        if (cardNumber != cardNotAvailable) {
            Player *players[] = {&player1, &player2, &player3};

            for (auto *currentPlayer: players) {
                if (player.getName() == currentPlayer->getName()) {
                    cardOwnership[cardNumber] = currentPlayer;

                    // if it is a knight add it to the player count
                    if (type == CardType::Knight) {
                        currentPlayer->addKnights(1);
                    }

                    // Optional: Uncomment the line below to print that a player took a card
                    // cout << "Card of type " << cardTypeToString(type) << " handed to " << currentPlayer->getName() << "." << endl;
                    return true;
                }
            }
        }

        cout << "Card of type " << cardTypeToString(type) << " is not available." << endl;
        return false;
    }


    /**
     * @brief Returns a specified number of cards of a specific type from a player.
     *
     * @param player The player who returns the cards.
     * @param type The type of card to be returned.
     * @param amount The number of cards to be returned.
     * @return bool True if the cards were successfully returned, false otherwise.
     */
    bool Catan::returnCard(const Player &player, CardType type, unsigned int amount) {
        unsigned int counter = 0;
        std::vector<unsigned int> cardsToErase;

        // Find the cards to be returned
        for (const auto &entry: cardOwnership) {
            unsigned int card = entry.first;
            if ((cards[card]->getType() == type) && (entry.second->getName() == player.getName())) {
                cardsToErase.push_back(card);
                counter++;
            }
            if (counter == amount) {
                // Remove the cards from ownership
                if (!cardsToErase.empty()) {
                    for (unsigned int card: cardsToErase) {
                        cardOwnership.erase(card);
                    }
                }

                // Optional: Uncomment the line below to print that a player has returned a card
                // if (type != CardType::LargestArmy) {
                //     cout << player.getName() << " has just returned " << amount << " " << cardTypeToString(type)
                //          << " card/s to the bank." << endl;
                // }
                return true;
            }
        }
        cout << "No card of type " << cardTypeToString(type) << " owned by " << player.getName() << " found." << endl;
        return false;
    }

    /**
     * @brief Finds an available card of a specific type.
     *
     * @param type The type of card to find.
     * @return unsigned int The index of the available card, or cardNotAvailable if no card is available.
     */
    unsigned int Catan::findAvailableCard(CardType type) {
        for (unsigned int i = 0; i < cards.size(); i++) {
            // Check if the card is of the desired type and not owned by anyone
            if (cards[i]->getType() == type && cardOwnership.find(i) == cardOwnership.end()) {
                return i;
            }
        }

        return cardNotAvailable;
    }

    /**
     * @brief Checks if a player has a specified number of cards of a specific type.
     *
     * @param player The player to check.
     * @param type The type of card to check for.
     * @param amount The number of cards to check for.
     * @return bool True if the player has at least the specified number of cards, false otherwise.
     */
    bool Catan::playerHasCards(const Player &player, CardType type, unsigned int amount) const {
        unsigned int count = 0;
        // Count the number of cards of the specified type owned by the player
        for (const auto &entry: cardOwnership) {
            if (entry.second->getName() == player.getName() && cards[entry.first]->getType() == type) {
                count++;

                // Check if the player have enough card
                if (count >= amount) {
                    return true;
                }
            }
        }
        return false;
    }


    /**
  * @brief Places a road for the specified player at the given path index.
  *
  * @param player The player who is placing the road.
  * @param pathIndex The index of the path where the road will be placed.
  * @return bool True if the road is successfully placed, false otherwise.
  */
    bool Catan::placeRoad(const Player &player, unsigned int pathIndex) {
        // Check if the path index is within bounds
        if (pathIndex >= board.getPathAdjacenciesSize()) {
            std::cout << "Path index is out of bound." << std::endl;
            return false;
        }

        // Check if the path is already occupied
        if (board.getPath(pathIndex).getOwner() != nullptr) {
            std::cout << "This path is already occupied." << std::endl;
            return false;
        }

        // Check if the player has the required resources to build a road
        if (!playerHasCards(player, CardType::Lumber, 1) || !playerHasCards(player, CardType::Brick, 1)) {
            std::cout << "You don't have the required resources (1 Lumber and 1 Brick) to build a road." << std::endl;
            return false;
        }

        // Deduct the required resources from the player's inventory
        returnCard(player, CardType::Lumber, 1);
        returnCard(player, CardType::Brick, 1);

        // List of players
        std::vector<Player*> players = {&player1, &player2, &player3};

        // Assign the road to the correct player
        for (Player* p : players) {
            if (player.getName() == p->getName()) {
                board.getPath(pathIndex).setOwner(p);
                break;
            }
        }

        std::cout << player.getName() << ", your road has been placed on path " << pathIndex << "." << std::endl;
        return true;
    }

/**
 * @brief Places a settlement for the specified player at the given intersection index.
 *
 * @param player The player who is placing the settlement.
 * @param intersectionIndex The index of the intersection where the settlement will be placed.
 * @return bool True if the settlement is successfully placed, false otherwise.
 */
    bool Catan::placeSettlement(const Player &player, unsigned int intersectionIndex) {
        // Check if the intersection index is within bounds
        if (intersectionIndex >= board.getIntersectionAdjacenciesSize()) {
            std::cout << "Intersection index is out of bound." << std::endl;
            return false;
        }

        // Check if the intersection is already occupied
        if (board.getIntersection(intersectionIndex).getOwner() != nullptr) {
            std::cout << "Intersection " << intersectionIndex << " is already occupied." << std::endl;
            return false;
        }

        // Check if the intersection is too close to another settlement or city
        for (const auto &path: board.getPathAdjacencies()) {
            if ((path.first == intersectionIndex && board.getIntersection(path.second).getOwner() != nullptr) ||
                (path.second == intersectionIndex && board.getIntersection(path.first).getOwner() != nullptr)) {
                std::cout
                        << "Illegal place to place settlement. Too close to another settlement/city. Please try again."
                        << std::endl;
                return false;
            }
        }

        // Check if the player has an adjacent road to the intersection
        bool hasAdjacentRoad = false;
        for (unsigned int i = 0; i < board.getPathAdjacenciesSize(); i++) {
            auto intersections = board.getPath(i).getIntersections();
            if ((board.getPath(i).getOwner() != nullptr) &&
                (board.getPath(i).getOwner()->getName() == player.getName()) &&
                ((intersections.first == intersectionIndex) || (intersections.second == intersectionIndex))) {
                hasAdjacentRoad = true;
                break;
            }
        }
        if (!hasAdjacentRoad) {
            std::cout
                    << "Illegal place to place settlement. You must have at least one road adjacent to the intersection. Please try again."
                    << std::endl;
            return false;
        }

        // Check if the player has the required resources to build a settlement
        if (!playerHasCards(player, CardType::Lumber, 1) ||
            !playerHasCards(player, CardType::Brick, 1) ||
            !playerHasCards(player, CardType::Wool, 1) ||
            !playerHasCards(player, CardType::Grain, 1)) {
            std::cout << player.getName()
                      << ", you do not have the required resources (1 Lumber, 1 Brick, 1 Wool, and 1 Grain) to build a settlement."
                      << std::endl;
            return false;
        }

        // Deduct the required resources from the player's inventory
        returnCard(player, CardType::Lumber, 1);
        returnCard(player, CardType::Brick, 1);
        returnCard(player, CardType::Wool, 1);
        returnCard(player, CardType::Grain, 1);

        std::vector<Player*> players = {&player1, &player2, &player3};

        // Assign the settlement to the correct player
        for (Player* p : players) {
            if (player.getName() == p->getName()) {
                board.getIntersection(intersectionIndex).setStructure(Intersection::Structure::Settlement, *p);
                break;
            }
        }

        std::cout << player.getName() << ", your settlement has been placed on intersection " << intersectionIndex
                  << "." << std::endl;
        addPoints(player, 1);
        return true;
    }

/**
 * @brief Upgrades a settlement to a city for the specified player at the given intersection index.
 *
 * @param player The player who is upgrading the settlement to a city.
 * @param intersectionIndex The index of the intersection where the settlement will be upgraded to a city.
 * @return bool True if the city is successfully placed, false otherwise.
 */
    bool Catan::placeCity(const Player &player, unsigned int intersectionIndex) {
        // Check if the intersection index is within bounds
        if (intersectionIndex >= board.getIntersectionAdjacenciesSize()) {
            std::cout << "Intersection index is out of bound." << std::endl;
            return false;
        }

        // Check if the intersection is owned by the player
        if ((board.getIntersection(intersectionIndex).getOwner() != nullptr) &&
            (board.getIntersection(intersectionIndex).getOwner()->getName() != player.getName())) {
            std::cout << "This intersection is not owned by " << player.getName() << std::endl;
            return false;
        }

        // Check if there is a settlement to upgrade
        if (board.getIntersection(intersectionIndex).getStructure() != Intersection::Structure::Settlement) {
            std::cout << "Can't upgrade to city because there isn't a Settlement on the intersection." << std::endl;
            return false;
        }

        // Check if the player has the required resources to build a city
        if (!playerHasCards(player, CardType::Ore, 3) || !playerHasCards(player, CardType::Grain, 2)) {
            std::cout << "The player does not have the required resources (3 Ore and 2 Grain) to build a city."
                      << std::endl;
            return false;
        }

        // Deduct the required resources from the player's inventory
        returnCard(player, CardType::Ore, 3);
        returnCard(player, CardType::Grain, 2);

        // Assign the city to the correct player
        std::vector<Player*> players = {&player1, &player2, &player3};

        for (Player* p : players) {
            if (player.getName() == p->getName()) {
                board.getIntersection(intersectionIndex).setStructure(Intersection::Structure::City, *p);
                break;
            }
        }


        std::cout << player.getName() << ", your city has been placed." << std::endl;
        addPoints(player, 1);
        return true;
    }

    /**
  * @brief Displays the current state of the game board, including intersections and roads.
  */
    void Catan::displayBoard() const {
        board.showIntersections();
        board.showRoads();
    }

/**
 * @brief Displays the cards held by the specified player.
 *
 * @param player The player whose cards will be displayed.
 */
    void Catan::showPlayerCards(const Player &player) const {
        std::unordered_map<CardType, int> cardCounts; // Map to store counts of each card type
        unsigned int totalCards = 0; // Total number of cards

        // Iterate through card ownership to count the cards owned by the player
        for (const auto &entry: cardOwnership) {
            if (entry.second->getName() == player.getName()) {
                CardType cardType = cards.at(entry.first)->getType();
                cardCounts[cardType]++;
                totalCards++;
            }
        }

        // Display the cards
        if (totalCards > 0) {
            std::cout << std::endl << player.getName() << " has the following cards:" << std::endl;
            for (const auto &count: cardCounts) {
                std::cout << cardTypeToString(count.first) << ": " << count.second << std::endl;
            }
        }

        else {
            std::cout << std::endl << player.getName() << " has no cards." << std::endl;
        }
    }

/**
 * @brief Converts a CardType enum value to its corresponding string representation.
 *
 * @param cardType The CardType enum value.
 * @return std::string The string representation of the CardType.
 */
    std::string Catan::cardTypeToString(CardType cardType) const {
        switch (cardType) {
            case CardType::Lumber:
                return "Lumber";
            case CardType::Brick:
                return "Brick";
            case CardType::Wool:
                return "Wool";
            case CardType::Grain:
                return "Grain";
            case CardType::Ore:
                return "Ore";
            case CardType::Knight:
                return "Knight";
            case CardType::VictoryPoint:
                return "Victory Point";
            case CardType::RoadBuilding:
                return "Road Building";
            case CardType::YearOfPlenty:
                return "Year of Plenty";
            case CardType::Monopoly:
                return "Monopoly";
            case CardType::LargestArmy:
                return "Largest Army";
            default:
                return "Unknown";
        }
    }

/**
 * @brief Displays the points of all players.
 */
    void Catan::displayPoints() {
        std::cout << std::endl << "Scoreboard:" << std::endl;

        std::vector<Player*> players = {&player1, &player2, &player3};

        // Print each player points
        for (Player* p : players) {
            std::cout << p->getName() << " has " << p->getPoints() << " points" << std::endl;
        }

    }

/**
 * @brief Adds points to the specified player.
 *
 * @param player The player to whom points will be added.
 * @param points The number of points to add.
 */
    void Catan::addPoints(const Player &player, unsigned int points) {
        std::vector<Player*> players = {&player1, &player2, &player3};

        for (Player* p : players) {
            if (player.getName() == p->getName()) {
                p->addPoints(points);
                break;
            }
        }

    }

/**
 * @brief Distributes resources to players based on the dice result.
 *
 * @param diceResult The result of the dice roll.
 */
    void Catan::distributeResources(unsigned int diceResult) {
        CardType hexCard;

        // Step 1: Identify all hexagons with the given dice result
        std::vector <Hexagon> matchingHexagons;
        for (const auto &hex: board.getHexagons()) {
            if (hex.getNumber() == diceResult) {
                matchingHexagons.push_back(hex);
            }
        }

        // Step 2: Iterate through all intersections
        for (const auto &intersection: board.getIntersections()) {
            bool adjacentToMatchingHexagon = false;

            // Check if the intersection is adjacent to any matching hexagon
            for (const auto &hex: matchingHexagons) {
                if (intersection.isAdjacentTo(hex)) {
                    adjacentToMatchingHexagon = true;
                    hexCard = hex.getType();
                    break;
                }
            }

            // Step 3: Allocate resources if the intersection is adjacent to a matching hexagon
            if (adjacentToMatchingHexagon) {
                Intersection::Structure structure = intersection.getStructure();
                Player *owner = intersection.getOwner();
                if (owner != nullptr) {
                    if (structure == Intersection::Structure::Settlement) {
                        takeCard(*owner, hexCard);
                    } else if (structure == Intersection::Structure::City) {
                        takeCard(*owner, hexCard);
                        takeCard(*owner, hexCard);
                    }
                }
            }
        }
    }

/**
 * @brief Allows a player to buy a development card.
 *
 * @param player The player who is buying the development card.
 * @return bool True if the development card is successfully bought, false otherwise.
 */
    bool Catan::buyDevCard(const Player &player) {
        // Check if the player has the relevant resource cards to buy a development card
        if (!playerHasCards(player, CardType::Ore, 1) ||
            !playerHasCards(player, CardType::Grain, 1) ||
            !playerHasCards(player, CardType::Wool, 1)) {
            std::cout
                    << "The player does not have the required resources (1 Ore, 1 Grain, and 1 Wool) to buy a development card."
                    << std::endl;
            return false;
        }

        // Count the available development cards of each type
        std::vector<unsigned int> devCardTypeCounter(5, 0);
        for (unsigned int i = 0; i < cards.size(); i++) {
            if (cardOwnership.find(i) == cardOwnership.end()) {
                switch (cards[i]->getType()) {
                    case CardType::Knight:
                        devCardTypeCounter[0]++;
                        break;
                    case CardType::VictoryPoint:
                        devCardTypeCounter[1]++;
                        break;
                    case CardType::RoadBuilding:
                        devCardTypeCounter[2]++;
                        break;
                    case CardType::YearOfPlenty:
                        devCardTypeCounter[3]++;
                        break;
                    case CardType::Monopoly:
                        devCardTypeCounter[4]++;
                        break;
                    default:
                        break;
                }
            }
        }
        unsigned int sumOfDevCards = static_cast<unsigned int>(std::accumulate(devCardTypeCounter.begin(),
                                                                               devCardTypeCounter.end(), 0));
        if (sumOfDevCards == 0) {
            std::cout << "\nThere are no further development cards in the pack." << std::endl;
            return false;
        }

        // Return cards to the bank
        returnCard(player, CardType::Ore, 1);
        returnCard(player, CardType::Grain, 1);
        returnCard(player, CardType::Wool, 1);

        // Generate a random number to determine which development card the player receives
        int randNum = rand() % static_cast<int>(sumOfDevCards) + 1;
        unsigned int index = 0;
        unsigned int cumulativeSum = 0;
        for (unsigned int i = 0; i < devCardTypeCounter.size(); ++i) {
            cumulativeSum += devCardTypeCounter[i];
            if (randNum <= cumulativeSum) {
                index = i;
                break;
            }
        }

        // Assign the development card to the player
        switch (index) {
            case 0:
                takeCard(player, CardType::Knight);
                manageLargestArmyCard(); // Manage the Largest Army Card logic and print status
                break;
            case 1:
                takeCard(player, CardType::VictoryPoint);
                addPoints(player, 1);
                break;
            case 2:
                takeCard(player, CardType::RoadBuilding);
                takeCard(player, CardType::Brick);
                takeCard(player, CardType::Brick);
                takeCard(player, CardType::Lumber);
                takeCard(player, CardType::Lumber);
                break;
            case 3:
                takeCard(player, CardType::YearOfPlenty);
                playYearOfPlentyCard();
                playYearOfPlentyCard();
                break;
            case 4:
                takeCard(player, CardType::Monopoly);
                playMonopolyCard();
                break;
            default:
                break;
        }
        nextPlayer(); // Next player's turn
        return true;
    }

    /**
    * @brief Manages the Largest Army Card by checking the player with the most knights and awarding the card.
    */
    void Catan::manageLargestArmyCard() {
        // Check eligibility for largest army
        Player *playerWithMostKnights = nullptr;
        const unsigned int minimumKnightsForLargestArmy = 3; // Must have more than 3 Knight cards
        unsigned int maxKnights = minimumKnightsForLargestArmy;

        // Find the player with the most knights
        Player *players[] = {&player1, &player2, &player3};
        for (Player *player: players) {
            if (player->getKnights() >= maxKnights) {
                maxKnights = player->getKnights();
                playerWithMostKnights = player;
            }
        }

        // The previous player returns the card
        for (Player *player: players) {
            if (playerHasCards(*player, CardType::LargestArmy, 1)) {
                returnCard(*player, CardType::LargestArmy, 1);
                player->reducePoints(2);
            }
        }

        // Add two victory points and grant the Largest Army Card to the new player
        if (playerWithMostKnights != nullptr) {
            takeCard(*playerWithMostKnights, CardType::LargestArmy);
            playerWithMostKnights->addPoints(2);
        }
    }

    /**
    * @brief Allows the current player to play a Monopoly card and choose a resource to monopolize.
    */
    void Catan::playMonopolyCard() {
        while (true) {
            std::cout << std::endl;
            std::cout << turn.getName() << ", please choose a resource for your monopoly." << std::endl;
            std::cout << "1. Lumber" << std::endl;
            std::cout << "2. Brick" << std::endl;
            std::cout << "3. Wool" << std::endl;
            std::cout << "4. Grain" << std::endl;
            std::cout << "5. Ore" << std::endl;
            int choice;
            std::cin >> choice;

            switch (choice) {
                case 1:
                    takeMonopoly(turn, CardType::Lumber);
                    break;
                case 2:
                    takeMonopoly(turn, CardType::Brick);
                    break;
                case 3:
                    takeMonopoly(turn, CardType::Wool);
                    break;
                case 4:
                    takeMonopoly(turn, CardType::Grain);
                    break;
                case 5:
                    takeMonopoly(turn, CardType::Ore);
                    break;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
            }
            if (choice <= 5) {
                break;
            }
        }
    }

    /**
     * @brief Transfers all cards of a specific type from other players to the player who played the Monopoly card.
     *
     * @param player The player who played the Monopoly card.
     * @param type The type of card to monopolize.
     */
    void Catan::takeMonopoly(const Player &player, CardType type) {
        for (auto &entry: cardOwnership) {
            unsigned int cardId = entry.first;
            auto card = cards[cardId];
            if (card->getType() == type) {
                entry.second = &player;
            }
        }
        returnCard(player, CardType::Monopoly, 1);
    }

    /**
     * @brief Allows the current player to play a Year of Plenty card and choose a resource to receive.
     */
    void Catan::playYearOfPlentyCard() {
        while (true) {
            std::cout << std::endl;
            std::cout << turn.getName() << ", please choose a resource for your Year of Plenty.\n" << std::endl;
            std::cout << "1. Lumber" << std::endl;
            std::cout << "2. Brick" << std::endl;
            std::cout << "3. Wool" << std::endl;
            std::cout << "4. Grain" << std::endl;
            std::cout << "5. Ore" << std::endl;
            int choice;
            std::cin >> choice;

            switch (choice) {
                case 1:
                    takeCard(turn, CardType::Lumber);
                    break;
                case 2:
                    takeCard(turn, CardType::Brick);
                    break;
                case 3:
                    takeCard(turn, CardType::Wool);
                    break;
                case 4:
                    takeCard(turn, CardType::Grain);
                    break;
                case 5:
                    takeCard(turn, CardType::Ore);
                    break;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
            }
            if (choice <= 5) {
                break;
            }
        }
    }

    /**
     * @brief Counts the number of resource cards a player has.
     *
     * @param player The player whose resource cards are to be counted.
     * @return unsigned int The total number of resource cards the player has.
     */
    unsigned int Catan::countPlayerResourceCards(const Player &player) const {
        unsigned int totalCards = 0;
        for (const auto &entry: cardOwnership) {
            CardType cardType = cards.at(entry.first)->getType();
            if (entry.second->getName() == player.getName() && isResourceCard(cardType)) {
                totalCards++;
            }
        }
        return totalCards;
    }

    /**
     * @brief Checks if a given CardType is a resource card.
     *
     * @param type The CardType to check.
     * @return bool True if the CardType is a resource card, false otherwise.
     */
    bool Catan::isResourceCard(CardType type) const {
        return (type == CardType::Lumber || type == CardType::Brick || type == CardType::Grain ||
                type == CardType::Wool || type == CardType::Ore);
    }

    /**
     * @brief Helper function to handle the return of resource cards when a 7 is rolled.
     *
     * @param player The player who needs to return cards.
     */
    void Catan::handleReturnCardsForSeven(Player &player) {
        unsigned int numOfResourceCards = countPlayerResourceCards(player);
        if (numOfResourceCards > 7) {
            unsigned int numOfCardsToReturn = numOfResourceCards / 2;
            for (unsigned int i = 0; i < numOfCardsToReturn; i++) {
                menuForDiceSeven(player);
            }
        }
    }

    /**
     * @brief Handles the event when a 7 is rolled, forcing players with more than 7 cards to return half of them.
     */
    void Catan::handleSeven() {
        std::vector<Player*> players = {&player1, &player2, &player3};

        for (Player* p : players) {
            handleReturnCardsForSeven(*p);
        }


        std::cout << "\nDice 7 handling has been completed.\n" << std::endl;
    }


    /**
     * @brief Displays a menu for the player to choose a resource card to return to the bank when a 7 is rolled.
     *
     * @param player The player who needs to return cards.
     */
    void Catan::menuForDiceSeven(const Player &player) {
        bool returnSuccess;
        while (true) {
            std::cout << std::endl;
            std::cout << player.getName() << ", please choose a resource to return to the bank.\n" << std::endl;
            std::cout << "1. Lumber" << std::endl;
            std::cout << "2. Brick" << std::endl;
            std::cout << "3. Wool" << std::endl;
            std::cout << "4. Grain" << std::endl;
            std::cout << "5. Ore" << std::endl;
            int choice;
            std::cin >> choice;

            switch (choice) {
                case 1:
                    returnSuccess = returnCard(player, CardType::Lumber, 1);
                    break;
                case 2:
                    returnSuccess = returnCard(player, CardType::Brick, 1);
                    break;
                case 3:
                    returnSuccess = returnCard(player, CardType::Wool, 1);
                    break;
                case 4:
                    returnSuccess = returnCard(player, CardType::Grain, 1);
                    break;
                case 5:
                    returnSuccess = returnCard(player, CardType::Ore, 1);
                    break;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
            }
            if (choice <= 5 && returnSuccess) {
                break;
            }
        }
    }

    /**
     * @brief Allows the player to trade cards with other players.
     *
     * @param player The player who initiates the trade.
     */
    void Catan::tradeCards(const Player &player) {
        std::vector < Player * > playerSelection = {&player1, &player2, &player3};
        CardType giveResource, getResource;
        unsigned int giveAmount, getAmount;
        unsigned int choice;

        // Menu to select resource type to give
        std::cout << "Select the resource you want to give: (1: Lumber, 2: Brick, 3: Wool, 4: Grain, 5: Ore): ";
        unsigned int giveResourceChoice;
        std::cin >> giveResourceChoice;
        giveResource = static_cast<CardType>(giveResourceChoice - 1);

        std::cout << "Enter the amount you want to give: ";
        std::cin >> giveAmount;

        // Check if the player has enough resources to give
        if (!playerHasCards(player, giveResource, giveAmount)) {
            std::cout << "You don't have enough of the selected resource to give.\n";
            return;
        }

        // Menu to select resource type to get
        std::cout << "Select the resource you want to get (1: Lumber, 2: Brick, 3: Wool, 4: Grain, 5: Ore): ";
        int getResourceChoice;
        std::cin >> getResourceChoice;
        getResource = static_cast<CardType>(getResourceChoice - 1);

        std::cout << "Enter the amount you want to get: ";
        std::cin >> getAmount;

        // Menu to select another player or reject the trade
        std::cout << "Select a player to trade with or reject the trade:\n";
        for (size_t i = 0; i < playerSelection.size(); ++i) {
            std::cout << i + 1 << ". " << playerSelection[i]->getName() << "\n";
        }
        std::cout << playerSelection.size() + 1 << ". Reject trade\n";
        std::cin >> choice;
        std::cout << std::endl;

        if (choice > 0 && choice <= playerSelection.size()) {
            if (choice == playerSelection.size() + 1) {
                std::cout << "Trade rejected.\n";
                return;
            }

            Player &otherPlayer = *playerSelection[choice - 1];

            // Check if the other player has enough resources to get
            if (!playerHasCards(otherPlayer, getResource, getAmount)) {
                std::cout << otherPlayer.getName() << " doesn't have enough of the selected resource to give.\n";
                return;
            }

            // First, return the cards
            returnCard(otherPlayer, getResource, getAmount);
            returnCard(player, giveResource, giveAmount);

            // Then, take the cards
            for (unsigned int i = 0; i < giveAmount; i++) {
                takeCard(otherPlayer, giveResource);
            }
            for (unsigned int i = 0; i < getAmount; i++) {
                takeCard(player, getResource);
            }
            std::cout << "Trade completed successfully!\n";
        } else {
            std::cout << "Trade rejected.\n";
        }
    }

    /**
     * @brief Retrieves the current state of the game board.
     *
     * @return Board The current game board.
     */
    Board Catan::getBoard() {
        return board;
    }
}