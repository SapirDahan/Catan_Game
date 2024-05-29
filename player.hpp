#pragma once

#include <string>
#include <vector>
#include <memory>

namespace ariel {

    class Player {
    public:
        Player(const std::string& name);
        const std::string& getName() const;
//        void addResourceCard(std::shared_ptr<ResourceCard> card);
//        bool hasResourceCards(ResourceCard::ResourceType type, unsigned int count) const;
//        bool removeResourceCard(ResourceCard::ResourceType type);
        void addPoints(unsigned int points);
        unsigned int getPoints() const;


    private:
        std::string name;
        unsigned int points = 0;
        //std::vector<std::shared_ptr<ResourceCard>> resourceCards;
    };

}
