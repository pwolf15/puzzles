#include <iostream>
#include <vector>
#include <math.h>

struct Rect
{
    int x;
    int y;
    int width;
    int height;
};

using namespace std;

bool IsIntersect_PW(const Rect &r1, const Rect &r2)
{
    Rect upper = (r2.height / 2 + r2.y) >= ((r1.height / 2) + r1.y) ? r2 : r1;
    Rect lower = (r2.height / 2 + r2.y) >= ((r1.height / 2) + r1.y) ? r1 : r2;
    int lowerTop    = lower.y + (lower.height / 2);
    int upperBottom = upper.y - (r2.height / 2);

    Rect leftmost = (r2.width / 2 + r2.x) >= ((r1.width / 2) + r1.x) ? r1 : r2;
    Rect rightmost = (r2.width / 2 + r2.x) >= ((r1.width / 2) + r1.x) ? r2 : r1;
    int leftmostRight    = leftmost.x + (lower.width / 2);
    int rightmostLeft = rightmost.x - (rightmost.width / 2);

    if (lowerTop >= upperBottom && leftmostRight >= rightmostLeft)
    {
        return true;
    }

    return false;
}

// assumes x and y represent center of rectangle
Rect IntersectRectangle_PW(const Rect &r1, const Rect &r2)
{
    if (!IsIntersect_PW(r1, r2))
    {
        return {0, 0, -1, -1};
    }

    Rect upper = (r2.height / 2 + r2.y) >= ((r1.height / 2) + r1.y) ? r2 : r1;
    Rect lower = (r2.height / 2 + r2.y) >= ((r1.height / 2) + r1.y) ? r1 : r2;
    int lowerTop    = lower.y + (lower.height / 2);
    int upperBottom = upper.y - (r2.height / 2);

    Rect leftmost = (r2.width / 2 + r2.x) >= ((r1.width / 2) + r1.x) ? r1 : r2;
    Rect rightmost = (r2.width / 2 + r2.x) >= ((r1.width / 2) + r1.x) ? r2 : r1;
    int leftmostRight    = leftmost.x + (lower.width / 2);
    int rightmostLeft = rightmost.x - (rightmost.width / 2);

    return {(leftmostRight + rightmostLeft) / 2, (lowerTop + upperBottom) / 2, leftmostRight - rightmostLeft, lowerTop - upperBottom};
}

bool IsIntersect(const Rect &r1, const Rect &r2)
{
    return r1.x <= r2.x + r2.width && r1.x + r1.width >= r2.x &&
        r1.y <= r2.y + r2.height && r1.y + r1.height >= r2.y;
}

// time complexity: O(1); all operations are constant
// space complexity: O(1)
Rect IntersectRectangle(const Rect &r1, const Rect &r2)
{
    if (!IsIntersect(r1, r2))
    {
        return {0, 0, -1, -1};
    }

    return {
        max(r1.x, r2.x),                                            // bottom-left coord x
        max(r1.y, r2.y),                                            // bottom-left coord y
        min(r1.x + r1.width, r2.x + r2.width) - max(r1.x, r2.x),    // width
        min(r1.y + r1.height, r2.y + r2.height) - max(r1.y, r2.y)}; // height
}

int main()
{
    Rect rect1;
    rect1.x = 0;
    rect1.y = 0;
    rect1.width = 2;
    rect1.height = 2;

    Rect rect2;
    rect2.x = 2;
    rect2.y = 2;
    rect2.width = 2;
    rect2.height = 2;

    Rect result = IntersectRectangle_PW(rect1, rect2);

    std::cout << "x: " << result.x << std::endl;
    std::cout << "y: " << result.y << std::endl;
    std::cout << "width: " << result.width << std::endl;
    std::cout << "height: " << result.height << std::endl;

    rect1.x = 0;
    rect1.y = 1;
    rect1.width = 4;
    rect1.height = 4;

    rect2.x = 0;
    rect2.y = 0;
    rect2.width = 4;
    rect2.height = 4;

    result = IntersectRectangle_PW(rect1, rect2);

    std::cout << "x: " << result.x << std::endl;
    std::cout << "y: " << result.y << std::endl;
    std::cout << "width: " << result.width << std::endl;
    std::cout << "height: " << result.height << std::endl;

    // assume x,y represent bototm left
    rect1.x = -1;
    rect1.y = -1;
    rect1.width = 2;
    rect1.height = 2;

    rect2.x = 1;
    rect2.y = 1;
    rect2.width = 2;
    rect2.height = 2;

    result = IntersectRectangle(rect1, rect2);

    std::cout << "x: " << result.x << std::endl;
    std::cout << "y: " << result.y << std::endl;
    std::cout << "width: " << result.width << std::endl;
    std::cout << "height: " << result.height << std::endl;

    rect1.x = -2;
    rect1.y = -1;
    rect1.width = 4;
    rect1.height = 4;

    rect2.x = -2;
    rect2.y = -2;
    rect2.width = 4;
    rect2.height = 4;

    result = IntersectRectangle(rect1, rect2);

    std::cout << "x: " << result.x << std::endl;
    std::cout << "y: " << result.y << std::endl;
    std::cout << "width: " << result.width << std::endl;
    std::cout << "height: " << result.height << std::endl;

    return 0;
}