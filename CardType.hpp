#pragma once

namespace ariel {

    enum class CardType {
        Lumber,
        Brick,
        Wool,
        Grain,
        Ore,
        Knight,
        VictoryPoint,
        RoadBuilding,
        YearOfPlenty,
        Monopoly,
        LargestArmy
    };

    // Return the name of the card based on the enum
    std::string getCardName(CardType cardType) {
        switch (cardType) {
            case CardType::Lumber:
                return "Lumber";
            case CardType::Brick:
                return "Brick";
            case CardType::Wool:
                return "Wool";
            case CardType::Grain:
                return "Grain";
            case CardType::Ore:
                return "Ore";
            case CardType::Knight:
                return "Knight";
            case CardType::VictoryPoint:
                return "Victory Point";
            case CardType::RoadBuilding:
                return "Road Building";
            case CardType::YearOfPlenty:
                return "Year of Plenty";
            case CardType::Monopoly:
                return "Monopoly";
            case CardType::LargestArmy:
                return "Largest Army";
            default:
                return "Unknown";
        }
    }
}