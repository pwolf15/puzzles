#include <iostream>

#include <functional>
#include <random>
#include <vector>
#include "Search.hpp"

#include "CppUTest/TestHarness.h"

TEST_GROUP(Search)
{

};


TEST(Search, BSearch)
{
  std::vector<int> arr = { 1,2,3,4,5,6,7,8,9};
  int idx = bsearch(3, arr);
  CHECK_EQUAL(2, idx);
}