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
// won't work for greater number of arrays...
std::vector<int> MergeSortedArrays_PW1(const std::vector<std::vector<int>>& sorted_arrays)
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

// time complexity: O(n log k)
// space complexity: O(k)
std::vector<int> MergeSortedArrays_PW2(const std::vector<std::vector<int>>& sorted_arrays)
{
  std::vector<int> result;
  struct HeapPair 
  {
    int index;
    int value;
    int arrIndex;
  };

  std::priority_queue<HeapPair, std::vector<HeapPair>,
                      std::function<bool(HeapPair, HeapPair)>>
      min_heap([](const HeapPair& a, const HeapPair& b)
               { return a.value >= b.value; });

  for (int i = 0; i < sorted_arrays.size(); ++i)
  {
    HeapPair hp;
    hp.index = 0;
    hp.value = sorted_arrays[i][0];
    hp.arrIndex = i;
    min_heap.push(hp);
  }

  while (true)
  {
    if (min_heap.empty())
    {
      break;
    }

    HeapPair min = min_heap.top();
    min_heap.pop();
    result.push_back(min.value);

    min.index++;
    if (min.index >= sorted_arrays[min.arrIndex].size())
    {
      continue;
    }
    else 
    {
      min.value = sorted_arrays[min.arrIndex][min.index];
      min_heap.push(min);
    }
  }

  return result;
}

// time complexity: O(n log k)
// space complexity: O(k)
std::vector<int> MergeSortedArrays_EPI(const std::vector<std::vector<int>>& sorted_arrays)
{
  std::priority_queue<IteratorCurrentAndEnd, std::vector<IteratorCurrentAndEnd>,
    std::greater<>>
    min_heap;

  for (const std::vector<int>& sorted_array: sorted_arrays)
  {
    if (!std::empty(sorted_array))
    {
      min_heap.emplace(IteratorCurrentAndEnd{std::cbegin(sorted_array),std::cend(sorted_array)});
    }
  }

  std::vector<int> result;
  while (!std::empty(min_heap))
  {
    IteratorCurrentAndEnd smallest_array = min_heap.top();
    min_heap.pop();
    result.emplace_back(*smallest_array.current);
    if (std::next(smallest_array.current) != smallest_array.end)
    {
      min_heap.emplace(IteratorCurrentAndEnd{std::next(smallest_array.current),
        smallest_array.end});
    }
  }
  return result;
}

std::vector<int> MergeSortedArrays(const std::vector<std::vector<int>>& sorted_arrays)
{
  return MergeSortedArrays_EPI(sorted_arrays);
}

// time complexity: O(n log k)
// space complexity: O(k)
std::vector<Star> FindClosestKStars_PW(std::vector<Star>::const_iterator stars_begin,
    const std::vector<Star>::const_iterator& stars_end,
    int k)
{
  std::vector<Star> result;

  std::priority_queue<Star> max_heap;

  while (stars_begin != stars_end)
  {
    max_heap.emplace(*stars_begin);
    stars_begin++;
    if (max_heap.size() > k) 
    {
      max_heap.pop();
    }
  }

  while (!std::empty(max_heap))
  {
    if (max_heap.size() <= k)
    {
      result.push_back(max_heap.top());
    }
    max_heap.pop();
  }

  return {std::rbegin(result),std::rend(result)};
}

// time complexity: O(n log k)
// space complexity: O(k)
std::vector<Star> FindClosestKStars_EPI(std::vector<Star>::const_iterator stars_begin,
    const std::vector<Star>::const_iterator& stars_end,
    int k)
{
  // max_heap to store the closest k stars seen so far
  std::priority_queue<Star> max_heap;

  while (stars_begin != stars_end)
  {
    // Add each star to the max-heap. If the max-heap size exceeds k,
    // remove the maximum elment from the max-heap.
    max_heap.emplace(*stars_begin++);
    if (max_heap.size() == k + 1) 
    {
      max_heap.pop();
    }
  }

  // Iteratively extract from the max-heap, which yeilds the stars
  // sorted according from furthest to closest.
  std::vector<Star> closest_stars;
  while (!std::empty(max_heap))
  {
    closest_stars.emplace_back(max_heap.top());
    max_heap.pop();
  }

  return {std::rbegin(closest_stars),std::rend(closest_stars)};
}

std::vector<Star> FindClosestKStars(std::vector<Star>::const_iterator stars_begin,
    const std::vector<Star>::const_iterator& stars_end,
    int k)
{
  return FindClosestKStars_EPI(stars_begin, stars_end, k);
}