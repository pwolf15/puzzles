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

TEST(Search, SearchStudent)
{
  std::vector<Student> students = {
    {
      "Julian",
      3.0
    },
    {
      "Bubbles",
      4.0
    },
    {
      "Ricky",
      2.0
    }
  };

  Student ricky = { "Ricky", 2.0 };

  CHECK(SearchStudent(students, ricky, CompGPA));

  Student randy = { "Randy", 2.5 };

  CHECK(!SearchStudent(students, randy, CompGPA));
}

TEST(Search, SearchFirstOfK)
{
  std::vector<int> A = { -14, -10, 2, 108, 108, 243, 285, 285, 285, 401 };
  CHECK_EQUAL(3, SearchFirstOfK(A, 108));
  CHECK_EQUAL(6, SearchFirstOfK(A, 285));
}

TEST(Search, BSearchIter)
{
  std::vector<int> arr = { 1,2,3,4,5,6,7,8,9};
  int idx = bsearch_iter(arr.begin(), arr.end(), 3);
  CHECK_EQUAL(2, idx);
}

TEST(Search, SquareRoot)
{
  CHECK_EQUAL(17,SquareRoot(300));
  CHECK_EQUAL(1,SquareRoot(1));
  CHECK_EQUAL(18,SquareRoot(340));
  CHECK_EQUAL(20,SquareRoot(400));

  for (int i = 4; i < 400; ++i)
  {
    int a = floor(sqrt(i));
    int b = SquareRoot(i);

    CHECK_EQUAL(floor(sqrt(i)), SquareRoot(i));
  }
}

TEST(Search, FindKthLargest)
{
  std::vector<int> A = { 3, 2, 1, 5, 4 };
  // CHECK_EQUAL(5, FindKthLargest(0, &A));
  // CHECK_EQUAL(4, FindKthLargest(1, &A));
  CHECK_EQUAL(3, FindKthLargest(2, &A));
}