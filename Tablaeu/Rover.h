#include <string>
#include <vector>
#include <utility>
#include <queue>

namespace Rover
{
    struct Coordinate
    {
        int X;
        int Y;
    };

    using Grid = std::vector<std::vector<int>>;
    using Visited = std::vector<std::vector<bool>>;

    class RoverMapper
    {
    public:
        RoverMapper(int width, int height, std::string &gridStr);
        bool getPath(Coordinate start, Coordinate end);
    
    private:
        void createGrid(std::string &gridStr);
        bool isValidMove(Coordinate newPosition);
        bool getPathInternal(Coordinate start, Coordinate end,
                             std::queue <Coordinate> &result);
        int m_width;
        int m_height;
        Grid m_grid;
        Visited m_visited;
        static const int moveOptions = 2;
        int rowMove[moveOptions] = {0, 1};
        int columnMove[moveOptions] = {1, 0};
    };
}//namespace
