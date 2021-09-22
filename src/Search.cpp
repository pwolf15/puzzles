#include "Search.hpp"

#include <iostream>

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