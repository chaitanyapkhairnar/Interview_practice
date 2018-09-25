/*
 * This file contains the implementation of RoverMapper class.
 */
#include <iostream>
#include "Rover.h"

namespace Rover
{
    /*
     * Constructor for RoverMapper class.
     * It creates a 2d grid of integers from the gridStr string.
     */
    RoverMapper::RoverMapper(int width, int height, std::string &gridStr) {
        m_width = width;
        m_height = height;
        if(gridStr.size() != width*height) {
            throw std::runtime_error("ERROR: Bad input string for grid\n");
        }
        createGrid(gridStr);
    }

    /*
     * Function to verify if the move is valid and possible.
     */
    bool RoverMapper::isValidMove(Coordinate const &newPosition,
                                  Visited const &visited) {
        if(newPosition.X < 0 || newPosition.X >= m_height ||
           newPosition.Y < 0 || newPosition.Y >= m_width ||
           visited[newPosition.X][newPosition.Y] == true ||
           m_grid[newPosition.X][newPosition.Y] == 0) {
            return false;
        }
        return true;
    }

    /* 
     * Internal recursive function to get path from start to end
     */
    bool RoverMapper::getPathInternal(Coordinate start, Coordinate end,
                                      std::vector<Coordinate> &result,
                                      int result_idx, Visited &visited) {
        /* Base case */
        if(start.X == end.X && start.Y == end.Y) {
            /* We have reached the destination, add this point to vector
             * and print the vector and return true.
             */
            result[result_idx] = start;
            
            std::cout << "Path found as below:\n";
            for(int id = 0; id <= result_idx; id++) {
                std::cout << result[id].X << "," << result[id].Y << std::endl;
                if(id != result_idx) {
                    std::cout << ",";
                }
            }
            std::cout << std::endl;
            return true;
        }

        /* Mark the current node as visited */
        visited[start.X][start.Y] = true;
        
        /* Add the current point to result vector */
        result[result_idx] = start;

        /*
         * We check for all possible moves from the current location and for
         * each valid move, we recursively call the function. We assume our
         * rover can move only in 2 directions for now. One is straight forward
         * and another is straight downwards.
         */
        for(int i=0; i < MOVE_DIRECTIONS; i++) {
            Coordinate nextMove;
            nextMove.X = start.X + rowMove[i];
            nextMove.Y = start.Y + columnMove[i];
            if(isValidMove(nextMove, visited)) {
                if(getPathInternal(nextMove, end, result, result_idx+1, visited)) {
                    /* If we get a path, return true */
                    return true;
                }
            }
        }
        /*
         * If we come here, then it means there is no path to end from the
         * current start position. So we backtrack by not incrementing the result_idx
         * and return false.
         * As we already marked this point as visited, in future, we will not
         * visit this point again.
         */
        return false;
    }

    /*
     * Function to get the path from start coordinate to end coordinate. If
     * no path exists, it will throw an error. If path exists, it will print
     * the coordinates of path from start to end including start and end.
     */
    bool RoverMapper::getPath(Coordinate start, Coordinate end) {
        /* Result vector */
        std::vector<Coordinate> result(m_width*m_height, {0, 0});
        int result_idx = 0;
        
        /* Visited vector */
        Visited visited(m_height, std::vector<bool>(m_width, false));
        
        if (getPathInternal(start, end, result, result_idx, visited)) {
            return true;
        } else {
            throw std::runtime_error("ERROR: Path does not exist in the grid.\n");
        }
        return false;
    }

    /*
     * Function to construct a 2d grid of integers from the gridStr string.
     * Here, we take first 'width' number of characters
     * from gridStr and create a row of them. Then the next 'width' number of
     * characters will form another row and so on. In the end, we will have
     * total 'height' number of rows in our grid.
     */
    void RoverMapper::createGrid(std::string &gridStr) {
        /* Assign size for the grid */
        m_grid.resize(m_height);
        for(auto &each : m_grid) {
            each.resize(m_width);
        }

        /* Start filling the grid. */
        int h = 0;
        int i = 0;
        while(i < gridStr.size()) {
            int w = 0;
            while(w < m_width) {
                m_grid[h][w] = gridStr[i] - '0';
                if(m_grid[h][w] != 0 && m_grid[h][w] != 1) {
                    throw std::runtime_error("ERROR: Grid string contains invalid values.\n");
                }
                w++;
                i++;
            }
            h++;
        }
    }
}/* namespace */
