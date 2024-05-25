# pragma once

#include "player.hpp"
#include <memory>

namespace ariel {

    class Card {
    public:
        virtual ~Card() = default; // Virtual destructor for polymorphic cleanup
        virtual const char* getType() const = 0; // Pure virtual function
        void setHolder(Player* holder);
        Player* getHolder() const;

    private:
        Player* holder = nullptr;
    };

}