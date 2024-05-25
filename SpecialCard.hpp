# pragma once

#include "Card.hpp"

namespace ariel {

    class SpecialCard : public Card {
    public:
        enum SpecialType { LargestArmy };

        SpecialCard(SpecialType type);
        const char* getType() const override;
        SpecialType getSpecialType() const;

    private:
        SpecialType type;
    };

}