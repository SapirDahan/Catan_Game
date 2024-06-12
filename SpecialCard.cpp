/*
 * Author: Sapir Dahan
 * ID: 325732972
 * Mail: sapirdahan2003@gmail.com
 */

#include "SpecialCard.hpp"

namespace ariel {

    /**
     * @brief Constructs a SpecialCard with a specific type.
     *
     * @param type The type of the special card.
     */
    SpecialCard::SpecialCard(CardType type) : type(type) {}

    /**
     * @brief Gets the type of the special card.
     *
     * @return CardType The type of the special card.
     */
    CardType SpecialCard::getType() const {
        return type;
    }

    /**
     * @brief Constructs a LargestArmyCard, which is a specific type of SpecialCard.
     */
    LargestArmyCard::LargestArmyCard() : SpecialCard(CardType::LargestArmy) {}

}
