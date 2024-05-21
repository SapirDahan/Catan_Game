#include "catan.hpp"

namespace ariel {
    // Constructor
    Catan::Catan(Player p1, Player p2, Player p3) : turn(p1), player1(p1), player2(p2), player3(p3) {
    }

    void Catan::ChooseStartingPlayer() const{
        cout << "The starting player is: " << turn.getName() << "!" << endl;
    }

    void Catan::printWinner() const{
        if(player1.getPoints() >= 10){
            cout << player1.getName() << " is the winner!!!" << endl;
        }

        else if(player2.getPoints() >= 10){
            cout << player2.getName() << " is the winner!!!" << endl;
        }

        else if(player3.getPoints() >= 10){
            cout << player3.getName() << " is the winner!!!" << endl;
        }

        else{
            cout << "The still go on!" << endl;
        }

    }

    Board Catan::getBoard() const{
        return board;
    }
}
