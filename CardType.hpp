#pragma once

namespace ariel {

    // Enum class representing the different types of cards in the game.
    enum class CardType {
        Lumber,         // Represents a Lumber resource card.
        Brick,          // Represents a Brick resource card.
        Wool,           // Represents a Wool resource card.
        Grain,          // Represents a Grain resource card.
        Ore,            // Represents an Ore resource card.
        Knight,         // Represents a Knight development card.
        VictoryPoint,   // Represents a Victory Point development card.
        RoadBuilding,   // Represents a Road Building development card.
        YearOfPlenty,   // Represents a Year of Plenty development card.
        Monopoly,       // Represents a Monopoly development card.
        LargestArmy     // Represents a Largest Army special card.
    };

}
