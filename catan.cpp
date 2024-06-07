#include "catan.hpp"
#include "Intersection.hpp"
#include "Hexagon.hpp"
#include "CardType.hpp"

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
            std::cout << "Card of type " << cardTypeToString(type) << " handed to " << player.getName() << std::endl; // Debug statement
            return true;
        }
        std::cout << "Card of type " << cardTypeToString(type) << " is not available." << std::endl;
        return false;
    }

//    bool Catan::returnCard(Player& player, CardType type, unsigned int amount) {
//        unsigned int counter = 0;
//        for (const auto& entry : cardOwnership) {
//            unsigned int card = entry.first;
//            if ((cards[card]->getType() == type) && (entry.second->getName() == player.getName())) {
//                cardOwnership.erase(card);
//                counter++;
//            }
//            if(counter == amount){
//                cout << player.getName() << " has just returned " << amount << " " << cardTypeToString(type) << " card/s to the bank." << endl;
//                return true;
//            }
//        }
//        std::cout << "No card of type " << static_cast<int>(type) << " owned by " << player.getName() << " to return." << std::endl;
//        return false;
//    }

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
                cout << player.getName() << " has just returned " << amount << " " << cardTypeToString(type)
                     << " card/s to the bank." << endl;
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
}