#include "ResourceCard.hpp"

namespace ariel {

    /**
     * @brief Constructs a ResourceCard with a specific type.
     *
     * @param type The type of the resource card.
     */
    ResourceCard::ResourceCard(CardType type) : type(type) {}

    /**
     * @brief Gets the type of the resource card.
     *
     * @return CardType The type of the resource card.
     */
    CardType ResourceCard::getType() const {
        return type;
    }

}
