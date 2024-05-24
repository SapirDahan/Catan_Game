#pragma
#include "player.hpp"
#include <vector>
#include <utility>

using namespace ariel;

class Intersection {
public:
    enum Structure { None, Settlement, City };

    Intersection(int index);

    int getIndex() const;
    Structure getStructure() const;
    Player* getOwner() const;
    void setStructure(Structure structure, Player* owner);
    void addAdjacentHexagon(int hexagonX, int hexagonY);
    const std::vector<std::pair<int, int>>& getAdjacentHexagons() const;

private:
    int index;
    Structure structure;
    Player* owner;
    std::vector<std::pair<int, int>> adjacentHexagons;
};