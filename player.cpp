#include "player.hpp"

namespace ariel {
    // Constructor
    Player::Player(string name): name(name) {
    }

    void Player::placeSettlement(vector<string> places, vector<int> placesNum, Board b) {
        // Method implementation goes here
    }

    void Player::placeRoad(vector<string> places, vector<int> placesNum, Board b) {
        // Method implementation goes here
    }

    void Player::rollDice() {
        // Method implementation goes here
    }

    void Player::endTurn() {
        // Method implementation goes here
    }

    void Player::trade(Player p, string give, string get, unsigned int giveAmount, unsigned int getAmount) {
        bool flag = true;

        for(unsigned int i = 0; i < resources.size(); i++){
            if(give == resources[i]){
                if(resourcesValues[i] < giveAmount){
                    flag = false;
                }
            }
        }

        for(unsigned int i = 0; i < resources.size(); i++){
            if(get == p.resources[i]){
                if(resourcesValues[i] < getAmount){
                    flag = false;
                }
            }
        }

        // Invalid transaction
        if(!flag){
            throw runtime_error("The transaction is invalid as it would result in a negative balance for one of the parties involved.");
        }

        for(unsigned int i = 0; i < resources.size(); i++){
            if(give == resources[i]){
                resourcesValues[i] -= giveAmount;
                p.resourcesValues[i] += giveAmount;
            }
        }

        for(unsigned int i = 0; i < resources.size(); i++){
            if(get == p.resources[i]){
                resourcesValues[i] += getAmount;
                p.resourcesValues[i] -= getAmount;
            }
        }

    }

    void Player::buyDevelopmentCard() {
        // Method implementation goes here
    }

    void Player::printPoints() const{
        cout<<"Points for " << name << ": " << points <<endl;
    }
}
