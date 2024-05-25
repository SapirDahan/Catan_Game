# pragma once

#include "Card.hpp"


namespace ariel {

    class ResourceCard : public Card {
    public:
        enum ResourceType { Lumber, Brick, Wool, Grain, Ore };

        ResourceCard(ResourceType type);
        const char* getType() const override;
        ResourceType getResourceType() const;

    private:
        ResourceType type;
    };

}
