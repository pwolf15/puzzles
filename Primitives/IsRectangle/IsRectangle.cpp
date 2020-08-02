#include <iostream>
#include <vector>
#include <math.h>

struct Point
{
    int x;
    int y;
};

using namespace std;

bool IsRectangle(std::vector<Point> points)
{

    return true;
}

int main()
{
    
    std::vector<Point> points = 
    {
        { 0, 1},
        {0, 3},
        {4, 1},
        {4, 3}
    };

    std::cout << IsRectangle(points) << std::endl;
    return 0;
}