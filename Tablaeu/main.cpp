/*
 * Main file to call the functions related to Rover.
 */
#include <iostream>
#include "Rover.h"

bool checkValidityOfInputs(Rover::Coordinate const & start,
                           Rover::Coordinate const & end,
                           int const width, int const height,
                           std::string const &gridStr)
{
    if(width <= 0 || height <= 0) {
        std::cout << "ERROR : Invalid width or height\n";
        return false;
    }
    if(start.X < 0 || start.X >= height || start.Y < 0 || start.Y >= width) {
        std::cout << "ERROR : Invalid start coordinates\n";
        return false;
    }
    if(end.X < 0 || end.X >= height || end.Y < 0 || end.Y >= width) {
        std::cout << "ERROR : Invalid end coordinates\n";
        return false;
    }

    if(gridStr.size() != width*height) {
        std::cout << "ERROR : Invalid string representing the grid\n";
        return false;
    }

    return true;
}

int main()
{
    Rover::Coordinate start, end;
    int width, height;
    std::string gridStr;
    std::cout << "Please enter the start X coordinate : ";
    std::cin >> start.X;
    std::cout << "Please enter the start Y coordinate : ";
    std::cin >> start.Y;
    std::cout << "Please enter the end X coordinate : ";
    std::cin >> end.X;
    std::cout << "Please enter the end Y coordinate : ";
    std::cin >> end.Y;
    std::cout << "Please enter the width : ";
    std::cin >> width;
    std::cout << "Please enter the height : ";
    std::cin >> height;
    std::cin.ignore();
    std::cout << "Please enter the grid string : ";
    std::getline(std::cin, gridStr);
//    std::cin >> gridStr;

    if(!checkValidityOfInputs(start, end, width, height, gridStr)) {
        return 0;
    }
    try
    {
        /* Create an object of RoverMapper Class and initialize it by creating
         * a 2d grid with the given width, height and gridStr.
         */
        Rover::RoverMapper mapper(width, height, gridStr);
        /* Call getPath to get the path from start coordinate to end coordinate
         * for the rover for this mapper object.
         */
        auto result = mapper.getPath(start, end);
    }
    catch(std::exception const & e)
    {
        std::cout << e.what();
        return 0;
    }
    return 0;
}
