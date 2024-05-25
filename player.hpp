#pragma once

#include <string>
#include <vector>
#include <memory>
//#include "ResourceCard.hpp"

namespace ariel {

    class Player {
    public:
        Player(const std::string& name);
        const std::string& getName() const;
//        void addResourceCard(std::shared_ptr<ResourceCard> card);
//        bool hasResourceCards(ResourceCard::ResourceType type, unsigned int count) const;
//        bool removeResourceCard(ResourceCard::ResourceType type);

    private:
        std::string name;
        //std::vector<std::shared_ptr<ResourceCard>> resourceCards;
    };

}
