/*
 * Author: Sapir Dahan
 * ID: 325732972
 * Mail: sapirdahan2003@gmail.com
 */

#include "doctest.h"
#include "catan.hpp"
#include "board.hpp"
#include "player.hpp"
#include "CardType.hpp"
#include "ResourceCard.hpp"
#include "DevelopmentCard.hpp"
#include "SpecialCard.hpp"
#include "Dice.hpp"
#include <set>

using namespace ariel;

TEST_CASE("Player tests") {
    ariel::Player player1("Alice");
    ariel::Player player2("Bob");

    CHECK(player1.getName() == "Alice");
    CHECK(player2.getName() == "Bob");

    player1.addPoints(3);
    player2.addPoints(5);
    CHECK(player1.getPoints() == 3);
    CHECK(player2.getPoints() == 5);

    player1.reducePoints(1);
    CHECK(player1.getPoints() == 2);

    player2.addKnights(2);
    CHECK(player2.getKnights() == 2);
}

TEST_CASE("CardType tests") {
    ariel::ResourceCard lumberCard(ariel::CardType::Lumber);
    ariel::DevelopmentCard knightCard(ariel::CardType::Knight);
    ariel::SpecialCard largestArmyCard(ariel::CardType::LargestArmy);

    CHECK(lumberCard.getType() == ariel::CardType::Lumber);
    CHECK(knightCard.getType() == ariel::CardType::Knight);
    CHECK(largestArmyCard.getType() == ariel::CardType::LargestArmy);
}

TEST_CASE("Dice tests") {
    ariel::Dice dice;
    std::set<unsigned int> rolledNumbers;

    for (int i = 0; i < 200; ++i) {
        unsigned int roll = dice.roll();
        CHECK(roll >= 1);
        CHECK(roll <= 6);
        rolledNumbers.insert(roll);
    }

    // Ensure that all numbers from 1 to 6 have been rolled at least once
    for (unsigned int num = 1; num <= 6; ++num) {
        CHECK(rolledNumbers.count(num) > 0);
    }
}

TEST_CASE("Board initialization") {
    ariel::Board board;

    CHECK(board.getHexagons().size() == 19);
    CHECK(board.getIntersections().size() == 54);
    CHECK(board.getPathAdjacencies().size() == 72);

    auto hex = board.getHexagon(0, 0);
    CHECK(hex.getType() == ariel::HexagonTypes[0]);
    CHECK(hex.getNumber() == ariel::HexagonNumbers[0]);

    CHECK_THROWS_AS(board.getHexagon(10, 10), std::invalid_argument);
    CHECK_THROWS_AS(board.getIntersection(100), std::invalid_argument);
    CHECK_THROWS_AS(board.getPath(100), std::invalid_argument);
}

TEST_CASE("Catan game tests") {
    ariel::Player p1("Alice");
    ariel::Player p2("Bob");
    ariel::Player p3("Charlie");

    ariel::Catan game(p1, p2, p3);

    game.ChooseStartingPlayer();
    CHECK(game.checkTurn()->getName() == "Alice");

    game.handFirstCards();
    CHECK(game.playerHasCards(p1, ariel::CardType::Lumber, 4));
    CHECK(game.playerHasCards(p1, ariel::CardType::Brick, 4));
    CHECK(game.playerHasCards(p1, ariel::CardType::Wool, 2));
    CHECK(game.playerHasCards(p1, ariel::CardType::Grain, 2));

    CHECK(game.placeRoad(p1, 13));
    CHECK_FALSE(game.placeRoad(p1, 13)); // Road already placed
    CHECK(game.placeSettlement(p1, 10));
    CHECK_FALSE(game.placeSettlement(p1, 10)); // Settlement already placed

    unsigned int roll = game.rollDices();
    CHECK(roll >= 2);
    CHECK(roll <= 12);

    CHECK_NOTHROW(game.distributeResources(roll));
    game.displayPoints();
}

TEST_CASE("Intersection tests") {
    ariel::Player p1("Alice");
    ariel::Intersection intersection(1);

    CHECK(intersection.getIndex() == 1);
    CHECK(intersection.getStructure() == ariel::Intersection::None);
    CHECK(intersection.getOwner() == nullptr);

    intersection.setStructure(ariel::Intersection::Settlement, p1);
    CHECK(intersection.getStructure() == ariel::Intersection::Settlement);

    ariel::Hexagon hex(ariel::CardType::Lumber, 5, 0, 0);
    intersection.addAdjacentHexagon(0, 0);
    CHECK(intersection.isAdjacentTo(hex));
}

TEST_CASE("Path tests") {
    ariel::Player p1("Alice");
    ariel::Path path(1, 0, 1);

    CHECK(path.getIndex() == 1);
    auto intersections = path.getIntersections();
    CHECK(intersections.first == 0);
    CHECK(intersections.second == 1);

    CHECK(path.getOwner() == nullptr);
    CHECK(path.setOwner(&p1));
    CHECK(path.getOwner() == &p1);
    CHECK_FALSE(path.setOwner(&p1)); // Already owned
}

TEST_CASE("Largest Army Card Management") {
    ariel::Player p1("Alice");
    ariel::Player p2("Bob");
    ariel::Player p3("Charlie");

    ariel::Catan game(p1, p2, p3);

    game.takeCard(p1, ariel::CardType::Knight);
    game.takeCard(p1, ariel::CardType::Knight);
    game.takeCard(p1, ariel::CardType::Knight);

    game.manageLargestArmyCard();
    CHECK(game.playerHasCards(p1, ariel::CardType::LargestArmy, 1));

    game.takeCard(p2, ariel::CardType::Knight);
    game.takeCard(p2, ariel::CardType::Knight);
    game.takeCard(p2, ariel::CardType::Knight);
    game.takeCard(p2, ariel::CardType::Knight);

    game.manageLargestArmyCard();
    CHECK_FALSE(game.playerHasCards(p1, ariel::CardType::LargestArmy, 1));
    CHECK(game.playerHasCards(p2, ariel::CardType::LargestArmy, 1));
}

TEST_CASE("Settlement and City placement tests") {
    ariel::Player p1("Alice");
    ariel::Player p2("Bob");
    ariel::Player p3("Charlie");

    ariel::Catan game(p1, p2, p3);

    game.handFirstCards();

    // Place initial roads and settlements
    game.placeRoad(p1, 13);
    game.placeRoad(p1, 41);
    game.placeSettlement(p1, 10);
    game.placeSettlement(p1, 29);

    game.nextPlayer();
    game.placeRoad(p2, 56);
    game.placeRoad(p2, 52);
    game.placeSettlement(p2, 40);
    game.placeSettlement(p2, 44);

    game.nextPlayer();
    game.placeRoad(p3, 15);
    game.placeRoad(p3, 58);
    game.placeSettlement(p3, 13);
    game.placeSettlement(p3, 42);

    game.nextPlayer(); // Back to Alice

    // Give players enough resources for a city
    game.takeCard(p1, ariel::CardType::Ore);
    game.takeCard(p1, ariel::CardType::Ore);
    game.takeCard(p1, ariel::CardType::Ore);
    game.takeCard(p1, ariel::CardType::Grain);
    game.takeCard(p1, ariel::CardType::Grain);

    game.takeCard(p2, ariel::CardType::Ore);
    game.takeCard(p2, ariel::CardType::Ore);
    game.takeCard(p2, ariel::CardType::Ore);
    game.takeCard(p2, ariel::CardType::Grain);
    game.takeCard(p2, ariel::CardType::Grain);

    game.takeCard(p3, ariel::CardType::Ore);
    game.takeCard(p3, ariel::CardType::Ore);
    game.takeCard(p3, ariel::CardType::Ore);
    game.takeCard(p3, ariel::CardType::Grain);
    game.takeCard(p3, ariel::CardType::Grain);

    // Try placing a city where there is no settlement
    CHECK_FALSE(game.placeCity(p1, 20));

    // Try placing a city on a settlement that does not belong to the player
    CHECK_FALSE(game.placeCity(p1, 40));

    // Place a city on the player's own settlement
    CHECK(game.placeCity(p1, 10));

    // Verify the city was placed
    auto& intersection = game.getBoard().getIntersection(10);
    CHECK(intersection.getStructure() == ariel::Intersection::City);
    CHECK(intersection.getOwner()->getName() == p1.getName());
}
