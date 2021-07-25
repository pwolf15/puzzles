#include <iostream>

#include "Heaps.hpp"
#include <functional>

#include "CppUTest/TestHarness.h"

TEST_GROUP(Heaps)
{
 
};

TEST(Heaps, TopK)
{
  std::vector<std::string> expected = { "hello", "google","patrick"};
  std::vector<std::string> input = { "hello", "my", "name", "is", "patrick", "this", "can", "be", "google"};
  std::vector<std::string> result = TopK(3, input.cbegin(), input.cend());
  CHECK_EQUAL(expected.size(), result.size());
  for (size_t i = 0; i < expected.size(); ++i)
  {
    CHECK_EQUAL(expected[i], result[i]);
  }
};
