#include "doctest.h"
#include "catan.hpp"
#include "board.hpp"
#include "player.hpp"
#include "CardType.hpp"
#include "ResourceCard.hpp"
#include "DevelopmentCard.hpp"
#include "SpecialCard.hpp"
#include "Dice.hpp"

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

    for (int i = 0; i < 100; ++i) {
        unsigned int roll = dice.roll();
        CHECK(roll >= 1);
        CHECK(roll <= 6);
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
    ariel::Player p1("Player1");
    ariel::Player p2("Player2");
    ariel::Player p3("Player3");

    ariel::Catan game(p1, p2, p3);

    game.ChooseStartingPlayer();
    CHECK(game.checkTurn()->getName() == "Player1");

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
    ariel::Player p1("Player1");
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
    ariel::Player p1("Player1");
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
    ariel::Player p1("Player1");
    ariel::Player p2("Player2");
    ariel::Player p3("Player3");

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
