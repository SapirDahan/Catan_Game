# pragma once

#include "Card.hpp"
#include "CardType.hpp"


namespace ariel {

    class ResourceCard : public Card {
    public:

        ResourceCard(CardType type);
        CardType getType() const;

    private:
        CardType type;
    };

}
