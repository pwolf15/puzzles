#ifndef __HEAPS_HPP__
#define __HEAPS_HPP__

#include <string>
#include <vector>
#include <cmath>

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

struct Star 
{
    bool operator<(const Star& that) const
    {
        return Distance() < that.Distance();
    }

    long double Distance() const { return sqrtf(pow(x,2) + pow(y,2) + pow(z,2)); }

    double x, y, z;
};

std::vector<Star> FindClosestKStars(std::vector<Star>::const_iterator stars_begin,
    const std::vector<Star>::const_iterator& stars_end,
    int k);

#endif  // __HEAPS_HPP
