#include "CppUTest/TestHarness.h"

#include "Design.hpp"
#include <iostream>

TEST_GROUP(Design)
{
 
};

TEST(Design, ShuffledArray)
{
    std::vector<int> nums = { 4, 5, 6 };
    ShuffledArray shuffled(nums);
    
    auto result = shuffled.shuffle();
    result = shuffled.shuffle();
    result = shuffled.reset();
};

TEST(Design, MyHashSet)
{
    MyHashSet hashSet;
    hashSet.add(1);
    hashSet.add(2);
    CHECK(hashSet.contains(1));
    CHECK(!hashSet.contains(3));
    hashSet.add(2);
    CHECK(hashSet.contains(2));
    hashSet.remove(2);
    CHECK(!hashSet.contains(2));
};

TEST(Design, SubrectangleQueries)
{
    std::vector<std::vector<int>> rect =
        {{1,2,1},{4,3,4},{3,2,1},{1,1,1}};
    SubrectangleQueries sq(rect);
    for (int i = 0; i < rect.size(); ++i)
    {
        for (int j = 0; j < rect[i].size(); ++j)
        {
            CHECK_EQUAL(rect[i][j], sq.getValue(i, j));
        }
    }

    CHECK_EQUAL(1, sq.getValue(0, 2));
    sq.updateSubrectangle(0, 0, 3, 2, 5);
    for (int i = 0; i < rect.size(); ++i)
    {
        for (int j = 0; j < rect[i].size(); ++j)
        {
            CHECK_EQUAL(5, sq.getValue(i, j));
        }
    }
    CHECK_EQUAL(5, sq.getValue(0, 2));
    CHECK_EQUAL(5, sq.getValue(3, 1));

    sq.updateSubrectangle(3, 0, 3, 2, 10);
    CHECK_EQUAL(10, sq.getValue(3, 1));
    CHECK_EQUAL(5, sq.getValue(0, 2));
}