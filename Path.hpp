#pragma

#include "player.hpp"
#include <utility>

using namespace ariel;

class Path {
public:
    Path(int index, int intersection1, int intersection2);

    int getIndex() const;
    Player* getOwner() const;
    void setOwner(Player* owner);
    std::pair<int, int> getIntersections() const;

private:
    int index;
    Player* owner;
    std::pair<int, int> intersections;
};
