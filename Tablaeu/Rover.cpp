#include <iostream>
#include "Rover.h"

namespace Rover
{
    /*
     * Constructor for RoverMapper class. It creates a 2d grid of integers
     * from the gridStr string.
     */
    RoverMapper::RoverMapper(int width, int height, std::string &gridStr) {
        m_width = width;
        m_height = height;
        if(gridStr.size() != width*height) {
            throw std::runtime_error("Bad input string for grid\n");
        }
        createGrid(gridStr);
        std::cout << "Created Rover Mapper!!\n";
    }

    /*
     * Function to verify if the move is valid and possible.
     */
    bool RoverMapper::isValidMove(Coordinate newPosition) {
        if(newPosition.X < 0 || newPosition.X >= m_height ||
           newPosition.Y < 0 || newPosition.Y >= m_width ||
           m_visited[newPosition.X][newPosition.Y] == true ||
           m_grid[newPosition.X][newPosition.Y] == 0) {
            return false;
        }
        return true;
    }

    /* 
     * Internal recursive function to get path from start to end
     */
    bool RoverMapper::getPathInternal(Coordinate start, Coordinate end,
                                      std::queue <Coordinate> &result) {
        std::cout << "getPathInternal called\n";
        // Base case
        if(start.X == end.X && start.Y == end.Y) {
            /* We have reached the destination, add this point to queue
             * and print the queue and return.
             */
            std::cout << "In Base case\n";
            result.push(start);
            std::cout << "start.x: " << start.X  << " start.y: " << start.Y << std::endl;
            while(!result.empty()) {
                Coordinate temp = result.front();
                std::cout << temp.X << "," << temp.Y;
                result.pop();
            }
            std::cout << std::endl;
            return true;
        }

        std::cout << "start.x: " << start.X  << " start.y: " << start.Y << std::endl;
        std::cout << "\n";
        // Mark the current node as visited
        m_visited[start.X][start.Y] = true;
        
        // Push the current node in result queue
        result.push(start);

        /*
         * We check for all possible moves from the current location and for
         * each valid move, we recursively call the function. We assume our
         * rover can move only in 2 directions for now. One is straight forward
         * and another is straight downwards.
         */
        for(int i=0; i < moveOptions; i++) {
            Coordinate nextMove;
            nextMove.X = start.X + rowMove[i];
            nextMove.Y = start.Y + columnMove[i];
            std::cout << "next.x: " << nextMove.X  << " next.y: " << nextMove.Y << std::endl;
            std::cout << "\n";
            if(isValidMove(nextMove)) {
                if(getPathInternal(nextMove, end, result)) {
                    // If we get a path, return true
                    return true;
                }
            }
        }
        /*
         * If we come here, then it means there is no path to end from the
         * current start position. So dequeue from the result and return false.
         * As we already marked this point as visited, in future, we will not
         * visit this point again.
         */
        result.pop();
        return false;
    }

    /*
     * Function to get the path from start coordinate to end coordinate. If
     * no path exists, it will throw an error. If path exists, it will print
     * the coordinates of path from start to end including start and end.
     */
    bool RoverMapper::getPath(Coordinate start, Coordinate end) {
        std::cout << "getPath called\n";
        // Result queue
        std::queue <Coordinate> result;
        // Queue used for BFS
        if (getPathInternal(start, end, result)) {
            return true;
        } else {
            throw std::runtime_error("Path does not exist in the grid.\n");
            return false;
        }
    }

    /*
     * Function to construct a 2d grid of integers from the gridStr string.
     * Here, we take first 'width' number of characters
     * from gridStr and create a row of them. Then the next 'width' number of
     * characters will form another row and so on. In the end, we will have
     * total 'height' number of rows in our grid.
     */
    void RoverMapper::createGrid(std::string &gridStr) {
        /* Allocate memory for the grid */
        m_grid.resize(m_height);
        for(auto &each : m_grid) {
            each.resize(m_width);
        }

        /* Allocate memory for visited array */
        m_visited.resize(m_height);
        for(auto &each : m_visited) {
            each.resize(m_width);
        }

        /* Start filling the grid. */
        int h = 0;
        int i = 0;
        while(i < gridStr.size()) {
            int w = 0;
            while(w < m_width) {
                m_grid[h][w] = gridStr[i] - '0';
                w++;
                i++;
            }
            h++;
        }

        /* Initialize visited array to false */
        for(int row = 0; row < m_height; row++) {
            for(int col = 0; col < m_width; col++) {
                m_visited[row][col] = false;
            }
        }
    }

}//namespace
