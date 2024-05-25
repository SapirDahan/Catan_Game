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

namespace ariel {
    class Board {
    public:
        Board();

        Hexagon &getHexagon(unsigned int x, unsigned int y);

        Intersection &getIntersection(unsigned int index);

        Path &getPath(unsigned int index);

        unsigned int getIntersectionAdjacenciesSize();
        unsigned int getPathAdjacenciesSize();

    private:
        std::vector<Hexagon> hexagons;
        std::vector<Intersection> intersections;
        std::vector<Path> paths;

        void initializeIntersections();

        void initializePaths();

        // Define intersection adjacencies
        const std::vector<std::vector<std::pair<unsigned int, unsigned int>>> intersectionAdjacencies = {{{0, 0}},
                                                                                       {{0, 0}},
                                                                                       {{0, 0}, {0, 1}},
                                                                                       {{0, 1}},
                                                                                       {{0, 1}, {0, 2}},
                                                                                       {{0, 2}},
                                                                                       {{0, 2}},
                                                                                       {{1, 0}},
                                                                                       {{0, 0}, {1, 0}},
                                                                                       {{0, 0}, {1, 0}, {1, 1}},
                                                                                       {{0, 0}, {0, 1}, {1, 1}},
                                                                                       {{1, 2}, {0, 1}, {1, 1}},
                                                                                       {{0, 1}, {1, 2}, {0, 2}},
                                                                                       {{1, 3}, {1, 2}, {0, 2}},
                                                                                       {{0, 2}, {1, 3}},
                                                                                       {{1, 3}},
                                                                                       {{2, 0}},
                                                                                       {{1, 0}, {2, 0}},
                                                                                       {{1, 0}, {2, 0}, {2, 1}},
                                                                                       {{1, 0}, {1, 1}, {2, 1}},
                                                                                       {{1, 1}, {2, 1}, {2, 2}},
                                                                                       {{1, 1}, {1, 2}, {2, 2}},
                                                                                       {{1, 2}, {2, 2}, {2, 3}},
                                                                                       {{1, 2}, {1, 3}, {2, 3}},
                                                                                       {{1, 3}, {2, 3}, {2, 4}},
                                                                                       {{1, 3}, {2, 4}},
                                                                                       {{2, 4}},
                                                                                       {{2, 0}},
                                                                                       {{2, 0}, {3, 0}},
                                                                                       {{2, 0}, {2, 1}, {3, 0}},
                                                                                       {{2, 1}, {3, 0}, {3, 1}},
                                                                                       {{2, 1}, {2, 2}, {3, 1}},
                                                                                       {{2, 2}, {3, 1}, {3, 2}},
                                                                                       {{2, 2}, {2, 3}, {3, 2}},
                                                                                       {{2, 3}, {3, 2}, {3, 3}},
                                                                                       {{2, 3}, {2, 4}, {3, 3}},
                                                                                       {{2, 4}, {3, 3}},
                                                                                       {{2, 4}},
                                                                                       {{3, 0}},
                                                                                       {{3, 0}, {4, 0}},
                                                                                       {{3, 0}, {3, 1}, {4, 0}},
                                                                                       {{3, 1}, {4, 0}, {4, 1}},
                                                                                       {{3, 1}, {3, 2}, {4, 1}},
                                                                                       {{3, 2}, {4, 1}, {4, 2}},
                                                                                       {{3, 2}, {3, 3}, {4, 2}},
                                                                                       {{3, 3}, {4, 2}},
                                                                                       {{3, 3}},
                                                                                       {{4, 0}},
                                                                                       {{4, 0}},
                                                                                       {{4, 0}, {4, 1}},
                                                                                       {{4, 1}},
                                                                                       {{4, 1}, {4, 2}},
                                                                                       {{4, 2}},
                                                                                       {{4, 2}}};

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
}