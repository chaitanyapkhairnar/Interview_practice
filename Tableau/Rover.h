/*
 * Header file with class member definitions
 */
#ifndef ROVER_H
#define ROVER_H

#include <string>
#include <vector>
#include <utility>
#include <array>

#define MOVE_DIRECTIONS 4

namespace Rover
{
    static std::array<int, MOVE_DIRECTIONS> rowMove{0, 0, 1, -1};
    static std::array<int, MOVE_DIRECTIONS> columnMove{1, -1, 0, 0};
    
    struct Coordinate
    {
        int X;
        int Y;
    };

    using Grid = std::vector<std::vector<int>>;      // Same as #define
    using Visited = std::vector<std::vector<bool>>;

    /*
     * This class handles the mappings of the movement for a rover.
     */
    class RoverMapper
    {
    public:
        RoverMapper(int width, int height, std::string &gridStr);
        bool getPath(Coordinate start, Coordinate end);
    
    private:
        void createGrid(std::string &gridStr);
        bool isValidMove(Coordinate const &newPosition, Visited const &visited);
        bool getPathInternal(Coordinate start, Coordinate end,
                             std::vector<Coordinate> &result,
                             int result_idx, Visited &visited);
        int m_width;
        int m_height;
        Grid m_grid;

    };
}//namespace

#endif
