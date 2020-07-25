#include <iostream>

#include "ArraysTests.hpp"
#include "Arrays.hpp"

TEST(Arrays, RemoveDuplicates)
{
    CHECK(1 == 1);
    const std::vector<std::vector<int>> tests = {
        { },
        { 1, 1, 2 },
        { 1, 1, 2, 3, 3},
        { 1 }
    };

    const std::vector<std::pair<int, std::vector<int>>> expected = {
        { 0, { } },
        { 2, { 1, 2 }},
        { 3, { 1, 2, 3}},
        { 1, { 1 }},
    };

    int i = 0;
    for (auto test : tests)
    {
        auto soln = removeDuplicates(test);
        CHECK_EQUAL(expected[i].first, soln);
        i++;
    };
}
