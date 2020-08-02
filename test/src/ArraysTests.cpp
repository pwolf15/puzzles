#include <iostream>

#include "ArraysTests.hpp"
#include "Arrays.hpp"

TEST(Arrays, RemoveDuplicates)
{
    const std::vector<std::vector<int>> tests = {
        {},
        {1, 1, 2},
        {1, 1, 2, 3, 3},
        {1}};

    const std::vector<std::pair<int, std::vector<int>>> expected = {
        {0, {}},
        {2, {1, 2}},
        {3, {1, 2, 3}},
        {1, {1}},
    };

    int i = 0;
    for (auto test : tests)
    {
        auto soln = removeDuplicates(test);
        CHECK_EQUAL(expected[i].first, soln);
        i++;
    };
};

TEST(Arrays, Rotate)
{
    const std::vector<std::pair<int, std::vector<int>>> tests = {
        {3, {1, 2, 3, 4, 5, 6, 7}},
        {2, {-1, -100, 3, 99}},
        {2, {-1}},
        {3, {1, 2}},
    };

    const std::vector<std::vector<int>> expected = {
        {5, 6, 7, 1, 2, 3, 4},
        {3, 99, -1, -100},
        {-1},
        {2, 1},
    };

    int i = 0;
    for (auto test : tests)
    {
        rotate(test.second, test.first);
        CHECK_EQUAL(expected[i].size(), test.second.size());
        for (size_t j = 0; j < expected[i].size(); j++)
        {
            CHECK_EQUAL(expected[i][j], test.second[j]);
        }
        i++;
    };
};

TEST(Arrays, RotateImage)
{
    auto matricesEqual = [](std::vector<std::vector<int>> A, std::vector<std::vector<int>> B)
    {
        for (size_t i = 0; i < A.size(); ++i)
        {
            for (size_t j = 0; j < A.size(); ++j)
            {
                if (A[i][j] != B[i][j])
                {
                    return false;
                }
            }
        }

        return true;
    };

    std::vector<std::vector<int>> example =
        {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9},
        };

    rotate(example);

    std::vector<std::vector<int>> expected =
        {
            {7, 4, 1},
            {8, 5, 2},
            {9, 6, 3},
        };

    CHECK(matricesEqual(example, expected));
};

TEST(Arrays, EvenOdd)
{
    auto partitioned = [](std::vector<int> vec)
    {
        bool foundOdd = false;
        for (auto el: vec)
        {
            if (foundOdd && el % 2 == 0)
            {
                return false;
            }
            else if (!foundOdd && el % 2 == 1)
            {
                foundOdd = true;
            }
        }

        return true;
    };

    std::vector<int> vec = {0,1,2,3,4,5,6,7,8};
    EvenOdd(&vec);
    CHECK(partitioned(vec));
};

static bool partitioned(std::vector<Color> vec, Color pivot)
{
    bool pivotSeen      = false;
    bool pivotPassed    = false;

    for (auto el: vec)
    {
        if (el < pivot && (pivotSeen || pivotPassed))
        {
            return false;
        }
        else if (el == pivot && !pivotSeen)
        {
            pivotSeen = true;
        }
        else if (el > pivot && !pivotSeen)
        {
            return false;
        }
        else if (el == pivot && pivotPassed)
        {
            return false;
        }
        else if (el > pivot && !pivotPassed)
        {
            pivotPassed = true;
        }
    }

    return true;
}

TEST(Arrays, DutchFlagPartition)
{
    for (int i = 0; i < 10000; i++)
    {

    std::vector<Color> vec;
    srand(time(NULL));
    for (int i = 0; i < 100; i++)
    {
        int randValue = rand() % 3;
        switch (randValue)
        {
            case 0:
                vec.push_back(Color::kRed);
                break;
            case 1:
                vec.push_back(Color::kWhite);
                break;
            case 2:
                vec.push_back(Color::kBlue);
                break;
        }
    }

        auto pivot = vec[0];
        DutchFlagPartition(0, &vec);
        if (!partitioned(vec, pivot))
        {
            size_t j = 0;
            for (auto el: vec)
            {
                std::cout << "Vec[" << j << "]: " << el << std::endl;
                j++;
            }
        }

        CHECK(partitioned(vec, pivot));
    }
}