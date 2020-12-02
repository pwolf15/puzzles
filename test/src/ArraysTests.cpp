#include <iostream>
#include <unordered_map>

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