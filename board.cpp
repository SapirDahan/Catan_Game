#include "board.hpp"
#include <iostream>

using namespace ariel;
using namespace std;

Board::Board() {
    // Generate hexagonal grid with 5 rows
    unsigned int rowLengths[5] = {3, 4, 5, 4, 3};
    unsigned int index = 0;
    for (unsigned int x = 0; x < 5; ++x) {
        for (unsigned int y = 0; y < rowLengths[x]; ++y) {
            hexagons.emplace_back(Hexagon(HexagonTypes[index], HexagonNumbers[index], x, y));
            index++;
        }
    }

    for (unsigned int i = 0; i < intersectionAdjacencies.size(); ++i) {
        intersections.emplace_back(Intersection(i));
    }

    initializeIntersections();
    initializePaths();
}

Hexagon& Board::getHexagon(unsigned int x, unsigned int y) {
    for (auto& hex : hexagons) {
        if (hex.getX() == x && hex.getY() == y) {
            return hex;
        }
    }
    throw std::invalid_argument("Hexagon not found");
}

Intersection& Board::getIntersection(unsigned int index) {
    if (index >= intersections.size()) {
        throw std::invalid_argument("Intersection index out of range");
    }
    return intersections[index];
}

Path& Board::getPath(unsigned int index) {
    if (index >= paths.size()) {
        throw std::invalid_argument("Path index out of range");
    }
    return paths[index];
}

void Board::initializeIntersections() {
    for (unsigned int i = 0; i < intersectionAdjacencies.size(); ++i) {
        for (const auto& hexagon : intersectionAdjacencies[i]) {
            intersections[i].addAdjacentHexagon(hexagon.first, hexagon.second);
        }
    }
}

void Board::initializePaths() {
    for (unsigned int i = 0; i < pathAdjacencies.size(); ++i) {
        paths.emplace_back(Path(i, pathAdjacencies[i].first, pathAdjacencies[i].second));
    }
}

unsigned int Board::getIntersectionAdjacenciesSize(){
    return intersectionAdjacencies.size();
}
unsigned int Board::getPathAdjacenciesSize(){
    return pathAdjacencies.size();
}

const std::vector<std::pair<unsigned int, unsigned int>>& Board::getPathAdjacencies() const {
    return pathAdjacencies;
}

const std::vector<std::vector<std::pair<unsigned int, unsigned int>>> Board::getIntersectionAdjacencies(){
    return intersectionAdjacencies;
}

const std::vector<Hexagon>& Board::getHexagons() const {
    return hexagons;
}

const std::vector<Intersection>& Board::getIntersections() const {
    return intersections;
}


