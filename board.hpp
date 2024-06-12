/*
 * Author: Sapir Dahan
 * ID: 325732972
 * Mail: sapirdahan2003@gmail.com
 */


#pragma once
#include <string>

#include <vector>
#include "Hexagon.hpp"
#include "Intersection.hpp"
#include "Path.hpp"
#include "CardType.hpp"

namespace ariel {
    class Board {
    public:

        // Constructor
        Board();

        // Destructor
        ~Board();

        /**
         * @brief Get the Hexagon object at the specified coordinates.
         *
         * @param x The x-coordinate of the hexagon.
         * @param y The y-coordinate of the hexagon.
         * @return Hexagon& A reference to the hexagon at the specified coordinates.
         * @throws std::invalid_argument if the hexagon is not found.
         */
        Hexagon &getHexagon(unsigned int x, unsigned int y);

        /**
         * @brief Get the Intersection object at the specified index.
         *
         * @param index The index of the intersection.
         * @return Intersection& A reference to the intersection at the specified index.
         * @throws std::invalid_argument if the intersection index is out of range.
         */
        Intersection &getIntersection(unsigned int index);

        /**
         * @brief Get the Path object at the specified index.
         *
         * @param index The index of the path.
         * @return Path& A reference to the path at the specified index.
         * @throws std::invalid_argument if the path index is out of range.
         */
        Path &getPath(unsigned int index);

        /**
         * @brief Get the number of intersection adjacencies.
         *
         * @return unsigned int The number of intersection adjacencies.
         */
        unsigned int getIntersectionAdjacenciesSize();

        /**
         * @brief Get the number of path adjacencies.
         *
         * @return unsigned int The number of path adjacencies.
         */
        unsigned int getPathAdjacenciesSize();

        /**
         * @brief Get the path adjacencies.
         *
         * @return const std::vector<std::pair<unsigned int, unsigned int>>& A reference to the vector of path adjacencies.
         */
        const std::vector<std::pair<unsigned int, unsigned int>>& getPathAdjacencies() const;

        /**
         * @brief Get the intersection adjacencies.
         *
         * @return const std::vector<std::vector<std::pair<unsigned int, unsigned int>>> A vector of vectors containing pairs of unsigned integers representing intersection adjacencies.
         */
        const std::vector<std::vector<std::pair<unsigned int, unsigned int>>> getIntersectionAdjacencies();

        /**
         * @brief Get the hexagons.
         *
         * @return const std::vector<Hexagon>& A reference to the vector of hexagons.
         */
        const std::vector<Hexagon>& getHexagons() const;

        /**
         * @brief Get the intersections.
         *
         * @return const std::vector<Intersection>& A reference to the vector of intersections.
         */
        const std::vector<Intersection>& getIntersections() const;

        /**
         * @brief Display the intersections on the board.
         */
        void showIntersections() const;

        /**
         * @brief Display the roads on the board.
         */
        void showRoads() const;

    private:
        std::vector<Hexagon> hexagons;
        std::vector<Intersection> intersections;
        std::vector<Path> paths;

        /**
         * @brief Initialize the intersections based on adjacencies.
         */
        void initializeIntersections();

        /**
         * @brief Initialize the paths based on adjacencies.
         */
        void initializePaths();

        // Define intersection adjacencies
        const std::vector<std::vector<std::pair<unsigned int, unsigned int>>> intersectionAdjacencies = Intersection::getIntersections();

        // Define path adjacencies
        const std::vector<std::pair<unsigned int, unsigned int>> pathAdjacencies = {{0,  1},
                                                                  {1,  2},
                                                                  {2,  3},
                                                                  {3,  4},
                                                                  {4,  5},
                                                                  {5,  6},
                                                                  {0,  8},
                                                                  {2,  10},
                                                                  {4,  12},
                                                                  {6,  14},
                                                                  {7,  8},
                                                                  {8,  9},
                                                                  {9,  10},
                                                                  {10, 11},
                                                                  {11, 12},
                                                                  {12, 13},
                                                                  {13, 14},
                                                                  {14, 15},
                                                                  {7,  17},
                                                                  {9,  19},
                                                                  {11, 21},
                                                                  {13, 23},
                                                                  {15, 25},
                                                                  {16, 17},
                                                                  {17, 18},
                                                                  {18, 19},
                                                                  {19, 20},
                                                                  {20, 21},
                                                                  {21, 22},
                                                                  {22, 23},
                                                                  {23, 24},
                                                                  {24, 25},
                                                                  {25, 26},
                                                                  {16, 27},
                                                                  {18, 29},
                                                                  {20, 31},
                                                                  {22, 33},
                                                                  {24, 35},
                                                                  {26, 37},
                                                                  {27, 28},
                                                                  {28, 29},
                                                                  {29, 30},
                                                                  {30, 31},
                                                                  {31, 32},
                                                                  {32, 33},
                                                                  {33, 34},
                                                                  {34, 35},
                                                                  {35, 36},
                                                                  {36, 37},
                                                                  {28, 38},
                                                                  {30, 40},
                                                                  {32, 42},
                                                                  {34, 44},
                                                                  {36, 46},
                                                                  {38, 39},
                                                                  {39, 40},
                                                                  {40, 41},
                                                                  {41, 42},
                                                                  {42, 43},
                                                                  {43, 44},
                                                                  {44, 45},
                                                                  {45, 46},
                                                                  {39, 47},
                                                                  {41, 49},
                                                                  {43, 51},
                                                                  {45, 53},
                                                                  {47, 48},
                                                                  {48, 49},
                                                                  {49, 50},
                                                                  {50, 51},
                                                                  {51, 52},
                                                                  {52, 53}};
    };

    // The board hexagon types
    const std::vector<CardType> HexagonTypes = {
            CardType::Ore, CardType::Wool, CardType::Lumber, CardType::Grain, CardType::Brick,
            CardType::Wool, CardType::Brick, CardType::Grain, CardType::Lumber,
            CardType::Lumber, //Middle hexagon should have been Desert but there is no such CardType
            CardType::Lumber, CardType::Ore, CardType::Lumber, CardType::Ore, CardType::Grain,
            CardType::Wool, CardType::Brick, CardType::Grain, CardType::Wool
    };

    // The board hexagon numbers
    const std::vector<unsigned int> HexagonNumbers = {
            10, 2, 9, 12, 6, 4, 10, 9, 11,
            1, //Middle hexagon should have been Desert but there is no such CardType, so it will never be equal to sum of dice
            3, 8, 8, 3, 4, 5, 5, 6, 11};
}