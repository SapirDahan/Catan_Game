#include "ResourceCard.hpp"

namespace ariel {

    ResourceCard::ResourceCard(CardType type) : type(type) {}

    CardType ResourceCard::getType() const {
        return type;
    }

}
