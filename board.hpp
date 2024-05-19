/*
 * Author: Sapir Dahan
 * ID: 325732972
 * Mail: sapirdahan2003@gmail.com
 */


#pragma once
#include <string>


using namespace std;

namespace ariel {
    class Board {
    private:
        Board(string name);
    public:
        Board getBoard();
    };
}