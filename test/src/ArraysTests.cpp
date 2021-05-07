#include <iostream>
#include <unordered_map>

#include "ArraysTests.hpp"
#include "Arrays.hpp"

#include <numeric>

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
        { 12, 11, 13, 9, 12, 8, 14, 13, 15},
        { 3, 91, 4, 95},
        { 3, 4, 91, 95},
        { 3, 91, 89, 95},
        { 3,3,5,0,0,3,1,4 },
        { 1,2,3,4,5 },
        { 7,6,4,3,1 },
        {1,2,4,2,5,7,2,4,9,0},
        };

    const std::vector<double> expected = {
        10,
        179,
        92,
        94,
        6,
        4,
        0,
        13
    };

    int i = 0;
    for (auto test : tests)
    {
        auto soln = BuyAndSellStockTwice(test);
        CHECK_EQUAL(expected[i], soln);
        i++;
    };
};

TEST(Arrays, IntersectII)
{
    std::vector<int> A = {1,2,2,1};
    std::vector<int> B = {2, 2};
    auto result = intersect(A, B);
    for (auto entry: result)
    {
        std::cout << entry << std::endl;
    }
    A = {4,9,5};
    B = {9,4,9,8,4};
    result = intersect(A, B);
    for (auto entry: result)
    {
        std::cout << entry << std::endl;
    }
}

TEST(Arrays, Rearrange)
{
    std::vector<int> A = {7, 1, 5, 62, 43, 3, 13, 16, 17, 19, 24, 32, 87, 64};
    Rearrange(&A);
    size_t i = 0;
    for (auto entry: A)
    {
        std::cout << i << ": " << entry << std::endl;
        i++;
    }
}

TEST(Arrays, GeneratePrimes)
{
    int num = 18;
    auto results = GeneratePrimes(num);
    std::vector<int> resultsExpected = { 2, 3, 5, 7, 11, 13, 17 };
    size_t i = 0;
    for (auto n: results)
    {
        CHECK_EQUAL(resultsExpected[i], n);
        i++;
    }

    num = 23;
    resultsExpected = { 2, 3, 5, 7, 11, 13, 17, 19, 23 };
    i = 0;
    for (auto n: results)
    {
        CHECK_EQUAL(resultsExpected[i], n);
        i++;
    }  
}

TEST(Arrays, ApplyPermutation)
{
    std::vector<int> perm = { 2, 0, 1, 3 };
    std::vector<int> vals = { 1, 2, 3, 4 };
    std::vector<int> expected = { 2, 3, 1, 4 };
    ApplyPermutation(perm, &vals);
    size_t i = 0;
    for (auto val: expected)
    {
        CHECK_EQUAL(expected[i], val);
        i++;
    }

    perm = { 3, 2, 1, 0 };
    vals = { 1, 2, 3, 4 };
    expected = { 4, 3, 2, 1};
    ApplyPermutation(perm, &vals);
    i = 0;
    for (auto val: expected)
    {
        CHECK_EQUAL(expected[i], val);
        i++;
    }
}

TEST(Arrays, NextPermutation)
{
    std::vector<int> perm = {1, 0, 3, 2};
    std::vector<int> expected = { 1, 2, 0, 3};
    std::vector<int> result;

    size_t i = 0;
    result = NextPermutation(perm);
    CHECK(expected.size() == result.size());
    for (auto val: result)
    {
        CHECK_EQUAL(expected[i], result[i]);
        i++;
    }

    perm = { 1, 0, 2, 3, 4};
    expected = { 1, 0, 2, 4, 3};
    result = NextPermutation(perm);

    i = 0;
    CHECK(expected.size() == result.size());
    for (auto val: result)
    {
        CHECK_EQUAL(expected[i], result[i]);
        i++;
    }

    perm = { 1, 2, 3, 4};
    expected = { 1, 2, 4, 3};
    result = NextPermutation(perm);

    i = 0;
    CHECK(expected.size() == result.size());
    for (auto val: result)
    {
        CHECK_EQUAL(expected[i], result[i]);
        i++;
    }

    perm = { 3, 2, 1, 0};
    expected = { };
    result = NextPermutation(perm);

    i = 0;
    CHECK(expected.size() == result.size());
    for (auto val: result)
    {
        CHECK_EQUAL(expected[i], result[i]);
        i++;
    }

    perm = { 1, 2, 3, 4};
    expected = { 1, 2, 4, 3};
    result = NextPermutation(perm);

    i = 0;
    CHECK(expected.size() == result.size());
    for (auto val: result)
    {
        CHECK_EQUAL(expected[i], result[i]);
        i++;
    }

    perm = { 4, 2, 0, 2, 3, 2, 0};
    expected = { 4, 2, 0, 3, 0, 2, 2};
    result = NextPermutation(perm);

    i = 0;
    CHECK(expected.size() == result.size());
    for (auto val: result)
    {
        CHECK_EQUAL(expected[i], result[i]);
        i++;
    }

    perm = { 1, 2 };
    expected = { 2, 1};
    result = NextPermutation(perm);

    i = 0;
    CHECK(expected.size() == result.size());
    for (auto val: result)
    {
        CHECK_EQUAL(expected[i], result[i]);
        i++;
    }

    result = { 3, 2, 1 };
    expected = { 1, 2, 3};
    NextPermutationLC(result);

    i = 0;
    CHECK(expected.size() == result.size());
    for (auto val: result)
    {
        CHECK_EQUAL(expected[i], result[i]);
        i++;
    }

    result = { 4, 2, 0, 2, 3, 2, 0};
    expected = { 4, 2, 0, 3, 0, 2, 2};
    NextPermutationLC(result);

    i = 0;
    for (auto val: result)
    {
        CHECK_EQUAL(expected[i], result[i]);
        i++;
    }
}

TEST(Arrays, RandomSampling)
{
    std::vector<int> in = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    RandomSampling(3, &in);

    for (int i = 0; i < 5; i++)
    {
        std::cout << in[i] << std::endl;
    }
}

TEST(Arrays, OnlineRandomSample)
{
    std::vector<int> in = {1, 1, 1, 1, 1};

    int k = 3;
    std::vector<int> result = OnlineRandomSample(in.begin(), in.end(), k);

    for (int i = 0; i < k && i < result.size(); i++)
    {
        std::cout << result[i] << std::endl;
    }

    std::cout << std::endl;

    std::vector<int> in2 = { 2, 3, 4, 5 };
    result = OnlineRandomSample(in2.begin(), in2.end(), k);
    for (int i = 0; i < k && i < result.size(); i++)
    {
        std::cout << result[i] << std::endl;
    }
}

TEST(Arrays, ComputeRandomPermutation)
{
    std::vector<int> result = ComputeRandomPermutation(10);

    for (auto mem: result)
    {
        std::cout << mem << std::endl;
    }
}

TEST(Arrays, RandomSubset)
{
    int n = 10;
    int k = 5;

    for (int i = 1; i <= 30; i++)
    {
        auto result = RandomSubset(n, k);
        for (auto mem: result)
        {
            std::cout << mem << " ";
        }

        std::cout << "\t\t";

        if (i % 5 == 0)
        {
            std::cout << std::endl;
        }
    }
}

TEST(Arrays, NonuniformRandomNumberGeneration)
{
    std::vector<int> values = { 3, 5, 7, 11 };
    std::vector<double> probabilities = { 9.0f / 18.0f, 6.0f / 18.0f, 2.0f / 18.0f, 1.0f / 18.0f };

    std::unordered_map<int, int> appearances;
    int numIters = 1000000;
    for (int i = 0; i < numIters; i++)
    {
        int val = NonuniformRandomNumberGeneration(values, probabilities);
        if (appearances.find(val) == appearances.end())
        {
            appearances[val] = 0;
        }
        else
        {
            appearances[val]++;
        }
    }

    for (auto val: appearances)
    {
        std::cout << val.first << ", " << val.second<< std::endl;
    }
}

TEST(Arrays, IsValidSudokuEPI)
{
    std::vector<std::vector<int>> sudoku =
        {
            {5, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0},
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 5},
            {0, 0, 0, 0, 8, 0, 0, 7, 9}};

    CHECK(IsValidSudoku(sudoku));

    sudoku =
        {
            {8, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0},
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 5},
            {0, 0, 0, 0, 8, 0, 0, 7, 9}};

    CHECK(!IsValidSudoku(sudoku));
}

TEST(Arrays, MatrixInSpiralOrder)
{
    std::vector<std::vector<int>> input =
    {
        { 1, 2, 3},
        { 4, 5, 6},
        { 7, 8, 9}
    };

    std::vector<int> out = MatrixInSpiralOrder(input);
    for (auto& num: out)
    {
        std::cout << num << ",";
    }

    std::cout << std::endl;

    input = 
    {
        { 1, 2, 3, 4},
        { 5, 6, 7, 8},
        { 9, 10, 11, 12},
        { 13, 14, 15, 16}
    };

    out = MatrixInSpiralOrder(input);

    for (auto& num: out)
    {
        std::cout << num << ",";
    }

    std::cout << std::endl;

    input = 
    {
        {  1,  2,  3,   4,   5},
        {  6,  7,  8,   9,  10},
        { 11, 12, 13,  14,  15},
        { 16, 17, 18,  19,  20},
        { 21, 22, 23,  24,  25},
    };

    out = MatrixInSpiralOrder(input);

    for (auto& num: out)
    {
        std::cout << num << ",";
    }

    std::cout << std::endl;


    input = 
    {
        { 1, 2, 3, 4},
        { 5, 6, 7, 8},
        { 9, 10, 11, 12}
    };

    out = MatrixInSpiralOrder(input);

    for (auto& num: out)
    {
        std::cout << num << ",";
    }

    std::cout << std::endl;

    input = 
    {
        { 7 },
        { 6 },
        { 9 }
    };

    out = MatrixInSpiralOrder(input);

    for (auto& num: out)
    {
        std::cout << num << ",";
    }

    std::cout << std::endl;
}

TEST(Arrays, RotateMatrix)
{
    std::vector<std::vector<int>> input =
    {
        { 1, 2, 3, 4},
        { 5, 6, 7, 8},
        { 9, 10, 11, 12},
        { 13, 14, 15, 16}
    };

    RotateMatrix(&input);
    for (size_t i = 0; i < input.size(); ++i)
    {
        for (size_t j = 0; j < input[0].size(); ++j)
        {
            std::cout << input[i][j] << " ";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;

    input =
    {
        { 1, 2},
        { 3, 4},
    };

    RotateMatrix(&input);
    for (size_t i = 0; i < input.size(); ++i)
    {
        for (size_t j = 0; j < input[0].size(); ++j)
        {
            std::cout << input[i][j] << " ";
        }

        std::cout << std::endl;
    }

    input =
    {
        { 1, 2, 3},
        { 4, 5, 6},
        { 7, 8, 9}
    };

    RotateMatrix(&input);
    for (size_t i = 0; i < input.size(); ++i)
    {
        for (size_t j = 0; j < input[0].size(); ++j)
        {
            std::cout << input[i][j] << " ";
        }

        std::cout << std::endl;
    }

    input =
    {
        { 1, 2, 3, 4, 5},
        { 6, 7, 8, 9, 10},
        { 11, 12, 13, 14, 15},
        { 16, 17, 18, 19, 20},
        { 21, 22, 23, 24, 25}
    };

    RotateMatrix(&input);
    for (size_t i = 0; i < input.size(); ++i)
    {
        for (size_t j = 0; j < input[0].size(); ++j)
        {
            std::cout << input[i][j] << " ";
        }

        std::cout << std::endl;
    }

    input =
    {
        { 1, 2, 3, 4, 5, 6},
        { 7, 8, 9, 10, 11, 12},
        { 13, 14, 15, 16, 17, 18},
        { 19, 20, 21, 22, 23, 24},
        { 25, 26, 27, 28, 29, 30},
        { 31, 32, 33, 34, 35, 36}
    };

    RotateMatrix(&input);
    for (size_t i = 0; i < input.size(); ++i)
    {
        for (size_t j = 0; j < input[0].size(); ++j)
        {
            std::cout << input[i][j] << " ";
        }

        std::cout << std::endl;
    }

    input =
    {
        { 1, 2, 3, 4, 5, 6},
        { 7, 8, 9, 10, 11, 12},
        { 13, 14, 15, 16, 17, 18},
        { 19, 20, 21, 22, 23, 24},
        { 25, 26, 27, 28, 29, 30},
        { 31, 32, 33, 34, 35, 36}
    };
    RotatedMatrix matrix(&input);
    std::cout << "First: " << matrix.ReadIntry(0, 0) << std::endl;
}

TEST(Arrays, GeneratePascalTriangle)
{
    std::vector<std::vector<int>> results = GeneratePascalTriangle(20);

    int i = 1;
    for (auto result: results)
    {
        std::cout << "Row[" << i << "]: ";
        for (auto col: result)
        {
            std::cout << col << " ";
        }
        std::cout << std::endl;
        i++;
    }
}

TEST(Arrays, GeneratePascalRow)
{
    int count = 2;
    for (int j = 0; j <= 10; j++)
    {
        std::vector<int> result = GeneratePascalRow(j);

        if (!result.size()) continue;

        std::cout << result[0];
        for (int i = 1; i < result.size(); ++i)
        {
            std::cout << "," << result[i];
        }

        std::cout << std::endl;
    }
}


TEST(Arrays, RunningSum)
{
    std::vector<int> input = {1, 2, 3, 4};
    std::vector<int> expected = { 1, 3, 6, 10};

    auto result = runningSum(input);
    for (int i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }
}

TEST(Arrays, NumIdenticalPairs)
{
    std::vector<int> vec = {1, 1, 1, 1};
    CHECK_EQUAL(6, numIdenticalPairs(vec));
}

TEST(Arrays, IsBoomerang)
{
    std::vector<std::vector<int>> vec = {{1,1},{2,3},{3,2}};
    CHECK(isBoomerang(vec));

    vec = {{1,1},{2,2},{3,3}};
    CHECK(!isBoomerang(vec));

    vec = {{0,0},{1,1},{1,1}};
    CHECK(!isBoomerang(vec));

    vec = {{0,0},{0,2},{2,1}};
    CHECK(isBoomerang(vec));

    vec = {{0,1},{0,1},{2,1}};
    CHECK(!isBoomerang(vec));

    vec = {{0,1},{2,1},{0,0}};
    CHECK(isBoomerang(vec));
}

TEST(Arrays, KWeakestRows)
{
    std::vector<std::vector<int>> m = 
        {{1,0,0,0},
        {1,1,1,1},
        {1,0,0,0},
        {1,0,0,0}};

    std::vector<int> expected = { 0, 2, 3, 1};
    int k = 4;
    std::vector<int> result;
    // auto result = kWeakestRows(m, k);
    // CHECK_EQUAL(expected.size(), result.size());
    // for (size_t i = 0; i < k; ++i)
    // {
    //     CHECK_EQUAL(expected[i], result[i]);
    // }

    k = 7;
    m = {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},{1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},{1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},{1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},{1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},{1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},{1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},{1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},{1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},{1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},{1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},{1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0}};
    expected = {17,21,3,7,12,25,1};
    result = kWeakestRows(m, k);
    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < k; ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }
}

TEST(Arrays, IsOneBitCharacter)
{
    std::vector<int> input = {1, 1, 0};
    CHECK(isOneBitCharacter(input));
    input = { 1, 1, 1, 0 };
    CHECK(!isOneBitCharacter(input));
}

TEST(Arrays, AddToArrayForm)
{
    std::vector<int> input = { 1, 2, 0, 0 };
    std::vector<int> expected = { 1, 2, 3, 4 };
    int k = 34;

    std::vector<int> result = addToArrayForm(input, k);
    CHECK_EQUAL(expected.size(), result.size());
    for (int i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    input = { 1, 2, 0, 1 };
    expected = { 1, 3, 0, 0 };
    k = 99;

    result = addToArrayForm(input, k);
    CHECK_EQUAL(expected.size(), result.size());
    for (int i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    input = { 2, 1, 5};
    expected = { 1, 0, 2, 1 };
    k = 806;

    result = addToArrayForm(input, k);
    CHECK_EQUAL(expected.size(), result.size());
    for (int i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }  
}

TEST(Arrays, ArrayPairSum)
{
    std::vector<int> input = { 1,4,3,2 };
    int expected = 4;
    int result = arrayPairSum(input);
    CHECK_EQUAL(expected, result);

    input = { 6,2,6,5,1,2 };
    expected = 9;
    result = arrayPairSum(input);
    CHECK_EQUAL(expected, result);
}

TEST(Arrays, FindContentChildren)
{
    std::vector<int> g = {1, 2, 3}, s = {1, 1};
    int expected = 1;
    int content = findContentChildren(g, s);
    CHECK_EQUAL(expected, content);

    g = {1,2}, s = {1,2,3};
    expected = 2;
    content = findContentChildren(g, s);
    CHECK_EQUAL(expected, content);

    g = {10,9,8,7}, s = {5,6,7,8};
    expected = 2;
    content = findContentChildren(g, s);
    CHECK_EQUAL(expected, content);
}

TEST(Arrays, NumRookCaptures)
{
    std::vector<std::vector<char>> board = 
        {
            {'.','.','.','.','.','.','.','.'},
            {'.','.','.','p','.','.','.','.'},
            {'.','.','.','p','.','.','.','.'},
            {'p','p','.','R','.','p','B','.'},
            {'.','.','.','.','.','.','.','.'},
            {'.','.','.','B','.','.','.','.'},
            {'.','.','.','p','.','.','.','.'},
            {'.','.','.','.','.','.','.','.'}
        };
    int expected = 3;
    int result = numRookCaptures(board);
    CHECK_EQUAL(expected, result);

}

TEST(Arrays, ThirdMax)
{
    std::vector<int> nums = { 1, 2, 3 };
    int expected = 1;
    int result = 0;
    result = thirdMax(nums);
    CHECK_EQUAL(expected, result);

    nums = { 1, 2 };
    expected = 2;
    result = thirdMax(nums);
    CHECK_EQUAL(expected, result);

    nums = { 1, 2, 2, 3 };
    expected = 1;
    result = thirdMax(nums);
    CHECK_EQUAL(expected, result);

    nums = { 5, 2, 2 };
    expected = 5;
    result = thirdMax(nums);
    CHECK_EQUAL(expected, result);

    nums = {1,2,-2147483648};
    expected = -2147483648;
    result = thirdMax(nums);
    CHECK_EQUAL(expected, result);
}

TEST(Arrays, CanPlaceFlowers)
{
    std::vector<int> nums = { 1, 0, 0, 0, 1};

    int numFlowers = 1;
    bool result = canPlaceFlowers(nums, numFlowers);
    CHECK(result);

    numFlowers = 2;
    result = canPlaceFlowers(nums, numFlowers);
    CHECK(!result);

    nums = {1,0,1,0,1,0,1};
    numFlowers = 1;
    result = canPlaceFlowers(nums, numFlowers);
    CHECK(!result);   

    nums = {0,0,1,0,1};
    numFlowers = 1;
    result = canPlaceFlowers(nums, numFlowers);
    CHECK(result);   

    nums = {1,0,0,0,1,0,0};
    numFlowers = 2;
    result = canPlaceFlowers(nums, numFlowers);
    CHECK(result);   
}

TEST(Arrays, ValidMountainArray)
{
    std::vector<int> nums = { 2,1 };
    bool result = validMountainArray(nums);
    CHECK(!result);

    nums = { 3,5,5 };
    result = validMountainArray(nums);
    CHECK(!result);

    nums = { 0,3,2,1 };
    result = validMountainArray(nums);
    CHECK(result);

    nums = { 9,8,7,6,5,4,3,2,1,0 };
    result = validMountainArray(nums);
    CHECK(!result);    

    nums = {1,3,2};
    result = validMountainArray(nums);
    CHECK(result); 

    nums = {2,0,2};
    result = validMountainArray(nums);
    CHECK(!result);  

    nums = {4,4,3,2,1};
    result = validMountainArray(nums);
    CHECK(!result);

    nums = {1,1,1,1,1,1,1,2,1};
    result = validMountainArray(nums);
    CHECK(!result);
}

TEST(Arrays, HasGroupsSizeX)
{
    std::vector<int> nums = {1,2,3,4,4,3,2,1};
    bool result = hasGroupsSizeX(nums);
    CHECK(result);

    nums = {1,1,1,2,2,2,3,3};
    result = hasGroupsSizeX(nums);
    CHECK(!result);

    nums = {1};
    result = hasGroupsSizeX(nums);
    CHECK(!result);

    nums = {1,1};
    result = hasGroupsSizeX(nums);
    CHECK(result);

    nums = {1,1,2,2,2,2};
    result = hasGroupsSizeX(nums);
    CHECK(result);

    nums = {1,1,1,1,2,2,2,2,2,2};
    result = hasGroupsSizeX(nums);
    CHECK(result);
}

TEST(Arrays, Average)
{
    std::vector<int> nums = {4000,3000,1000,2000};
    CHECK_EQUAL(2500.00000, average(nums));

    nums = {1000,2000,3000};
    CHECK_EQUAL(2000.00000, average(nums));

    nums = { 6000,5000,4000,3000,2000,1000};
    CHECK_EQUAL(3500.00000, average(nums));

    nums = { 8000,9000,2000,3000,6000,1000 };
    CHECK_EQUAL(4750.00000, average(nums));
}

TEST(Arrays, CalPoints)
{
    std::vector<std::string> input = {"5","2","C","D","+"};
    int expected = 30;
    CHECK_EQUAL(expected, calPoints(input));
}


TEST(Arrays, MaxProfit)
{
    std::vector<int> input = {7,1,5,3,6,4};
    int expected = 7;
    CHECK_EQUAL(expected, maxProfit(input));

    input = {1,2,3,4,5};
    expected = 4;
    CHECK_EQUAL(expected, maxProfit(input));

    input = {7,6,4,3,1};
    expected = 0;
    CHECK_EQUAL(expected, maxProfit(input));
}

TEST(Arrays, PrefixesDivBy5)
{
    std::vector<int> input = {0, 1, 1};
    std::vector<bool> expected = {true,false,false};
    std::vector<bool> results = prefixesDivBy5(input);
    CHECK_EQUAL(expected.size(), results.size());
    for (int i = 0; i < results.size(); ++i)
    {
        CHECK_EQUAL(expected[i], results[i]);
    }

    input = {1,1,1};
    expected = {false,false,false};
    results = prefixesDivBy5(input);
    CHECK_EQUAL(expected.size(), results.size());
    for (int i = 0; i < results.size(); ++i)
    {
        CHECK_EQUAL(expected[i], results[i]);
    }

    input = {0,1,1,1,1,1};
    expected = {true,false,false,false,true,false};
    results = prefixesDivBy5(input);
    CHECK_EQUAL(expected.size(), results.size());
    for (int i = 0; i < results.size(); ++i)
    {
        CHECK_EQUAL(expected[i], results[i]);
    }

    input = {1,1,1,0,1};
    expected = {false,false,false,false,false};
    results = prefixesDivBy5(input);
    CHECK_EQUAL(expected.size(), results.size());
    for (int i = 0; i < results.size(); ++i)
    {
        CHECK_EQUAL(expected[i], results[i]);
    }
}

TEST(Arrays, Search)
{
    std::vector<int> input = {-1,0,3,5,9,12};
    CHECK_EQUAL(4, search(input, 9));

    input = {-1,0,3,5,9,12};
    CHECK_EQUAL(-1, search(input, 2));

    input = {2, 5};
    CHECK_EQUAL(0, search(input, 2));

    input = { -1, 0, 5};
    CHECK_EQUAL(1, search(input, 0));
    
    input = { -1, 0, 5};
    CHECK_EQUAL(0, search(input, -1));

    input = {-1,0,3,5,9,12};
    CHECK_EQUAL(5, search(input, 12));

    input = {2, 5};
    CHECK_EQUAL(-1, search(input, 0));
}

TEST(Arrays, CanMakeArithmeticProgression)
{
    std::vector<int> input = {3,5,1};
    CHECK(canMakeArithmeticProgression(input));

    input = {1,2,4};
    CHECK(!canMakeArithmeticProgression(input));
}

TEST(Arrays, OddCells)
{
    std::vector<std::vector<int>> indices = {{0,1},{1,1}};
    CHECK_EQUAL(6, oddCells(2, 3, indices));

    indices = {{1, 1},{0, 0}};
    CHECK_EQUAL(0, oddCells(2, 2, indices));
}

TEST(Arrays, CanFormArray)
{
    std::vector<int> arr = {85};
    std::vector<std::vector<int>> pieces = {{85}};
    CHECK(canFormArray(arr, pieces));

    arr = {15,88}, pieces = {{88},{15}};
    CHECK(canFormArray(arr, pieces));

    arr = {15,88}, pieces = {{88},{15}};
    CHECK(canFormArray(arr, pieces));

    arr = {49,18,16}, pieces = {{16,18,49}};
    CHECK(!canFormArray(arr, pieces));

    arr = {91,4,64,78}, pieces = {{78},{4,64},{91}};
    CHECK(canFormArray(arr, pieces));

    arr = {1,3,5,7}, pieces = {{2,4,6,8}};
    CHECK(!canFormArray(arr, pieces));

    arr = {15,88}, pieces = {{88},{15}};
    CHECK(canFormArray(arr, pieces));

    arr = {12}, pieces = {{1}};
    CHECK(!canFormArray(arr, pieces));
}

TEST(Arrays, KLengthApart)
{
    std::vector<int> nums = {1,0,0,0,1,0,0,1};
    int k = 2;
    CHECK(kLengthApart(nums, k));

    nums = {1,0,0,1,0,1};
    k = 2;
    CHECK(!kLengthApart(nums, k));

    nums = {1,1,1,1,1};
    k = 0;
    CHECK(kLengthApart(nums, k));

    nums = {0,1,0,1};
    k = 1;
    CHECK(kLengthApart(nums, k));
}

TEST(Arrays, CheckStraightLine)
{
    std::vector<std::vector<int>> coords = {{1,2},{2,3},{3,4},{4,5},{5,6},{6,7}};
    CHECK(checkStraightLine(coords));

    coords = {{1,1},{2,2},{3,4},{4,5},{5,6},{7,7}};
    CHECK(!checkStraightLine(coords));

    coords = {{-4,-3},{1,0},{3,-1},{0,-1},{-5,2}};
    CHECK(!checkStraightLine(coords));
}

TEST(Arrays, CheckIfExist)
{
    std::vector<int> arr = {10,2,5,3};
    CHECK(checkIfExist(arr));

    arr = {7,1,14,11};
    CHECK(checkIfExist(arr));

    arr = {3,1,7,11};
    CHECK(!checkIfExist(arr));
}

TEST(Arrays, Check)
{
    std::vector<int> arr = {3,4,5,1,2};
    CHECK(check(arr));

    arr = {2,1,3,4};
    CHECK(!check(arr));

    arr = {1,2,3};
    CHECK(check(arr));

    arr = {1,1,1};
    CHECK(check(arr));

    arr = {2,1};
    CHECK(check(arr));

    arr = {1, 3, 2};
    CHECK(!check(arr));
}

TEST(Arrays, ConstructRectangle)
{
    std::vector<int> expected = { 37, 1 };
    std::vector<int> result = constructRectangle(37);
    CHECK_EQUAL(expected.size(), result.size());
    for (int i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    expected = { 427, 286 };
    result = constructRectangle(122122);
    CHECK_EQUAL(expected.size(), result.size());
    for (int i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    expected = { 2, 2 };
    result = constructRectangle(4);
    CHECK_EQUAL(expected.size(), result.size());
    for (int i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }
}

TEST(Arrays, ContainsNearbyDuplicate)
{
    std::vector<int> input = { 1,2,3,1 };
    CHECK(containsNearbyDuplicate(input, 3));

    input = { 1,0,1,1 };
    CHECK(containsNearbyDuplicate(input, 1));

    input = {1,2,3,1,2,3};
    CHECK(!containsNearbyDuplicate(input, 2));

    input = { 99, 99 };
    CHECK(containsNearbyDuplicate(input, 2));

    input = { 1 };
    CHECK(!containsNearbyDuplicate(input, 1));
    
    input = { 1,2,3,4,5,6,7,8,9,9 };
    CHECK(containsNearbyDuplicate(input, 3));
}

TEST(Arrays, CountMatches)
{
    std::vector<std::vector<std::string>> input = {{"phone","blue","pixel"},{"computer","silver","lenovo"},{"phone","gold","iphone"}};

    CHECK_EQUAL(1, countMatches(input, "color", "silver"));

    input = {{"phone","blue","pixel"},{"computer","silver","phone"},{"phone","gold","iphone"}};
    CHECK_EQUAL(2, countMatches(input, "type", "phone"));
}

TEST(Arrays, CountNegatives)
{
    std::vector<std::vector<int>> input = {{4,3,2,-1},{3,2,1,-1},{1,1,-1,-2},{-1,-1,-2,-3}};
    CHECK_EQUAL(8, countNegatives(input));

    input = {{3,2},{1,0}};
    CHECK_EQUAL(0, countNegatives(input));

    input = {{1,-1},{-1,-1}};
    CHECK_EQUAL(3, countNegatives(input));

    input = {{5,1,0},{-5,-5,-5}};
    CHECK_EQUAL(3, countNegatives(input));
}

TEST(Arrays, CreateTargetArray)
{
    std::vector<int> nums = {0,1,2,3,4};
    std::vector<int> indices = {0,1,2,2,1};
    std::vector<int> result = createTargetArray(nums, indices);
    std::vector<int> expected = {0,4,1,3,2};
    CHECK_EQUAL(expected.size(), result.size());

    for (int i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    nums = {1,2,3,4,0};
    indices = {0,1,2,3,0};
    result = createTargetArray(nums, indices);
    expected = {0,1,2,3,4};
    CHECK_EQUAL(expected.size(), result.size());

    for (int i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    nums = {1};
    indices = {0};
    result = createTargetArray(nums, indices);
    expected = {1};
    CHECK_EQUAL(expected.size(), result.size());

    for (int i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }
}

TEST(Arrays, MinOperations)
{
    std::vector<std::string> logs = {"d1/","d2/","../","d21/","./"};
    CHECK_EQUAL(2, minOperations(logs));

    logs = {"d1/","d2/","./","d3/","../","d31/"};
    CHECK_EQUAL(3, minOperations(logs));

    logs = {"d1/","../","../","../"};
    CHECK_EQUAL(0, minOperations(logs));    

    logs = {"1/"};
    CHECK_EQUAL(1, minOperations(logs));   
}

TEST(Arrays, DiStringMatch)
{
    std::vector<int> expected = { 0, 4, 1, 3, 2};
    std::vector<int> result = diStringMatch("IDID");
    CHECK_EQUAL(expected.size(), result.size());
    for (int i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    expected = { 0, 1, 2, 3 };
    result = diStringMatch("III");
    CHECK_EQUAL(expected.size(), result.size());
    for (int i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    expected = { 3,2,0,1 };
    result = diStringMatch("DDI");
    CHECK_EQUAL(expected.size(), result.size());
    for (int i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }
}

TEST(Arrays, Decode)
{
    std::vector<int> expected = { 1,0,2,1 };
    std::vector<int> input = {1,2,3};
    std::vector<int> result = decode(input, 1);
    CHECK_EQUAL(expected.size(), result.size());
    for (int i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    expected = { 4, 2, 0, 7, 4 };
    input = {6,2,7,3};
    result = decode(input, 4);
    CHECK_EQUAL(expected.size(), result.size());
    for (int i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }
}

TEST(Arrays, DecompressRLElist)
{
    std::vector<int> expected = { 2, 4, 4, 4};
    std::vector<int> input = {1,2,3,4};
    std::vector<int> result = decompressRLElist(input);
    CHECK_EQUAL(expected.size(), result.size());
    for (int i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    expected = {1,3,3};
    input = { 1,1,2,3 };
    result = decompressRLElist(input);
    CHECK_EQUAL(expected.size(), result.size());
    for (int i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }
}

TEST(Arrays, DestCity)
{
    std::vector<std::vector<std::string>> paths = {{"London","New York"},{"New York","Lima"},{"Lima","Sao Paulo"}};
    CHECK_EQUAL("Sao Paulo", destCity(paths));

    paths = {{"B","C"},{"D","B"},{"C","A"}};
    CHECK_EQUAL("A", destCity(paths));

    paths = {{"A","Z"}};
    CHECK_EQUAL("Z", destCity(paths));
}

TEST(Arrays, CountGoodTriplets)
{
    std::vector<int> arr = {3,0,1,1,9,7};
    CHECK_EQUAL(4, countGoodTriplets(arr, 7, 2, 3));

    arr = {1,1,2,2,3};
    CHECK_EQUAL(0, countGoodTriplets(arr, 0, 0, 1));

    arr = {7,3,7,3,12,1,12,2,3};
    CHECK_EQUAL(12, countGoodTriplets(arr, 5, 8, 1));
}

TEST(Arrays, Decrypt)
{
    std::vector<int> expected = {12,10,16,13};
    std::vector<int> arr = {5,7,1,4};
    std::vector<int> result = decrypt(arr, 3);
    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    expected = {0,0,0,0};
    arr = {1,2,3,4};
    result = decrypt(arr, 0);
    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    expected = {12,5,6,13};
    arr = {2,4,9,3};
    result = decrypt(arr, -2);
    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }
}

TEST(Arrays, FindShortestSubArray)
{
    std::vector<int> arr = {1,2,2,3,1};
    CHECK_EQUAL(2, findShortestSubArray(arr));

    arr = {1,2,2,3,1,4,2};
    CHECK_EQUAL(6, findShortestSubArray(arr));

    arr = {1,2,2,1,2,1,1,1,1,2,2,2};
    CHECK_EQUAL(9, findShortestSubArray(arr));
}

TEST(Arrays, MinDeletionSize)
{
    std::vector<std::string> arr = { "cba","daf","ghi" };
    CHECK_EQUAL(1, minDeletionSize(arr));

    arr = { "a","b" };
    CHECK_EQUAL(0, minDeletionSize(arr));

    arr = { "zyx","wvu","tsr" };
    CHECK_EQUAL(3, minDeletionSize(arr));
}

TEST(Arrays, ContainsPattern)
{
    std::vector<int> arr = {1,2,4,4,4,4};
    CHECK(containsPattern(arr, 1, 3));

    arr = {1,2,1,2,1,1,1,3};
    CHECK(containsPattern(arr, 2, 2));

    arr = {1,2,1,2,1,3};
    CHECK(!containsPattern(arr, 2, 3));

    arr = {1,2,3,1,2};
    CHECK(!containsPattern(arr, 2, 2));

    arr = { 2,2,2,2 };
    CHECK(!containsPattern(arr, 2, 3));  
}

TEST(Arrays, FinalPrices)
{
    std::vector<int> arr = { 8,4,6,2,3 };
    std::vector<int> expected = { 4,2,4,2,3 };
    std::vector<int> result = finalPrices(arr);
    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    arr = {1,2,3,4,5};
    expected = {1,2,3,4,5};
    result = finalPrices(arr);
    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    arr = {10,1,1,6};
    expected = {9,0,1,6};
    result = finalPrices(arr);
    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }
}

TEST(Arrays, DistributeCandies)
{
    std::vector<int> arr = { 1,1,2,2,3,3 };
    CHECK_EQUAL(3, distributeCandies(arr));

    arr = { 1,1,2,3 };
    CHECK_EQUAL(2, distributeCandies(arr));    

    arr = { 6,6,6,6 };
    CHECK_EQUAL(1, distributeCandies(arr));    
}

TEST(Arrays, DistributeCandies2)
{
    std::vector<int> expected = { 1,2,3,1 };
    std::vector<int> result = distributeCandies(7, 4);
    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    } 

    expected = { 5,2,3 };
    result = distributeCandies(10, 3);
    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }   
}

TEST(Arrays, DistanceBetweenBusStops)
{
    std::vector<int> distance = {1,2,3,4};
    int start = 0, destination = 1;
    CHECK_EQUAL(1, distanceBetweenBusStops(distance, start, destination));

    distance = {1,2,3,4};
    start = 0, destination = 2;
    CHECK_EQUAL(3, distanceBetweenBusStops(distance, start, destination));

    distance = {1,2,3,4};
    start = 0, destination = 3;
    CHECK_EQUAL(4, distanceBetweenBusStops(distance, start, destination));

    distance = {7,6,3,0,3};
    start = 0, destination = 4;
    CHECK_EQUAL(3, distanceBetweenBusStops(distance, start, destination));

    distance = {8,11,6,7,10,11,2};
    start = 0, destination = 3;
    CHECK_EQUAL(25, distanceBetweenBusStops(distance, start, destination));
}

TEST(Arrays, DuplicateZeros)
{
    std::vector<int> arr = {1,0,2,3,0,4,5,0};
    std::vector<int> expected = {1,0,0,2,3,0,0,4};
    duplicateZeros(arr);
    for (size_t i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], arr[i]);
    }
}

TEST(Arrays, SumZero)
{
    std::vector<int> result = sumZero(5);
    CHECK_EQUAL(5, result.size());
    CHECK_EQUAL(0, std::accumulate(result.begin(), result.end(), 0));

    result = sumZero(3);
    CHECK_EQUAL(3, result.size());
    CHECK_EQUAL(0, std::accumulate(result.begin(), result.end(), 0));

    result = sumZero(1);
    CHECK_EQUAL(1, result.size());
    CHECK_EQUAL(0, std::accumulate(result.begin(), result.end(), 0));
}

TEST(Arrays, GetImportance)
{
    std::vector<Employee*> employees;
    Employee* e1 = new Employee();
    e1->id = 1;
    e1->importance = 5;
    Employee* e2 = new Employee();
    e2->id = 2;
    e2->importance = 3;
    Employee* e3 = new Employee();
    e3->id = 3;
    e3->importance = 3;
    e1->subordinates.push_back(2);
    e1->subordinates.push_back(3);
    employees.push_back(e1);
    employees.push_back(e2);
    employees.push_back(e3);

    CHECK_EQUAL(11, getImportance(employees, 1));

    delete e1;
    delete e2;
    delete e3;
}

TEST(Arrays, FindSpecialInteger)
{
    std::vector<int> arr = { 1,2,2,6,6,6,6,7,10 };
    CHECK_EQUAL(6, findSpecialInteger(arr));

    arr = {1};
    CHECK_EQUAL(1, findSpecialInteger(arr));

    arr = {1,1,2,2,3,3,3,3};
    CHECK_EQUAL(3, findSpecialInteger(arr));
}

TEST(Arrays, FairCandySwap)
{
    std::vector<int> bobsBars = {2,2};
    std::vector<int> alicesBars =  {1,1};
    std::vector<int> expected = {1, 2};
    std::vector<int> result = fairCandySwap(alicesBars, bobsBars);
    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    bobsBars = {2, 3};
    alicesBars =  {1,2};
    expected = {1, 2};
    result = fairCandySwap(alicesBars, bobsBars);
    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    bobsBars = {1, 3};
    alicesBars =  {2};
    expected = {2, 3};
    result = fairCandySwap(alicesBars, bobsBars);
    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    bobsBars = {2, 4};
    alicesBars =  {1,2,5};
    expected = {5, 4};
    result = fairCandySwap(alicesBars, bobsBars);
    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }  
}

TEST(Arrays, FindLucky)
{
    std::vector<int> arr = { 2,2,3,4 };
    CHECK_EQUAL(2, findLucky(arr));

    arr = { 1,2,2,3,3,3 };
    CHECK_EQUAL(3, findLucky(arr));

    arr = { 2,2,2,3,3 };
    CHECK_EQUAL(-1, findLucky(arr));

    arr = { 5 };
    CHECK_EQUAL(-1, findLucky(arr));

    arr = { 7,7,7,7,7,7,7 };
    CHECK_EQUAL(7, findLucky(arr));
}

TEST(Arrays, FindDisappearedNumbers)
{
    std::vector<int> arr = { 4,3,2,7,8,2,3,1 };
    std::vector<int> expected = { 5,6 };
    std::vector<int> result = findDisappearedNumbers(arr);

    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    arr = { 1, 1 };
    expected = { 2 };
    result = findDisappearedNumbers(arr);

    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    arr = { 1,1,2,2 };
    expected = { 3, 4 };
    result = findDisappearedNumbers(arr);

    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    arr = { 2, 2 };
    expected = { 1 };
    result = findDisappearedNumbers(arr);

    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }
}

TEST(Arrays, FindNumbers)
{
    std::vector<int> arr = { 12,345,2,6,7896 };
    CHECK_EQUAL(2, findNumbers(arr));

    arr = { 555,901,482,1771 };
    CHECK_EQUAL(1, findNumbers(arr)); 
}

TEST(Arrays, NearestValidPoint)
{
    std::vector<std::vector<int>> arr = {{1,2},{3,1},{2,4},{2,3},{4,4}};
    CHECK_EQUAL(2, nearestValidPoint(3, 4, arr)); 

    arr = {{3,4}};
    CHECK_EQUAL(0, nearestValidPoint(3, 4, arr)); 

    arr = {{2,3}};
    CHECK_EQUAL(-1, nearestValidPoint(3, 4, arr)); 

    arr = {{1,2},{3,3},{3,3}};
    CHECK_EQUAL(0, nearestValidPoint(1, 1, arr)); 
}

TEST(Arrays, MaxAltitude)
{
    std::vector<int> alts = {-5,1,5,0,-7};
    CHECK_EQUAL(1, largestAltitude(alts)); 

    alts = {-4,-3,-2,-1,4,3,2};
    CHECK_EQUAL(0, largestAltitude(alts)); 
}

TEST(Arrays, FlipAndInvertImage)
{
    std::vector<std::vector<int>> image =  {{1,1,0},{1,0,1},{0,0,0}};
    std::vector<std::vector<int>> expected = {{1,0,0},{0,1,0},{1,1,1}};
    auto result = flipAndInvertImage(image);
    for (size_t i = 0; i < image.size(); ++i)
    {
        for (size_t j = 0; j < image[i].size(); ++j)
        {
            CHECK_EQUAL(expected[i][j], result[i][j]);
        }
    }

    image = {{1,1,0,0},{1,0,0,1},{0,1,1,1},{1,0,1,0}};
    expected = {{1,1,0,0},{0,1,1,0},{0,0,0,1},{1,0,1,0}};
    result = flipAndInvertImage(image);
    for (size_t i = 0; i < image.size(); ++i)
    {
        for (size_t j = 0; j < image[i].size(); ++j)
        {
            CHECK_EQUAL(expected[i][j], result[i][j]);
        }
    }
}

TEST(Arrays, NextGreatestLetter)
{
    std::vector<char> arr =  {'c', 'f', 'j'};
    CHECK_EQUAL('c', nextGreatestLetter(arr, 'a'));

    arr = {'c', 'f', 'j'};
    CHECK_EQUAL('f', nextGreatestLetter(arr, 'c'));

    arr = {'c', 'f', 'j'};
    CHECK_EQUAL('f', nextGreatestLetter(arr, 'd'));

    arr = {'c', 'f', 'j'};
    CHECK_EQUAL('j', nextGreatestLetter(arr, 'g'));

    arr = {'c', 'f', 'j'};
    CHECK_EQUAL('c', nextGreatestLetter(arr, 'j'));

    arr = {'c', 'f', 'j'};
    CHECK_EQUAL('c', nextGreatestLetter(arr, 'k'));
}

TEST(Arrays, FindTheDistanceValue)
{
    std::vector<int> arr1 = { 4,5,8 };
    std::vector<int> arr2 = { 10,9,1,8 };
    CHECK_EQUAL(2, findTheDistanceValue(arr1, arr2, 2));

    arr1 = { 1,4,2,3};
    arr2 = { -4,-3,6,10,20,30 };
    CHECK_EQUAL(2, findTheDistanceValue(arr1, arr2, 3));

    arr1 = { 2,1,100,3 };
    arr2 = { -5,-2,10,-3,7 };
    CHECK_EQUAL(1, findTheDistanceValue(arr1, arr2, 6));
}

TEST(Arrays, FindJudge)
{
    std::vector<std::vector<int>> trust = {{1,2}};
    CHECK_EQUAL(2, findJudge(2, trust));

    trust = {{1,3},{2,3}};
    CHECK_EQUAL(3, findJudge(3, trust));

    trust = {{1,3},{2,3},{3,1}};
    CHECK_EQUAL(-1, findJudge(3, trust));

    trust = {{1,2},{2,3}};
    CHECK_EQUAL(-1, findJudge(3, trust));

    trust = {{1,3},{1,4},{2,3},{2,4},{4,3}};
    CHECK_EQUAL(3, findJudge(4, trust));
}

TEST(Arrays, FindCenter)
{
    std::vector<std::vector<int>> edges = {{1,2},{2,3},{4,2}};
    CHECK_EQUAL(2, findCenter(edges));

    edges = {{1,2},{5,1},{1,3},{1,4}};
    CHECK_EQUAL(1, findCenter(edges));
}

TEST(Arrays, MaximumWealth)
{
    std::vector<std::vector<int>> accounts = {{1,2,3},{3,2,1}};
    CHECK_EQUAL(6, maximumWealth(accounts));

    accounts = {{1,5},{7,3},{3,5}};
    CHECK_EQUAL(10, maximumWealth(accounts));

    accounts = {{2,8,7},{7,1,3},{1,9,5}};
    CHECK_EQUAL(17, maximumWealth(accounts));
}

TEST(Arrays, KidsWithCandies)
{
    std::vector<int> candies = {2,3,5,1,3};
    std::vector<bool> result = kidsWithCandies(candies, 3);
    std::vector<bool> expected = {true,true,true,false,true};

    for (size_t i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    candies = {4,2,1,1,2};
    result = kidsWithCandies(candies, 1);
    expected = {true,false,false,false,false};

    for (size_t i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    candies = {12,1,12};
    result = kidsWithCandies(candies, 10);
    expected = {true,false,true};

    for (size_t i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }
}

TEST(Arrays, MinOperations2)
{
    std::vector<int> expected = { 1,1,3 };
    std::string boxes = "110";
    std::vector<int> result = minOperations(boxes);
    for (size_t i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    expected = { 11,8,5,4,3,4 };
    boxes = "001011";
    result = minOperations(boxes);
    for (size_t i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }
}

TEST(Arrays, SmallerNumbersThanCurrent)
{
    std::vector<int> expected = { 4,0,1,1,3 };
    std::vector<int> nums = { 8,1,2,2,3 };
    std::vector<int> result = smallerNumbersThanCurrent(nums);
    for (int i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    expected = { 2,1,0,3 };
    nums = { 6,5,4,8 };
    result = smallerNumbersThanCurrent(nums);
    for (int i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    expected = { 0, 0, 0, 0};
    nums = { 7,7,7,7 };
    result = smallerNumbersThanCurrent(nums);
    for (int i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }
}

TEST(Arrays, HeightChecker)
{
    std::vector<int> heights = { 1,1,4,2,1,3 };
    CHECK_EQUAL(3, heightChecker(heights));

    heights = { 5,1,2,3,4 };
    CHECK_EQUAL(5, heightChecker(heights));

    heights = { 1,2,3,4,5 };
    CHECK_EQUAL(0, heightChecker(heights));

    heights = { 2,1,2,1,1,2,2,1 };
    CHECK_EQUAL(4, heightChecker(heights));
}

TEST(Arrays, GetMaximumGenerated)
{
    CHECK_EQUAL(3, getMaximumGenerated(7));
    CHECK_EQUAL(1, getMaximumGenerated(2));
    CHECK_EQUAL(2, getMaximumGenerated(3));
    CHECK_EQUAL(1, getMaximumGenerated(1));
}

TEST(Arrays, FloodFill)
{
    std::vector<std::vector<int>> expected =
     {{2,2,2},{2,2,0},{2,0,1}};
    std::vector<std::vector<int>> image =
     {{1,1,1},{1,1,0},{1,0,1}};
    auto result = floodFill(image, 1, 1, 2);
    for (size_t i = 0; i < expected.size(); ++i)
    {
        for (size_t j = 0; j < expected[i].size(); ++j)
        {
            CHECK_EQUAL(expected[i][j], result[i][j]);
        }
    }

    expected = {{0,0,0},{0,1,1}};
    image = {{0,0,0},{0,1,1}};
    result = floodFill(image, 1, 1, 1);
    for (size_t i = 0; i < expected.size(); ++i)
    {
        for (size_t j = 0; j < expected[i].size(); ++j)
        {
            CHECK_EQUAL(expected[i][j], result[i][j]);
        }
    }
}

TEST(Arrays, ImageSmoother)
{
    std::vector<std::vector<int>> expected =
        {{0,0,0},
        {0,0,0},
        {0,0,0}};

    std::vector<std::vector<int>> image =
        {{1,1,1},
        {1,0,1},
        {1,1,1}};

    auto result = imageSmoother(image);
    for (size_t i = 0; i < expected.size(); ++i)
    {
        for (size_t j = 0; j < expected[i].size(); ++j)
        {
            CHECK_EQUAL(expected[i][j], result[i][j]);
        }
    }

    expected =
        {{255, 255, 255},
        {255, 255, 255},
        {255, 255, 255}};

    image =
        {{255, 255, 255},
        {255, 255, 255},
        {255, 255, 255}};

    result = imageSmoother(image);
    for (size_t i = 0; i < expected.size(); ++i)
    {
        for (size_t j = 0; j < expected[i].size(); ++j)
        {
            CHECK_EQUAL(expected[i][j], result[i][j]);
        }
    }
} 

TEST(Arrays, MajorityElement)
{
    std::vector<int> nums = {3,2,3};
    CHECK_EQUAL(3, majorityElement(nums));

    nums = {2,2,1,1,1,2,2};
    CHECK_EQUAL(2, majorityElement(nums));
}

TEST(Arrays, AllCellsDistOrder)
{
    std::vector<std::vector<int>> expected = 
        {{0,0},{0,1}};
    auto result = allCellsDistOrder(1, 2, 0, 0);
    for (size_t i = 0; i < expected.size(); ++i)
    {
        for (auto j = 0; j < expected[i].size(); ++j)
        {
            CHECK_EQUAL(expected[i][j], result[i][j]);
        }
    }

    expected = {{2,3},{1,3},{2,2},{2,4},{0,3},{1,2},{1,4},{2,1},{0,2},{0,4},{1,1},{2,0},{0,1},{1,0},{0,0}};
    result = allCellsDistOrder(3, 5, 2, 3);
    for (size_t i = 0; i < expected.size(); ++i)
    {
        for (auto j = 0; j < expected[i].size(); ++j)
        {
            CHECK_EQUAL(expected[i][j], result[i][j]);
        }
    }
}

TEST(Arrays, CountGoodRectangles)
{
    std::vector<std::vector<int>> rectangles = 
        {{5,8},{3,9},{5,12},{16,5}};
    CHECK_EQUAL(3, countGoodRectangles(rectangles));
    rectangles = {{2,3},{3,7},{4,3},{3,7}};
    CHECK_EQUAL(3, countGoodRectangles(rectangles));
}

TEST(Arrays, DiagonalSum)
{
    std::vector<std::vector<int>> mat =
        {{1,2,3},
        {4,5,6},
        {7,8,9}};
    CHECK_EQUAL(25, diagonalSum(mat));

    mat =
        {{1,1,1,1},
        {1,1,1,1},
        {1,1,1,1},
        {1,1,1,1}};
    CHECK_EQUAL(8, diagonalSum(mat));


    mat =
        {{5}};

    CHECK_EQUAL(5, diagonalSum(mat));
}

TEST(Arrays, SelfDividingNumbers)
{
    std::vector<int> expected =
        {
            1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 15, 22
        };
    std::vector<int> nums = selfDividingNumbers(1, 22);
    CHECK_EQUAL(expected.size(), nums.size());
    for(int i = 0; i < nums.size(); ++i)
    {
        CHECK_EQUAL(expected[i], nums[i]);
    }
}

TEST(Arrays, ArraySign)
{
    std::vector<int> nums = {-1,-2,-3,-4,3,2,1};
    CHECK_EQUAL(1, arraySign(nums));

    nums = {1,5,0,2,-3};
    CHECK_EQUAL(0, arraySign(nums));

    nums = {-1,1,-1,1,-1};
    CHECK_EQUAL(-1, arraySign(nums));

    nums = {9,72,34,29,-49,-22,-77,-17,-66,-75,-44,-30,-24};
    CHECK_EQUAL(-1, arraySign(nums));
}

TEST(Arrays, SumOfUnique)
{
    std::vector<int> arr = { 1,2,3,2 };
    CHECK_EQUAL(4, sumOfUnique(arr));

    arr = {1,1,1,1,1};
    CHECK_EQUAL(0, sumOfUnique(arr));

    arr = {1,2,3,4,5};
    CHECK_EQUAL(15, sumOfUnique(arr));
}

TEST(Arrays, MaxProduct)
{
    std::vector<int> arr = { 3, 4, 5, 2 };
    CHECK_EQUAL(12, maxProduct(arr));

    arr = { 1,5,4,5 };
    CHECK_EQUAL(16, maxProduct(arr));

    arr = { 3, 7 };
    CHECK_EQUAL(12, maxProduct(arr));
}

TEST(Arrays, BusyStudent)
{
    std::vector<int> startTimes = { 1,2,3 };
    std::vector<int> endTimes = { 3,2,7 };
    CHECK_EQUAL(1, busyStudent(startTimes,endTimes,4));

    startTimes = { 4 };
    endTimes = { 4 };
    CHECK_EQUAL(1, busyStudent(startTimes,endTimes,4));

    startTimes = { 4 };
    endTimes = { 4 };
    CHECK_EQUAL(0, busyStudent(startTimes,endTimes,5));

    startTimes = { 1,1,1,1 };
    endTimes = { 1,3,2,4 };
    CHECK_EQUAL(0, busyStudent(startTimes,endTimes,7));

    startTimes = { 9,8,7,6,5,4,3,2,1 };
    endTimes = { 10,10,10,10,10,10,10,10,10 };
    CHECK_EQUAL(5, busyStudent(startTimes,endTimes,5));
}

TEST(Arrays, MatrixReshape)
{
    std::vector<std::vector<int>> mat = { {1,2},{3,4} };
    std::vector<std::vector<int>> exp = {{ 1, 2, 3, 4 }};
    int r = 1;
    int c = 4;
    auto result = matrixReshape(mat, r, c);
    CHECK_EQUAL(exp.size(), result.size());
    CHECK_EQUAL(exp[0].size(), result[0].size());
    for (size_t i = 0; i < r; ++i)
    {
        for (size_t j = 0; j < c; ++j)
        {
            CHECK_EQUAL(exp[i][j], result[i][j]);
        }
    }

    mat = { {1,2},{3,4} };
    exp = { {1,2},{3,4} };
    r = 2;
    c = 4;
    result = matrixReshape(mat, r, c);
    CHECK_EQUAL(exp.size(), result.size());
    CHECK_EQUAL(exp[0].size(), result[0].size());
    for (size_t i = 0; i < exp.size(); ++i)
    {
        for (size_t j = 0; j < exp[0].size(); ++j)
        {
            CHECK_EQUAL(exp[i][j], result[i][j]);
        }
    }
}

TEST(Arrays, SmallestRangeI)
{
    std::vector<int> nums = { 1 };
    CHECK_EQUAL(0, smallestRangeI(nums,0));

    nums = { 0,10 };
    CHECK_EQUAL(6, smallestRangeI(nums,2));

    nums = { 1,3,6 };
    CHECK_EQUAL(0, smallestRangeI(nums,3));
}

TEST(Arrays, IsToeplitzMatrix)
{
    std::vector<std::vector<int>> mat = {{1,2,3,4},{5,1,2,3},{9,5,1,2}};
    CHECK(isToeplitzMatrix(mat));

    mat = {{1,2},{2,2}};
    CHECK(!isToeplitzMatrix(mat));

    mat = {{18},{66}};
    CHECK(isToeplitzMatrix(mat));

    mat = {{11,74,0,93},{40,11,74,7}};
    CHECK(!isToeplitzMatrix(mat));

    mat = {
        {36,59,71,15,26,82,87},
        {56,36,59,71,15,26,82},
        {15,0,36,59,71,15,26}
    };
    CHECK(!isToeplitzMatrix(mat));
}

TEST(Arrays, NumMovesStones)
{
    std::vector<int> expected = { 1, 2 };
    auto result = numMovesStones(1, 2, 5);
    CHECK_EQUAL(expected[0], result[0]);
    CHECK_EQUAL(expected[1], result[1]);

    expected = { 0, 0 };
    result = numMovesStones(4, 3, 2);
    CHECK_EQUAL(expected[0], result[0]);
    CHECK_EQUAL(expected[1], result[1]);

    // expected = { 1, 2 };
    // result = numMovesStones(3, 5, 1);
    // CHECK_EQUAL(expected[0], result[0]);
    // CHECK_EQUAL(expected[1], result[1]);
}

TEST(Arrays, SummaryRanges)
{
    std::vector<std::string> expected = 
    {
        "0->2",
        "4->5",
        "7"
    };
    std::vector<int> input = { 0, 1, 2, 4, 5, 7 };
    std::vector<std::string> result = summaryRanges(input);
    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    expected = 
    {
        "0",
        "2->4",
        "6",
        "8->9"
    };
    input = { 0,2,3,4,6,8,9 };
    result = summaryRanges(input);
    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    expected = 
    {
    };
    input = {};
    result = summaryRanges(input);
    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }
}

TEST(Arrays, SortedSquares)
{
    std::vector<int> expected = { 0,1,9,16,100 };
    std::vector<int> nums = {-4,-1,0,3,10 };
    std::vector<int> result = sortedSquares(nums);
    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    expected = { 4,9,9,49,121 };
    nums = {-7,-3,2,3,11};
    result = sortedSquares(nums);
    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }
}

TEST(Arrays, UniqueOccurrences)
{
    std::vector<int> nums = {1,2,2,1,1,3};
    CHECK(uniqueOccurrences(nums));

    nums = {1,2};
    CHECK(!uniqueOccurrences(nums));

    nums = { -3,0,1,-3,1,1,1,-3,10,0 };
    CHECK(uniqueOccurrences(nums));
}

TEST(Arrays, NextGreaterElement)
{
    std::vector<int> nums1 = {4,1,2};
    std::vector<int> nums2 = {1,3,4,2};
    std::vector<int> result = nextGreaterElement(nums1, nums2);
    std::vector<int> expected = {-1,3,-1};
    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    nums1 = {2,4};
    nums2 = {1,2,3,4};
    result = nextGreaterElement(nums1, nums2);
    expected = {3,-1};
    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }
}

TEST(Arrays, MinStartValue)
{
    std::vector<int> nums = {-3,2,-3,4,2};
    CHECK_EQUAL(5, minStartValue(nums));

    nums = {1, 2};
    CHECK_EQUAL(1, minStartValue(nums));

    nums = {1,-2,-3};
    CHECK_EQUAL(5, minStartValue(nums));
}

TEST(Arrays, SortByBits)
{
    std::vector<int> nums = {0,1,2,3,4,5,6,7,8};
    std::vector<int> expected = { 0,1,2,4,8,3,5,6,7 };
    std::vector<int> result = sortByBits(nums);
    for (int i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    nums = { 1024,512,256,128,64,32,16,8,4,2,1 };
    expected = { 1,2,4,8,16,32,64,128,256,512,1024 };
    result = sortByBits(nums);
    for (int i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    nums = { 1000, 1000 };
    expected = { 1000, 1000 };
    result = sortByBits(nums);
    for (int i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    nums = { 2,3,5,7,11,13,17,19 };
    expected = { 2,3,5,17,7,11,13,19 };
    result = sortByBits(nums);
    for (int i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    nums = { 10,100,1000,10000 };
    expected = { 10,100,10000,1000 };
    result = sortByBits(nums);
    for (int i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }
}

TEST(Arrays, ReplaceElements)
{
    std::vector<int> nums = {17,18,5,4,6,1};
    std::vector<int> expected = { 18,6,6,6,1,-1 };
    std::vector<int> results = replaceElements(nums);
    for (int i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], results[i]);
    }

    nums = {400};
    expected = { -1 };
    results = replaceElements(nums);
    for (int i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], results[i]);
    }
}

TEST(Arrays, LuckyNumbers)
{
    std::vector<std::vector<int>> nums = {{3,7,8},{9,11,13},{15,16,17}};
    std::vector<int> expected = { 15 };
    std::vector<int> results = luckyNumbers(nums);
    CHECK_EQUAL(expected.size(), results.size());
    for (int i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], results[i]);
    }

    nums = {{1,10,4,2},{9,3,8,7},{15,16,17,12}};
    expected = { 12 };
    results = luckyNumbers(nums);
    CHECK_EQUAL(expected.size(), results.size());
    for (int i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], results[i]);
    }

    nums = {{7,8},{1,2}};
    expected = { 7 };
    results = luckyNumbers(nums);
    CHECK_EQUAL(expected.size(), results.size());
    for (int i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], results[i]);
    }
}

TEST(Arrays, MinimumAbsDifference)
{
    std::vector<int> arr = {4,2,1,3};
    std::vector<std::vector<int>> expected = {{1,2},{2,3},{3,4}};
    std::vector<std::vector<int>> results = minimumAbsDifference(arr);
    CHECK_EQUAL(expected.size(), results.size());
    for (int i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i].size(), results[i].size());
        for (int j = 0; j < expected[i].size(); ++j)
        {
            CHECK_EQUAL(expected[i][j], results[i][j]);
        }
    }
}

TEST(Arrays, FrequencySort)
{
    std::vector<int> arr = {1,1,2,2,2,3};
    std::vector<int> expected = { 3,1,1,2,2,2 };
    std::vector<int> result = frequencySort(arr);
    for (size_t i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    arr = {2,3,1,3,2};
    expected = { 1,3,3,2,2 };
    result = frequencySort(arr);
    for (size_t i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    arr = {-1,1,-6,4,5,-6,1,4,1};
    expected = { 5,-1,4,4,-6,-6,1,1,1 };
    result = frequencySort(arr);
    for (size_t i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }
}

TEST(Arrays, RepeatedNTimes)
{
    std::vector<int> arr = {1,2,3,3};
    CHECK_EQUAL(3, repeatedNTimes(arr));

    arr = {1,2,3,32,1,2,5,3,2};
    CHECK_EQUAL(2, repeatedNTimes(arr));

    arr = {5,1,5,2,5,3,5,4};
    CHECK_EQUAL(5, repeatedNTimes(arr));
    
    arr = {9,5,3,3};
    CHECK_EQUAL(3, repeatedNTimes(arr));
}

TEST(Arrays, CountBalls)
{
    CHECK_EQUAL(2, countBalls(1, 10));
    CHECK_EQUAL(2, countBalls(5, 15));
    CHECK_EQUAL(2, countBalls(10, 20));
}

TEST(Arrays, GetMinDistance)
{
    std::vector<int> nums = { 1,2,3,4,5 };
    CHECK_EQUAL(1, getMinDistance(nums, 5, 3));

    nums = { 1 };
    CHECK_EQUAL(0, getMinDistance(nums, 1, 0));

    nums = { 1,1,1,1,1,1,1,1,1,1 };
    CHECK_EQUAL(0, getMinDistance(nums, 1, 0));
}

TEST(Arrays, Transpose)
{
    std::vector<std::vector<int>> matrix =
        {
            {1,2,3},
            {4,5,6},
            {7,8,9}
        };
    std::vector<std::vector<int>> result = transpose(matrix);
    std::vector<std::vector<int>> expected =
        {
            {1,4,7},
            {2,5,8},
            {3,6,9}
        };
    for (size_t i = 0; i < expected.size(); ++i)
    {
        for (size_t j = 0; j < expected[i].size(); ++j)
        {
            CHECK_EQUAL(expected[i][j], result[i][j]);
        }
    }

    matrix =
        {
            {1,2,3},
            {4,5,6}
        };

    result = transpose(matrix);
    expected =
        {
            {1,4},
            {2,5},
            {3,6}
        };
    for (size_t i = 0; i < expected.size(); ++i)
    {
        for (size_t j = 0; j < expected[i].size(); ++j)
        {
            CHECK_EQUAL(expected[i][j], result[i][j]);
        }
    }
}

TEST(Arrays, IsAlienSorted)
{
    std::vector<std::string> words = { "hello","leetcode" };
    CHECK(isAlienSorted(words, "hlabcdefgijkmnopqrstuvwxyz"));

    words = { "word","world","row" };
    CHECK(!isAlienSorted(words, "worldabcefghijkmnpqstuvxyz"));

    words = { "apple","app" };
    CHECK(!isAlienSorted(words, "abcdefghijklmnopqrstuvwxyz"));
}

TEST(Arrays, LastStoneWeight)
{
    std::vector<int> stones = { 2,7,4,1,8,1 };
    CHECK_EQUAL(1, lastStoneWeight(stones));

    stones = { 1, 3};
    CHECK_EQUAL(2, lastStoneWeight(stones));

    stones = { 3,7,2 };
    CHECK_EQUAL(2, lastStoneWeight(stones));
}