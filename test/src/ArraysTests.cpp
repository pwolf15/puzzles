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
    auto matricesEqual = [](std::vector<std::vector<int>> A, std::vector<std::vector<int>> B) {
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
    auto partitioned = [](std::vector<int> vec) {
        bool foundOdd = false;
        for (auto el : vec)
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

    std::vector<int> vec = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    EvenOdd(&vec);
    CHECK(partitioned(vec));
};

static bool partitioned(std::vector<Color> vec, Color pivot)
{
    bool pivotSeen = false;
    bool pivotPassed = false;

    for (auto el : vec)
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
            for (auto el : vec)
            {
                std::cout << "Vec[" << j << "]: " << el << std::endl;
                j++;
            }
        }

        CHECK(partitioned(vec, pivot));
    }
}

TEST(Arrays, MoveZeroes)
{
    auto checkZeroes = [](const std::vector<int> &nums) {
        bool foundZero = false;
        for (auto num : nums)
        {
            if (num && foundZero)
            {
                return false;
            }
            else if (!num && !foundZero)
            {
                foundZero = true;
            }
        }

        return true;
    };

    std::vector<int> nums = {0, 1, 0, 3, 12};
    moveZeroes(nums);
    CHECK(checkZeroes(nums));
    nums = {};
    moveZeroes(nums);
    CHECK(checkZeroes(nums));
    nums = {0};
    moveZeroes(nums);
    CHECK(checkZeroes(nums));
    nums = {1};
    moveZeroes(nums);
    CHECK(checkZeroes(nums));
    nums = {0, 1, 0, 2, 0, 3, 0, 4, 0, 5};
    moveZeroes(nums);
    CHECK(checkZeroes(nums));
    nums = {0, 1};
    moveZeroes(nums);
    CHECK(checkZeroes(nums));
    nums = {1, 0};
    moveZeroes(nums);

    CHECK(checkZeroes(nums));
}

TEST(Arrays, PlusOne)
{
    std::vector<int> example = {1, 3, 9};
    std::vector<int> result = PlusOne(example);

    example = {1};
    result = PlusOne(example);

    example = {9, 9, 9, 9, 9, 9, 9, 9};
    result = PlusOne(example);
}

TEST(Arrays, ContainsDuplicate)
{
    std::vector<int> example = {1, 2, 3, 4};
    CHECK(!containsDuplicate(example));
    example = {1, 2, 3, 1};
    CHECK(containsDuplicate(example));
}

TEST(Arrays, IsValidSudoku)
{
    std::vector<std::vector<char>> sudoku =
        {
            {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
            {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
            {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
            {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
            {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
            {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
            {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
            {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
            {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

    CHECK(isValidSudoku(sudoku));

    sudoku =
        {
            {'8', '3', '.', '.', '7', '.', '.', '.', '.'},
            {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
            {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
            {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
            {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
            {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
            {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
            {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
            {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

    CHECK(!isValidSudoku(sudoku));
}

TEST(Arrays, Multiply)
{
    auto result = Multiply( {-1, 2, 3, 4, 5, 6, 7}, {3, 1, 4, 1, 5, 9, 2, 6, 5});
    std::vector<int> expected = { -3, 8, 7, 8, 5, 0, 6, 6, 1, 3, 1, 3, 2, 5, 5 };
    for (size_t i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    result = Multiply( {1, 2, 3, 4, 5, 6, 7}, {0});
    expected = { 0 };
    for (size_t i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }
}

TEST(Arrays, CanReachEnd)
{
    std::vector<int> setup = {3, 3, 1, 0, 2, 0, 1};

    CHECK(CanReachEnd(setup));

    setup = {3, 2, 0, 0, 2, 0, 1};

    CHECK(!CanReachEnd(setup));

    setup = {2, 4, 1, 1, 0, 2, 3};
    
    CHECK(CanReachEnd(setup));
}

TEST(Arrays, DeleteDuplicates)
{
    const std::vector<std::vector<int>> tests = {
        {},
        {1, 1, 2},
        {1, 1, 2, 3, 3},
        {1},
        {2, 3, 5, 5, 7, 11, 11, 13}
        };

    const std::vector<std::pair<int, std::vector<int>>> expected = {
        {0, {}},
        {2, {1, 2}},
        {3, {1, 2, 3}},
        {1, {1}},
        {6, {2, 3, 5, 7, 11, 13}}
    };

    int i = 0;
    for (auto test : tests)
    {
        auto soln = DeleteDuplicates(&test);
        CHECK_EQUAL(expected[i].first, soln);
        i++;
    };
};

TEST(Arrays, DeleteKey)
{
    const std::vector<std::pair<std::vector<int>, int>> tests = {
        {{}, 0},
        {{1, 1, 2}, 1},
        {{1, 1, 2, 3, 3}, 3},
        {{1}, 1},
        {{2, 3, 5, 5, 7, 11, 11, 13}, 5}
        };

    const std::vector<std::pair<int, std::vector<int>>> expected = {
        {0, {}},
        {1, {2}},
        {3, {1, 1, 2}},
        {0, {0}},
        {6, {2, 3, 7, 11, 11, 13}}
    };

    int i = 0;
    for (auto test : tests)
    {
        auto soln = DeleteKey(&test.first, test.second);
        CHECK_EQUAL(expected[i].first, soln);
        i++;
    };
};

TEST(Arrays, AtMostN)
{
    const std::vector<std::vector<int>> tests = {
        {},
        {1, 1, 2},
        {1, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        {1},
        {2, 3, 5, 5, 5, 5, 5, 5, 5, 7, 11, 11, 13}
        };

    const std::vector<std::pair<int, std::vector<int>>> expected = {
        {0, {}},
        {3, {1, 1, 2}},
        {5, {1, 1, 2, 3, 3}},
        {1, {1}},
        {8, {2, 3, 5, 5, 7, 11, 11, 13}}
    };

    int i = 0;
    for (auto test : tests)
    {
        auto soln = AtMostN(&test);
        CHECK_EQUAL(expected[i].first, soln);
        i++;
    };
};

TEST(Arrays, BuyAndSellStockOnce)
{
    const std::vector<std::vector<double>> tests = {
        {310, 315, 275, 295, 260, 270, 290, 230, 255, 250},
        {300},
        {300, 390, 279}
        };

    const std::vector<double> expected = {
        30,
        0,
        90
    };

    int i = 0;
    for (auto test : tests)
    {
        auto soln = BuyAndSellStockOnce(test);
        CHECK_EQUAL(expected[i], soln);
        i++;
    };
};

TEST(Arrays, LongestContiguousSubarray)
{
    const std::vector<std::vector<int>> tests = {
        {1, 2, 2, 3},
        { 1, 1, 1, 2, 2, 2, 3, 3, 3, 3},
        {},
        { 1, 2, 3, 4, 5, 5, 5, 7, 6, 5, 7, 8, 9 }
        };

    const std::vector<int> expected = {
        2,
        4,
        0,
        3
    };

    int i = 0;
    for (auto test : tests)
    {
        auto soln = longestContiguousSubarray(test);
        CHECK_EQUAL(expected[i], soln);
        i++;
    };
};

TEST(Arrays, BuyAndSellStockTwice)
{
    const std::vector<std::vector<double>> tests = {
        { 12, 11, 13, 9, 12, 8, 14, 13, 15}
        };

    const std::vector<double> expected = {
        10
    };

    int i = 0;
    // for (auto test : tests)
    // {
    //     auto soln = BuyAndSellStockTwice(test);
    //     CHECK_EQUAL(expected[i], soln);
    //     i++;
    // };
};