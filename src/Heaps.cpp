#include "Heaps.hpp"

#include <functional>
#include <queue>

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