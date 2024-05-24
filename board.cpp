#include "board.hpp"

Board::Board() {
    // Generate hexagonal grid with 5 rows
    int rowLengths[5] = {3, 4, 5, 4, 3};
    for (int x = 0; x < 5; ++x) {
        for (int y = 0; y < rowLengths[x]; ++y) {
            hexagons.emplace_back(Hexagon(Hexagon::Desert, 0, x, y));
        }
    }

    for (int i = 0; i < intersectionAdjacencies.size(); ++i) {
        intersections.emplace_back(Intersection(i));
    }


    initializeIntersections();
    initializePaths();
}

Hexagon& Board::getHexagon(int x, int y) {
    for (auto& hex : hexagons) {
        if (hex.getX() == x && hex.getY() == y) {
            return hex;
        }
    }
    throw std::out_of_range("Hexagon not found");
}

Intersection& Board::getIntersection(int index) {
    if (index < 0 || index >= intersections.size()) {
        throw std::out_of_range("Intersection index out of range");
    }
    return intersections[index];
}

Path& Board::getPath(int index) {
    if (index < 0 || index >= paths.size()) {
        throw std::out_of_range("Path index out of range");
    }
    return paths[index];
}

void Board::initializeIntersections() {
    for (int i = 0; i < intersectionAdjacencies.size(); ++i) {
        for (const auto& hexagon : intersectionAdjacencies[i]) {
            intersections[i].addAdjacentHexagon(hexagon.first, hexagon.second);
        }
    }
}

void Board::initializePaths() {
    for (int i = 0; i < pathAdjacencies.size(); ++i) {
        paths.emplace_back(Path(i, pathAdjacencies[i].first, pathAdjacencies[i].second));
    }
}
