#include "Heaps.hpp"

#include <functional>
#include <queue>
#include <iostream>

// time complexity: O(n log k), where n is number of input strings
// space complexity: O(k)
std::vector<std::string> TopK(
    int k,
    std::vector<std::string>::const_iterator stream_begin,
    const std::vector<std::string>::const_iterator& stream_end)
{
  std::priority_queue<std::string, std::vector<std::string>,
                      std::function<bool(std::string, std::string)>>
      min_heap([](const std::string& a, const std::string& b)
               { return std::size(a) >= std::size(b); });
  while (stream_begin != stream_end)
  {
    min_heap.emplace(*stream_begin);
    if (std::size(min_heap) > k)
    {
      // Remove shortest string. Note that the comparison function
      //    above will order the strings by length.
      min_heap.pop();
    }
    stream_begin = std::next(stream_begin);
  }
  std::vector<std::string> result;
  while (!std::empty(min_heap))
  {
    result.emplace_back(min_heap.top());
    min_heap.pop();
  }
  return result;
}

// time complexity: O(n)
// space complexity: O(1)
std::vector<int> MergeSortedArrays(const std::vector<std::vector<int>>& sorted_arrays)
{
  std::vector<int> result;
  int i = 0, j = 0, k = 0;
  int sz1 = sorted_arrays[0].size(), sz2 = sorted_arrays[1].size(), sz3 = sorted_arrays[2].size();
  while (true)
  {
    if (i >= sz1 && j >= sz2 && k >= sz3)
    {
      break;
    }
    
    int val1 = i < sz1 ? sorted_arrays[0][i] : -1;
    int val2 = j < sz2 ? sorted_arrays[1][j] : -1;
    int val3 = k < sz3 ? sorted_arrays[2][k] : -1;
    int nextVal = -1;

    if (val1 == -1)
    {
      if (val2 == -1) 
      {
        nextVal = val3;
        k++;
      }
      else if (val3 == -1) 
      {
        nextVal = val2;
        j++;
      }
      else if (val2 <= val3)
      {
        nextVal = val2;
        j++;
      }
      else if (val3 < val2)
      {
        nextVal = val3;
        k++;
      }
    }
    else if (val2 == -1)
    {
      if (val1 == -1) 
      {
        nextVal = val3;
        k++;
      }
      else if (val3 == -1) 
      {
        nextVal = val1; 
        i++;
      }
      else if (val1 <= val3)
      {
        nextVal = val1;
        i++;
      }
      else if (val3 < val1)
      {
        nextVal = val3;
        k++;
      }
    }
    else if (val3 == -1)
    {
      if (val1 == -1) 
      {
        nextVal = val2;
        j++;
      }
      else if (val2 == -1) 
      {
        nextVal = val1; 
        i++;
      }
      else if (val1 <= val2)
      {
        nextVal = val1;
        i++;
      }
      else if (val2 < val1)
      {
        nextVal = val2;
        j++;
      }
    }
    else 
    {
      if (val1 <= val2 && val1 <= val3)
      {
        nextVal = val1;
        i++;
      }
      else if (val2 <= val1 && val2 <= val3)
      {
        nextVal = val2;
        j++;
      }
      else if (val3 <= val1 && val3 <= val2)
      {
        nextVal = val3;
        k++;
      }
    }

    result.push_back(nextVal);
  }

  return result;
}