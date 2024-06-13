/*
 * Author: Sapir Dahan
 * ID: 325732972
 * Mail: sapirdahan2003@gmail.com
 */

#include "board.hpp"
#include <iostream>

using namespace ariel;
using namespace std;

/**
 * @brief Constructs a Board object and initializes the hexagons, intersections, and paths.
 */
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

    // Initialize intersections
    for (unsigned int i = 0; i < intersectionAdjacencies.size(); ++i) {
        intersections.emplace_back(Intersection(i));
    }

    initializeIntersections();
    initializePaths();
}

/**
 * @brief Destructor for the Board class. Clears hexagons and paths.
 */
Board::~Board() {
    hexagons.clear();
    paths.clear();
}

/**
 * @brief Gets a reference to a hexagon based on its coordinates.
 *
 * @param x The x-coordinate of the hexagon.
 * @param y The y-coordinate of the hexagon.
 * @return Hexagon& Reference to the hexagon.
 * @throws std::invalid_argument if the hexagon is not found.
 */
Hexagon& Board::getHexagon(unsigned int x, unsigned int y) {

    // Find the hexagon
    for (auto& hex : hexagons) {
        if (hex.getX() == x && hex.getY() == y) {
            return hex;
        }
    }

    throw std::invalid_argument("Hexagon not found");
}

/**
 * @brief Gets a reference to an intersection based on its index.
 *
 * @param index The index of the intersection.
 * @return Intersection& Reference to the intersection.
 * @throws std::invalid_argument if the intersection index is out of range.
 */
Intersection& Board::getIntersection(unsigned int index) {

    // Check bound
    if (index >= intersections.size()) {
        throw std::invalid_argument("Intersection index out of range");
    }

    return intersections[index];
}

/**
 * @brief Gets a reference to a path based on its index.
 *
 * @param index The index of the path.
 * @return Path& Reference to the path.
 * @throws std::invalid_argument if the path index is out of range.
 */
Path& Board::getPath(unsigned int index) {

    // Check bound
    if (index >= paths.size()) {
        throw std::invalid_argument("Path index out of range");
    }

    return paths[index];
}

/**
 * @brief Initializes the intersections with their adjacent hexagons.
 */
void Board::initializeIntersections() {
    for (unsigned int i = 0; i < intersectionAdjacencies.size(); ++i) {

        // Go over the hexagon the adjacent to the intersection
        for (const auto& hexagon : intersectionAdjacencies[i]) {
            intersections[i].addAdjacentHexagon(hexagon.first, hexagon.second);
        }
    }
}

/**
 * @brief Initializes the paths with their adjacent intersections.
 */
void Board::initializePaths() {
    for (unsigned int i = 0; i < pathAdjacencies.size(); ++i) {
        paths.emplace_back(Path(i, pathAdjacencies[i].first, pathAdjacencies[i].second));
    }
}

/**
 * @brief Gets the size of the intersection adjacencies vector.
 *
 * @return unsigned int Size of the intersection adjacencies vector.
 */
unsigned int Board::getIntersectionAdjacenciesSize() {
    return intersectionAdjacencies.size();
}

/**
 * @brief Gets the size of the path adjacencies vector.
 *
 * @return unsigned int Size of the path adjacencies vector.
 */
unsigned int Board::getPathAdjacenciesSize() {
    return pathAdjacencies.size();
}

/**
 * @brief Gets the path adjacencies vector.
 *
 * @return const std::vector<std::pair<unsigned int, unsigned int>>& Reference to the path adjacencies vector.
 */
const std::vector<std::pair<unsigned int, unsigned int>>& Board::getPathAdjacencies() const {
    return pathAdjacencies;
}

/**
 * @brief Gets the intersection adjacencies vector.
 *
 * @return const std::vector<std::vector<std::pair<unsigned int, unsigned int>>> Reference to the intersection adjacencies vector.
 */
const std::vector<std::vector<std::pair<unsigned int, unsigned int>>> Board::getIntersectionAdjacencies() {
    return intersectionAdjacencies;
}

/**
 * @brief Gets the hexagons vector.
 *
 * @return const std::vector<Hexagon>& Reference to the hexagons vector.
 */
const std::vector<Hexagon>& Board::getHexagons() const {
    return hexagons;
}

/**
 * @brief Gets the intersections vector.
 *
 * @return const std::vector<Intersection>& Reference to the intersections vector.
 */
const std::vector<Intersection>& Board::getIntersections() const {
    return intersections;
}

/**
 * @brief Displays information about intersections with structures.
 */
void Board::showIntersections() const {

    // Go over the intersections
    for (const auto& intersection : intersections) {

        // If there is a settlement or city
        if (intersection.getStructure() != Intersection::Structure::None) {
            string structureName = (intersection.getStructure() == Intersection::Structure::Settlement) ? "Settlement" : "City";
            string ownerName = intersection.getOwner() ? intersection.getOwner()->getName() : "None";
            std::cout << "Intersection Index: " << intersection.getIndex()
                      << ", Structure: " << structureName
                      << ", Owner: " << ownerName << std::endl;
        }
    }
}

/**
 * @brief Displays information about roads and their owners.
 */
void Board::showRoads() const {

    // Go over the paths
    for (const auto& path : paths) {

        // If there is an owner
        if (path.getOwner() != nullptr) {
            std::string ownerName = path.getOwner()->getName();
            std::cout << "Path Index: " << path.getIndex()
                      << ", Owner: " << ownerName << std::endl;
        }
    }
}

