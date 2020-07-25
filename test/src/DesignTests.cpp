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

