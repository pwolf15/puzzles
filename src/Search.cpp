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
int SearchFirstOfK_PW1(const std::vector<int>& A, int k)
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

int bsearch_iter(std::vector<int>::iterator begin, std::vector<int>::iterator end, int k)
{
  int L = 0, U = end - begin - 1;
  while (L <= U)
  {
    int M = L + (U - L) / 2;
    if (*(begin + M) < k)
    {
      L = M + 1;
    }
    else if (*(begin + M) == k)
    {
      while (*(begin + M) == k && M >= 0)
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

int SearchFirstOfK_PW2(std::vector<int>& A, int k)
{
  int cur = bsearch_iter(A.begin(), A.end(), k);
  int temp = cur;
  int i = 0;
  while (temp != -1)
  {
    cur = temp;
    temp = bsearch_iter(A.begin(), A.begin() + cur, k);
    i++;
  }

  return cur;
}

int SearchFirstOfK(std::vector<int>& A, int k)
{
  return SearchFirstOfK_PW2(A, k);
}