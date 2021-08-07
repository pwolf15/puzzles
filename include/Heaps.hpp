#ifndef __HEAPS_HPP__
#define __HEAPS_HPP__

#include <string>
#include <vector>

std::vector<std::string> TopK(
    int k,
    std::vector<std::string>::const_iterator stream_begin,
    const std::vector<std::string>::const_iterator& stream_end);

struct IteratorCurrentAndEnd 
{
    bool operator>(const IteratorCurrentAndEnd& that) const 
    {
        return *current > *that.current;
    }

    std::vector<int>::const_iterator current;
    std::vector<int>::const_iterator end;
};

std::vector<int> MergeSortedArrays(const std::vector<std::vector<int>>& sorted_arrays);

#endif  // __HEAPS_HPP
