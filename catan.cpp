#include "catan.hpp"
#include "Intersection.hpp"
#include "Hexagon.hpp"
#include "CardType.hpp"
#include <numeric>

using namespace std;

namespace ariel {
    // Constructor
    Catan::Catan(Player& p1, Player& p2, Player& p3) : turn(p1), player1(p1), player2(p2), player3(p3), dice() {
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
        cout  << std::endl << "The starting player is: " << turn.getName() << "!" << endl;
    }


    Board Catan::getBoard() const{
        return board;
    }

    Player Catan::nextPlayer(){
        if(turn.getPoints()>=10){
            std::cout << std::endl << turn.getName() << " is the winner with " << turn.getPoints() << " victory points!!" << std::endl;
            std::cout << std::endl << "GAME OVER!" << std::endl;
            exit(EXIT_SUCCESS);
        }

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

        for (unsigned int i = 0; i < 4; ++i) {
            takeCard(player1, CardType::Lumber);
            takeCard(player1, CardType::Brick);
            takeCard(player2, CardType::Lumber);
            takeCard(player2, CardType::Brick);
            takeCard(player3, CardType::Lumber);
            takeCard(player3, CardType::Brick);
        }
        for (unsigned int i = 0; i < 2; ++i) {
            takeCard(player1, CardType::Wool);
            takeCard(player1, CardType::Grain);
            takeCard(player2, CardType::Wool);
            takeCard(player2, CardType::Grain);
            takeCard(player3, CardType::Wool);
            takeCard(player3, CardType::Grain);
        }
        std::cout << "Each player has received the initial resource cards: 4 Lumber, 4 Bricks, 2 Wool, and 2 Grain." << std::endl;
        std::cout << "Before the game begins, each player shall build two roads and two settlements using these cards." << std::endl;
    }

    bool Catan::takeCard(Player& player, CardType type) {
        unsigned int cardNumber = findAvailableCard(type);
        if (cardNumber != 1000) {
            if (player.getName() == player1.getName()) {
                cardOwnership[cardNumber] = &player1;
            }
            if (player.getName() == player2.getName()) {
                cardOwnership[cardNumber] = &player2;
            }
            if (player.getName() == player3.getName()) {
                cardOwnership[cardNumber] = &player3;
            }
            std::cout << "Card of type " << cardTypeToString(type) << " handed to " << player.getName() << "." << std::endl;
            return true;
        }
        std::cout << "Card of type " << cardTypeToString(type) << " is not available." << std::endl;
        return false;
    }


    bool Catan::returnCard(Player& player, CardType type, unsigned int amount) {
        unsigned int counter = 0;
        std::vector<unsigned int> cardsToErase;
        for (const auto& entry : cardOwnership) {
            unsigned int card = entry.first;
            if ((cards[card]->getType() == type) && (entry.second->getName() == player.getName())) {
                cardsToErase.push_back(card);
                counter++;
            }
            if(counter == amount) {
                if (!cardsToErase.empty()) {
                    for (unsigned int card: cardsToErase) {
                        cardOwnership.erase(card);
                    }
                }
                if (type != CardType::LargestArmy){
                    cout << player.getName() << " has just returned " << amount << " " << cardTypeToString(type)
                         << " card/s to the bank." << endl;
                }
                return true;
            }
        }
        cout << "No card of type " << cardTypeToString(type) << " owned by " << player.getName() << " found." << endl;
        return false;
    }


     unsigned int Catan::findAvailableCard(CardType type) {
        for (unsigned int i = 0; i < cards.size(); i++) {
            if (cards[i]->getType() == type && cardOwnership.find(i) == cardOwnership.end()) {
                return i;
            }
        }
        return 1000;
    }

    bool Catan::playerHasCards(Player& player, CardType type, unsigned int amount) const {
        unsigned int count = 0;
        for (const auto& entry : cardOwnership) {
            if (entry.second->getName() == player.getName() && cards[entry.first]->getType() == type) {
                count++;
                if (count >= amount) {
                    return true;
                }
            }
        }
        return false;
    }

    bool Catan::placeRoad(Player& player, unsigned int pathIndex) {

        if(pathIndex >= board.getPathAdjacenciesSize()){
            std::cout << "Path index is out of bound." << std::endl;
            return false;
        }

        if (board.getPath(pathIndex).getOwner() != nullptr) {
            std::cout << "This path is already occupied." << std::endl;
            return false;
        }

        if (!playerHasCards(player, CardType::Lumber, 1) || !playerHasCards(player, CardType::Brick, 1)) {
            std::cout << "You don't have the required resources (1 Lumber and 1 Brick) to build a road." << std::endl;
            return false;
        }

        returnCard(player, CardType::Lumber, 1);
        returnCard(player, CardType::Brick, 1);
        if (player.getName() == player1.getName()){
            board.getPath(pathIndex).setOwner(&player1);
        }
        if (player.getName() == player2.getName()){
            board.getPath(pathIndex).setOwner(&player2);
        }
        if (player.getName() == player3.getName()){
            board.getPath(pathIndex).setOwner(&player3);
        }
        //board.getPath(pathIndex).setOwner(&player);
        std::cout << player.getName() << ", your road has been placed on path " << pathIndex << "." << std::endl;

        return true;
    }

    bool Catan::placeSettlement(Player& player, unsigned int intersectionIndex) {
        if(intersectionIndex >= board.getIntersectionAdjacenciesSize()){
            std::cout << "Intersection index is out of bound." << std::endl;
            return  false;
        }
        if (board.getIntersection(intersectionIndex).getOwner() != nullptr) {
            std::cout << "Intersection " << intersectionIndex << " is already occupied." << std::endl;
            return false;
        }

        for(const auto& path : board.getPathAdjacencies()){
            if(path.first == intersectionIndex){
                if(board.getIntersection(path.second).getOwner() != nullptr){
                    std::cout << "Illegal place to place settlement. Too close to another settlement/city. Please try again." << std::endl;
                    return false;
                }
            }
            if(path.second == intersectionIndex) {
                if (board.getIntersection(path.first).getOwner() != nullptr) {
                    std::cout
                            << "Illegal place to place settlement. Too close to another settlement/city. Please try again."
                            << std::endl;
                    return false;
                }
            }
        }

        bool hasAdjacentRoad;
        hasAdjacentRoad = false;

        for (unsigned int i = 0; i < board.getPathAdjacenciesSize(); i++) {
            auto intersections = board.getPath(i).getIntersections();
            if ((board.getPath(i).getOwner() != nullptr) && (board.getPath(i).getOwner()->getName() == player.getName()) && ((intersections.first == intersectionIndex) || (intersections.second == intersectionIndex))) {
                hasAdjacentRoad = true;
                break;
            }
        }
        if (!hasAdjacentRoad) {
            std::cout << "Illegal place to place settlement. You must have at least one road adjacent to the intersection. Please try again." << std::endl;
            return false;
        }

        if (!playerHasCards(player, CardType::Lumber, 1) ||
            !playerHasCards(player, CardType::Brick, 1) ||
            !playerHasCards(player, CardType::Wool, 1) ||
            !playerHasCards(player, CardType::Grain, 1)) {

            std::cout << player.getName() << ", you not have the required resources (1 Lumber, 1 Brick, 1 Wool, and 1 Grain) to build a settlement." << std::endl;
            return false;
        }

        returnCard(player, CardType::Lumber, 1);
        returnCard(player, CardType::Brick, 1);
        returnCard(player, CardType::Wool, 1);
        returnCard(player, CardType::Grain, 1);
        if (player.getName() == player1.getName()){
            board.getIntersection(intersectionIndex).setStructure(Intersection::Structure::Settlement, player1);
        }
        if (player.getName() == player2.getName()){
            board.getIntersection(intersectionIndex).setStructure(Intersection::Structure::Settlement, player2);
        }
        if (player.getName() == player3.getName()){
            board.getIntersection(intersectionIndex).setStructure(Intersection::Structure::Settlement, player3);
        }

        std::cout << player.getName() << ", your settlement has been placed on intersection " << intersectionIndex << "." << std::endl;
        addPoints(player, 1);

        return true;

    }


    bool Catan::placeCity(Player& player, unsigned int intersectionIndex) {
        if(intersectionIndex >= board.getIntersectionAdjacenciesSize()){
            std::cout << "Intersection index is out of bound." << std::endl;
            return  false;
        }
        if ((board.getIntersection(intersectionIndex).getOwner() != nullptr) &&  board.getIntersection(intersectionIndex).getOwner()->getName() != player.getName()) {
            std::cout << "This intersection is not owned by " << player.getName() << std::endl;
            return false;
        }

        if(board.getIntersection(intersectionIndex).getStructure() != Intersection::Structure::Settlement){
            std::cout << "Can't update to city because on the intersection there isn't a Settlement." << std::endl;
            return false;
        }

        if (!playerHasCards(player, CardType::Ore, 3) ||
            !playerHasCards(player, CardType::Grain, 2)) {

            std::cout << "The player does not have the required resources (3 Ore and 2 Grain) to build a city." << std::endl;
            return false;
        }
        returnCard(player, CardType::Ore, 3);
        returnCard(player, CardType::Grain, 2);
        if (player.getName() == player1.getName()){
            board.getIntersection(intersectionIndex).setStructure(Intersection::Structure::City, player1);
        }
        if (player.getName() == player2.getName()){
            board.getIntersection(intersectionIndex).setStructure(Intersection::Structure::City, player2);
        }
        if (player.getName() == player3.getName()){
            board.getIntersection(intersectionIndex).setStructure(Intersection::Structure::City, player3);
        }

        std::cout << player.getName() << ", your city has been placed." << std::endl;
        addPoints(player, 1);

        return true;

    }

    void Catan::displayBoard() const {
        board.showIntersections();
        board.showRoads();
    }

    void Catan::showPlayerCards(Player& player) const{

        std::unordered_map<CardType, int> cardCounts;
        unsigned totalCards;

        totalCards = 0;

        for (const auto& entry : cardOwnership) {
            if (entry.second->getName() == player.getName()) {
                CardType cardType = cards.at(entry.first)->getType();
                cardCounts[cardType]++;
                totalCards++;
            }
        }
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

    std::string Catan::cardTypeToString(CardType cardType) const{
        switch (cardType) {
            case CardType::Lumber: return "Lumber";
            case CardType::Brick: return "Brick";
            case CardType::Wool: return "Wool";
            case CardType::Grain: return "Grain";
            case CardType::Ore: return "Ore";
            case CardType::Knight: return "Knight";
            case CardType::VictoryPoint: return "Victory Point";
            case CardType::RoadBuilding: return "Road Building";
            case CardType::YearOfPlenty: return "Year of Plenty";
            case CardType::Monopoly: return "Monopoly";
            case CardType::LargestArmy: return "Largest Army";
            default: return "Unknown";
        }
    }

    void Catan::displayPoints() {
        cout << endl << "Scoreboard:" << endl;
        cout << player1.getName() << " has " << player1.getPoints() << " points" << endl;
        cout << player2.getName() << " has " << player2.getPoints() << " points" << endl;
        cout << player3.getName() << " has " << player3.getPoints() << " points" << endl;
    }

    void Catan::addPoints(Player& player, unsigned int points) {
        if(player.getName() == player1.getName()){
            player1.addPoints(points);
        }
        if(player.getName() == player2.getName()){
            player2.addPoints(points);
        }
        if(player.getName() == player3.getName()){
            player3.addPoints(points);
        }
    }


#include "catan.hpp"
#include "Intersection.hpp"
#include "Hexagon.hpp"

    void Catan::distributeResources(unsigned int diceResult) {

        CardType hexCard;

        // Step 1: Identify all hexagons with the given dice result
        std::vector<Hexagon> matchingHexagons;
        for (const auto& hex : board.getHexagons()) {
            if (hex.getNumber() == diceResult) {
                matchingHexagons.push_back(hex);
            }
        }

        // Step 2: Iterate through all intersections
        for (const auto& intersection : board.getIntersections()) {
            bool adjacentToMatchingHexagon = false;

            // Check if the intersection is adjacent to any matching hexagon
            for (const auto& hex : matchingHexagons) {
                if (intersection.isAdjacentTo(hex)) {
                    adjacentToMatchingHexagon = true;
                    hexCard = hex.getType();
                    break;
                }
            }

            // Step 3: Allocate resources if the intersection is adjacent to a matching hexagon
            if (adjacentToMatchingHexagon) {
                Intersection::Structure structure = intersection.getStructure();
                Player* owner = intersection.getOwner();
                if (owner != nullptr) {
                    if (structure == Intersection::Structure::Settlement) {
                        takeCard(*owner, hexCard);
                    }
                    else if (structure == Intersection::Structure::City) {
                        takeCard(*owner, hexCard);
                        takeCard(*owner, hexCard);
                    }
                }
            }
        }
    }

    bool Catan::buyDevCard(Player& player) {

        // Check if the player has the relevant resource cards to by a development card
        if (!playerHasCards(player, CardType::Ore, 1) ||
            !playerHasCards(player, CardType::Grain, 1) ||
            !playerHasCards(player, CardType::Wool, 1)) {

            std::cout << "The player does not have the required resources (1 Ore, 1 Grain and 1 Wool) to buy a development card." << std::endl;
            return false;
        }

        std::vector<unsigned int> devCardTypeCounter(5, 0);

        for (unsigned int i = 0; i < cards.size(); i++) {
            if (cardOwnership.find(i) == cardOwnership.end()) {
                if (cards[i]->getType() == CardType::Knight){
                    devCardTypeCounter[0] += 1;
                }
                if (cards[i]->getType() == CardType::VictoryPoint){
                    devCardTypeCounter[1] += 1;
                }
                if (cards[i]->getType() == CardType::RoadBuilding){
                    devCardTypeCounter[2] += 1;
                }
                if (cards[i]->getType() == CardType::YearOfPlenty){
                    devCardTypeCounter[3] += 1;
                }
                if (cards[i]->getType() == CardType::Monopoly){
                    devCardTypeCounter[4] += 1;
                }
            }
        }
        unsigned int sumOfDevCards = static_cast<unsigned int>(std::accumulate(devCardTypeCounter.begin(), devCardTypeCounter.end(), 0));
        if (sumOfDevCards == 0){
            std::cout << "\nThere are no further development cards in the pack." << endl;
            return false;
        }

        // Return cards to the bank
        returnCard(player, CardType::Ore, 1);
        returnCard(player, CardType::Grain, 1);
        returnCard(player, CardType::Wool, 1);

        unsigned int index;

        // Generate a random number between 1 and sumOfDevCards
        int randNum = rand() % static_cast<int>(sumOfDevCards) + 1;

        // Find the corresponding card type
        int cumulativeSum = 0;
        for (unsigned int i = 0; i < devCardTypeCounter.size(); ++i) {
            cumulativeSum += devCardTypeCounter[i];
            if (randNum <= cumulativeSum) {
                index = i;
                break;
            }
        }

        // take a development Card
        if(index == 0){
            takeCard(player, CardType::Knight);
            if(player.getName() == player1.getName()){
                player1.addKnights(1);
            }
            if(player.getName() == player2.getName()){
                player2.addKnights(1);
            }
            if(player.getName() == player3.getName()){
                player3.addKnights(1);
            }
            manageLargestArmyCard(); // Manage the Largest Army Card logic and prints status
        }
        if(index == 1){
            takeCard(player, CardType::VictoryPoint);
            if(player.getName() == player1.getName()){
                addPoints(player1,1);
            }
            if(player.getName() == player2.getName()){
                addPoints(player2,1);
            }
            if(player.getName() == player3.getName()){
                addPoints(player3,1);
            }
        }
        if(index == 2){
            takeCard(player, CardType::RoadBuilding);
            takeCard(player, CardType::Brick);
            takeCard(player, CardType::Brick);
            takeCard(player, CardType::Lumber);
            takeCard(player, CardType::Lumber);
        }
        if(index == 3){
            takeCard(player, CardType::YearOfPlenty);
            playYearOfPlentyCard();
            playYearOfPlentyCard();
        }
        if(index == 4){
            takeCard(player, CardType::Monopoly);
            playMonopolyCard();
        }
        nextPlayer(); // Next player turn

        return true;
    }

    void Catan::manageLargestArmyCard(){
        // Check eligibility for largest army

        Player* playerWithMostKnights = nullptr;
        unsigned int maxKnights = 3;  // Must have more than 3 Knight cards

        if (player1.getKnights() >= maxKnights) {
            maxKnights = player1.getKnights();
            playerWithMostKnights = &player1;
        }

        if (player2.getKnights() >= maxKnights) {
            maxKnights = player2.getKnights();
            playerWithMostKnights = &player2;
        }

        if (player3.getKnights() >= maxKnights) {
            playerWithMostKnights = &player3;
        }

        // The previous player returns the card
        if (playerHasCards(player1, CardType::LargestArmy, 1)){
            returnCard(player1, CardType::LargestArmy, 1);
            player1.reducePoints(2);
        }
        if (playerHasCards(player2, CardType::LargestArmy, 1)){
            returnCard(player2, CardType::LargestArmy, 1);
            player2.reducePoints(2);
        }
        if (playerHasCards(player3, CardType::LargestArmy, 1)){
            returnCard(player3, CardType::LargestArmy, 1);
            player3.reducePoints(2);
        }

        // Add two victory points and grant the Largest Army Card
        if (playerWithMostKnights != nullptr){
            if (playerWithMostKnights->getName() == player1.getName()){
                takeCard(player1, CardType::LargestArmy);
                player1.addPoints(2);
            }
            if (playerWithMostKnights->getName() == player2.getName()){
                takeCard(player2, CardType::LargestArmy);
                player2.addPoints(2);
            }
            if (playerWithMostKnights->getName() == player3.getName()){
                takeCard(player3, CardType::LargestArmy);
                player3.addPoints(2);
            }
        }
    }


    void Catan::playMonopolyCard() {
        while (true) {
            std::cout << std::endl;
            std::cout << turn.getName() << ", please choose a resource for your monopoly." << std::endl
                      << std::endl;
            std::cout << "Choose resource: " << std::endl;
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


    void Catan::takeMonopoly(Player& player, CardType type){
        for (auto& entry : cardOwnership) {
            unsigned int cardId = entry.first;
            auto card = cards[cardId];
            if (card->getType() == type) {
                entry.second = &player;
            }
        }
        returnCard(player, CardType::Monopoly, 1);
    }

    void Catan::playYearOfPlentyCard() {
        while (true) {
            std::cout << std::endl;
            std::cout << turn.getName() << ", please choose a resource for your monopoly." << std::endl
                      << std::endl;
            std::cout << "Choose resource: " << std::endl;
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

    unsigned int Catan::countPlayerResourceCards(Player& player) const{

        unsigned int totalCards;

        totalCards = 0;
        for (const auto& entry : cardOwnership) {
            CardType cardType = cards.at(entry.first)->getType();
            if (entry.second->getName() == player.getName() && isResourceCard(cardType)) {
                totalCards++;
            }
        }
        return totalCards;
    }

   bool Catan::isResourceCard(CardType type) const{
        if (type == CardType::Lumber || type == CardType::Brick || type == CardType::Grain || type == CardType::Wool || type == CardType::Ore){
            return true;
        }
       return false;
    }

    void Catan::handleSeven(){
        unsigned int numOfResourceCardsforPlayer1 = countPlayerResourceCards(player1);
        if(numOfResourceCardsforPlayer1 > 7){
            unsigned int numOfCardsToReturn = numOfResourceCardsforPlayer1 / 2;
            for(unsigned int i=0; i<numOfCardsToReturn ; i++){
                menuForDiceSeven(player1);
            }
        }
        unsigned int numOfResourceCardsforPlayer2 = countPlayerResourceCards(player2);
        if(numOfResourceCardsforPlayer2 > 7){
            unsigned int numOfCardsToReturn = numOfResourceCardsforPlayer2 / 2;
            for(unsigned int i=0; i<numOfCardsToReturn ; i++){
                menuForDiceSeven(player2);
            }
        }
        unsigned int numOfResourceCardsforPlayer3 = countPlayerResourceCards(player3);
        if(numOfResourceCardsforPlayer3 > 7){
            unsigned int numOfCardsToReturn = numOfResourceCardsforPlayer3 / 2;
            for(unsigned int i=0; i<numOfCardsToReturn ; i++){
                menuForDiceSeven(player3);
            }
        }
        std::cout << "\nDice 7 handling has been completed.\n" << std::endl;
    }


    void Catan::menuForDiceSeven(Player& player) {
        bool returnSuccess;
        while (true) {
            std::cout << std::endl;
            std::cout << player.getName() << ", please choose a resource to return to the bank." << std::endl
                      << std::endl;
            std::cout << "Choose resource: " << std::endl;
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
                    returnSuccess = returnCard(player, CardType::Brick,1);
                    break;
                case 3:
                    returnSuccess = returnCard(player, CardType::Wool,1);
                    break;
                case 4:
                    returnSuccess = returnCard(player, CardType::Grain,1);
                    break;
                case 5:
                    returnSuccess = returnCard(player, CardType::Ore,1);
                    break;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
            }
            if (choice <= 5 && returnSuccess) {
                break;
            }
        }
    }


    void Catan::tradeCards(Player &player) {
        std::vector<Player*> playerSelection = {&player1, &player2, &player3};
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
            for(unsigned int i=0 ; i<giveAmount ; i++){
                takeCard(otherPlayer, giveResource);
            }
            for(unsigned int i=0 ; i<getAmount ; i++) {
                takeCard(player, getResource);
            }
            std::cout << "Trade completed successfully!\n";
        } else {
            std::cout << "Trade rejected.\n";
        }
    }



}