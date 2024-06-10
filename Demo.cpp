/**
 * Demo file for Ex3.
 *
 */
#include <iostream>
#include <vector>
#include "catan.hpp"

using namespace std;
using namespace ariel;

int main(){

    // Create three players
    Player player1("A");
    Player player2("B");
    Player player3("C");

    // Initialize the Catan game with the three players
    Catan catanGame(player1, player2, player3);

    // Distribute the initial resource cards to all players
    catanGame.handFirstCards();

    // Choose the starting player
    catanGame.ChooseStartingPlayer();

    // Player 1 places their initial roads and settlements
    catanGame.placeRoad(*catanGame.checkTurn(), 13);
    catanGame.placeRoad(*catanGame.checkTurn(), 41);
    catanGame.placeSettlement(*catanGame.checkTurn(), 10);
    catanGame.placeSettlement(*catanGame.checkTurn(), 29);

    // Move to the next player
    catanGame.nextPlayer();

    // Player 2 places their initial roads and settlements
    catanGame.placeRoad(*catanGame.checkTurn(), 56);
    catanGame.placeRoad(*catanGame.checkTurn(), 52);
    catanGame.placeSettlement(*catanGame.checkTurn(), 40);
    catanGame.placeSettlement(*catanGame.checkTurn(), 44);

    // Move to the next player
    catanGame.nextPlayer();

    // Player 3 places their initial roads and settlements
    catanGame.placeRoad(*catanGame.checkTurn(), 15);
    catanGame.placeRoad(*catanGame.checkTurn(), 58);
    catanGame.placeSettlement(*catanGame.checkTurn(), 13);
    catanGame.placeSettlement(*catanGame.checkTurn(), 42);

    // Move to the next player
    catanGame.nextPlayer();

    std::cout << std::endl << "Initial placements are completed." << std::endl;
    std::cout << std::endl << "Let the game begin!" << std::endl;

    // Distribute resources from adjacent hexagons to all players based on the dice roll
    for(unsigned int i = 2; i <= 12; i++) {
        catanGame.distributeResources(i);
    }

    // Roll the dice and distribute resources based on the result
    unsigned int diceOutcome = catanGame.rollDices();
    std::cout << "Rolling the dice... the output is: " << diceOutcome << endl;
    catanGame.distributeResources(diceOutcome);

    // Handle special case if the dice outcome is 7
    if(diceOutcome == 7){
        catanGame.handleSeven();
    }

    // Repeat dice rolling and resource distribution
    diceOutcome = catanGame.rollDices();
    std::cout << "Rolling the dice... the output is: " << diceOutcome << endl;
    catanGame.distributeResources(diceOutcome);

    if(diceOutcome == 7){
        catanGame.handleSeven();
    }

    diceOutcome = catanGame.rollDices();
    std::cout << "Rolling the dice... the output is: " << diceOutcome << endl;
    catanGame.distributeResources(diceOutcome);

    if(diceOutcome == 7){
        catanGame.handleSeven();
    }

    // Display the current state of the board
    std::cout << "Displaying the board\n" << endl;
    catanGame.displayBoard();

    // Show the cards held by each player
    std::cout << player1.getName() << " has the cards: " << std::endl;
    catanGame.showPlayerCards(player1);

    std::cout << player2.getName() << " has the cards: " << std::endl;
    catanGame.showPlayerCards(player2);

    std::cout << player3.getName() << " has the cards: " << std::endl;
    catanGame.showPlayerCards(player3);

    return 0;
}
