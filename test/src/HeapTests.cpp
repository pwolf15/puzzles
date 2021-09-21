#include <iostream>

#include <functional>
#include <random>
#include <vector>
#include "Heaps.hpp"

#include "CppUTest/TestHarness.h"

TEST_GROUP(Heaps){

};

TEST(Heaps, TopK)
{
  std::vector<std::string> expected = {"hello", "google", "patrick"};
  std::vector<std::string> input = {"hello", "my",  "name", "is",    "patrick",
                                    "this",  "can", "be",   "google"};
  std::vector<std::string> result = TopK(3, input.cbegin(), input.cend());
  CHECK_EQUAL(expected.size(), result.size());
  for (size_t i = 0; i < expected.size(); ++i)
  {
    CHECK_EQUAL(expected[i], result[i]);
  }
};

TEST(Heaps, MergeSortedArrays)
{
  std::vector<std::vector<int>> arrays = {{3, 5, 7}, {0, 6}, {0, 6, 28}};
  std::vector<int> expected = {0, 0, 3, 5, 6, 6, 7, 28};
  std::vector<int> result = MergeSortedArrays(arrays);
  CHECK_EQUAL(expected.size(), result.size());

  for (size_t i = 0; i < expected.size(); ++i)
  {
    CHECK_EQUAL(expected[i], result[i]);
  }
}

TEST(Heaps, KClosestStars)
{
  std::vector<Star> stars;
  for (size_t i = 0; i < 3; ++i)
  {
    stars.push_back(Star{(double)(rand() % 1000), (double)(rand() % 1000),
                         (double)(rand() % 1000)});

    std::cout << "(" << stars[i].x << "," << stars[i].y << "," << stars[i].z
              << ")"
              << " "
              << "Distance: " << stars[i].Distance() << std::endl;
  }

  std::vector<Star> expected = stars;
  std::sort(expected.begin(), expected.end());
  std::vector<Star> result =
      FindClosestKStars(stars.begin(), stars.end(), stars.size());

  CHECK_EQUAL(expected.size(), result.size());
  for (size_t i = 0; i < result.size(); ++i)
  {
    CHECK_EQUAL(expected[i].x, result[i].x);
    CHECK_EQUAL(expected[i].y, result[i].y);
    CHECK_EQUAL(expected[i].z, result[i].z);
  }
}
