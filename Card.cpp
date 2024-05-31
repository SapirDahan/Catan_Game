#include "Card.hpp"

namespace ariel {

    void Card::setHolder(Player* holder) {
        this->holder = holder;
    }

    Player* Card::getHolder() const {
        return holder;
    }


}
