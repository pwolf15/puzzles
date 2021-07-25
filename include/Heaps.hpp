#ifndef __HEAPS_HPP__
#define __HEAPS_HPP__

#include <string>
#include <vector>

std::vector<std::string> TopK(
    int k,
    std::vector<std::string>::const_iterator stream_begin,
    const std::vector<std::string>::const_iterator& stream_end);

#endif  // __HEAPS_HPP
