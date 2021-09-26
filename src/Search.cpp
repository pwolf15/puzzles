#include "Search.hpp"

#include <iostream>

// time complexity: O(log n), sorting takes O(n log n)
int bsearch(int t, const std::vector<int>& A)
{
  int L = 0, U = std::size(A) - 1;
  while (L <= U)
  {
    int M = L + (U - L) / 2;
    std::cout << "M: " << M << std::endl;
    if (A[M] < t)
    {
      L = M + 1;
    }
    else if (A[M] == t)
    {
      return M;
    }
    else
    {
      U = M - 1;
    }
  }
  return -1;
}

bool SearchStudent(
    const std::vector<Student>& students,
    const Student& target,
    const std::function<bool(const Student&, const Student&)>& comp_GPA)
{
  return binary_search(std::begin(students), std::end(students), target,
                       comp_GPA);
}

// time complexity: O(log n + n) = O(n)
// space complexity: O(n)
int SearchFirstOfK(const std::vector<int>& A, int k)
{
  int L = 0, U = std::size(A) - 1;
  while (L <= U)
  {
    int M = L + (U - L) / 2;
    if (A[M] < k)
    {
      L = M + 1;
    }
    else if (A[M] == k)
    {
      while (A[M] == k && M >= 0)
      {
        --M;
      }
      return M + 1;
    }
    else
    {
      U = M - 1;
    }
  }
  return -1;
}