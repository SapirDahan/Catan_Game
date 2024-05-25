#include "ResourceCard.hpp"

namespace ariel {

    ResourceCard::ResourceCard(ResourceType type) : type(type) {}

    const char* ResourceCard::getType() const {
        switch (type) {
            case Lumber: return "Lumber";
            case Brick: return "Brick";
            case Wool: return "Wool";
            case Grain: return "Grain";
            case Ore: return "Ore";
            default: return "Unknown";
        }
    }

    ResourceCard::ResourceType ResourceCard::getResourceType() const {
        return type;
    }

}
