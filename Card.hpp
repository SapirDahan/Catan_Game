# pragma once

#include "player.hpp"
#include "CardType.hpp"
#include <memory>

namespace ariel {

    class Card {
    public:
        virtual ~Card() = default; // Virtual destructor for polymorphic cleanup
        virtual CardType getType() const = 0;
        void setHolder(Player* holder);
        Player* getHolder() const;

    private:
        Player* holder = nullptr;
    };

}