#include "Arrays.hpp"

#include <algorithm>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <deque>
#include <queue>
#include <cmath>
#include <map>
#include <numeric>
#include <stack>
#include <set>

// RNG
#include <ctime>
#include <random>

// functional
#include <functional>

int removeDuplicates_Efficient(std::vector<int> &nums)
{
    // time complexity: O(n) where n is array length
    // space complexity: O(1)

    // keep two points i and j, where i is slow-runner and j
    // is the fast-runner. As long as nums[i] == nums[j], increment j
    // to skip the duplicate.

    // When we encounter nums[j] != nums[i], the duplicate run has ended
    // so we must copy it svalue to nums[i + 1]. i can be incremented and
    // we repeat the same process until i reaches the array end

    if (nums.empty())
    {
        return 0;
    }

    int i = 0;
    for (int j = 1; j < nums.size(); ++j)
    {
        if (nums[j] != nums[i])
        {
            i++;
            nums[i] = nums[j];
        }
    }

    return i + 1;
}

int removeDuplicates_PW(std::vector<int> &nums)
{
    if (nums.empty())
    {
        return 0;
    }

    int curElement = nums[0];
    int curLength = 1;
    for (auto i = 1; i < nums.size(); ++i)
    {
        // only increase size of unique element found
        // relies on sorted precondition
        if (nums[i] != curElement)
        {
            nums[curLength++] = nums[i];
            curElement = nums[i];
        }
    }

    return curLength;
}

int removeDuplicates(std::vector<int> &nums)
{
    return removeDuplicates_Efficient(nums);
}

// time complexity: O(n)
// space complexity: O(n)
void rotate_simple(std::vector<int> &nums, int k)
{
    k %= nums.size();
    if (k >= nums.size())
    {
        return;
    }

    std::vector<int> numsRotated;

    // put last k elements up front
    for (int i = nums.size() - k; i < nums.size(); ++i)
    {
        numsRotated.push_back(nums[i]);
    }

    // push remaining elements to end
    for (int i = 0; i < nums.size() - k; ++i)
    {
        numsRotated.push_back(nums[i]);
    }

    // swap nums
    std::swap(nums, numsRotated);
}

// Given an array, rotate the array to the right by k steps, where k is non-negative.
// Try to come up as many solutions as you can, there are at least 3 different ways to solve this problem.
// Could you do it in-place with O(1) extra space?
void rotate(std::vector<int> &nums, int k)
{
    rotate_simple(nums, k);
}

#include <iostream>

// You are given an n x n 2D matrix representing an image.
// Rotate the image by 90 degrees (clockwise).
void rotate(std::vector<std::vector<int>> &matrix)
{
    // [
    // [1,2,3],
    // [4,5,6],
    // [7,8,9]
    // ],
    // [0, 0] => [0, 2]
    // [0, 1] => [1, 2]
    // [0, 2] => [2, 2]
    // [1, 0] => [0, 1]
    // [1, 1] => [1, 1]
    // [1, 2] => [2, 1]
    // [2, 0] => [0, 0]
    // [2, 1] => [1, 0]
    // [2, 2] => [2, 0]

    // rotate the input matrix in-place such that it becomes:
    // [
    // [7,4,1],
    // [8,5,2],
    // [9,6,3]
    // ]

    std::vector<std::vector<int>> rotated;
    rotated.resize(matrix.size());
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        rotated[i].resize(matrix.size());
        for (size_t j = 0; j < matrix.size(); ++j)
        {
            rotated[i][j] = matrix[j][i];
        }
    }

    for (size_t i = 0; i < rotated.size(); ++i)
    {
        for (size_t j = 0; j < rotated.size() / 2; ++j)
        {
            std::swap(rotated[i][j], rotated[i][rotated.size() - 1 - j]);
        }
    }

    std::swap(rotated, matrix);
}

// time complexity: O(3n) = O(n)
// space complexity: O(n + n / 2 + n / 2)
void EvenOdd_BF(std::vector<int> *A_ptr)
{
    std::vector<int> &A = *A_ptr;
    std::vector<int> evens;
    std::vector<int> odds;
    std::copy_if(A.begin(), A.end(), std::back_inserter(evens), [](int el) {
        return el % 2 == 0;
    });
    std::copy_if(A.begin(), A.end(), std::back_inserter(odds), [](int el) {
        return el % 2 == 1;
    });
    A.clear();
    std::copy(evens.begin(), evens.end(), std::back_inserter(A));
    std::copy(odds.begin(), odds.end(), std::back_inserter(A));
}

// time complexity: O(N)
// space complexity: O(1)
void EvenOdd_InPlace(std::vector<int> *A_ptr)
{
    std::vector<int> &A = *A_ptr;

    // if current odd and last even swap
    int oddIdx = *(A.end() - 1);
    int evenIdx = 0;

    auto isEven = [](int n) {
        return n % 2 == 0;
    };

    // lhs == odd, rhs == odd => oddStart-- (don't progress even ptr)
    // lhs == odd, rhs == even => swap(odd, even), oddStart--, evenStart++
    // lhs == even => just increment even ptr (evenIdx++)
    // else (lhs == odd) => swap and decrement odd ptr
    while (oddIdx > evenIdx)
    {
        if (isEven(A[evenIdx]))
        {
            evenIdx++;
        }
        else
        {
            std::swap(A[evenIdx], A[oddIdx--]);
        }
    }
}

void EvenOdd_Book(std::vector<int> *A_ptr)
{
    std::vector<int> &A = *A_ptr;
    int next_even = 0, next_odd = A.size() - 1;
    while (next_even < next_odd)
    {
        if (A[next_even] % 2 == 0)
        {
            next_even++;
        }
        else
        {
            std::swap(A[next_even], A[next_odd--]);
        }
    }
}

void EvenOdd(std::vector<int> *A_ptr)
{
    return EvenOdd_Book(A_ptr);
}

// O(3n) space complexity
// O(4n) time complexity (search, search, search, generate)
void DutchFlagPartition_BF(int pivot_index, std::vector<Color> *a_ptr)
{
    std::vector<Color> &A = *a_ptr;
    int less_idx = 0;
    int greater_idx = A.size() - 1;
    Color pivotVal = A[pivot_index];

    std::vector<Color> less_than;
    std::vector<Color> equal;
    std::vector<Color> greater_than;
    std::copy_if(A.begin(), A.end(), std::back_inserter(less_than), [pivotVal](Color lhs) {
        return lhs < pivotVal;
    });
    std::copy_if(A.begin(), A.end(), std::back_inserter(equal), [pivotVal](Color lhs) {
        return lhs == pivotVal;
    });
    std::copy_if(A.begin(), A.end(), std::back_inserter(greater_than), [pivotVal](Color lhs) {
        return lhs > pivotVal;
    });

    A.clear();
    std::copy(less_than.begin(), less_than.end(), std::back_inserter(A));
    std::copy(equal.begin(), equal.end(), std::back_inserter(A));
    std::copy(greater_than.begin(), greater_than.end(), std::back_inserter(A));
}

// O(1) space complexity
// O(n^2) time complexity
void DutchFlagPartition_n2(int pivot_index, std::vector<Color> *a_ptr)
{
    std::vector<Color> &A = *a_ptr;
    Color pivot = A[pivot_index];

    // First pass: group elements smaller than pivot.
    for (int i = 0; i < A.size(); ++i)
    {
        // Look for a smaller element.
        for (int j = i + 1; j < A.size(); ++j)
        {
            if (A[j] < pivot)
            {
                std::swap(A[i], A[j]);
                break;
            }
        }
    }
    // Second pass: group elements larger than pivot.
    for (int i = A.size() - 1; i >= 0; --i)
    {
        // Look for a larger element. Stop when we reach an element less
        // than pivot, since first pass has moved them to the start of A.
        for (int j = i - 1; j >= 0; --j)
        {
            if (A[j] > pivot)
            {
                std::swap(A[i], A[j]);
                break;
            }
        }
    }
}

// O(1) space complexity
// O(n) time complexity
void DutchFlagPartition_n(int pivot_index, std::vector<Color> *a_ptr)
{
    std::vector<Color> &A = *a_ptr;
    Color pivot = A[pivot_index];
    int smaller = 0;

    // first pass: group elements smaller than pivot.
    for (int i = 0; i < A.size(); ++i)
    {
        if (A[i] < pivot)
        {
            std::swap(A[i], A[smaller++]);
        }
    }
    // second pass: group elements larger than pivot.
    int larger = A.size() - 1;
    for (int i = A.size() - 1; i >= 0; --i)
    {
        if (A[i] > pivot)
        {
            std::swap(A[i], A[larger--]);
        }
    }
}

void DutchFlagPartition_OnePass(int pivot_index, std::vector<Color> *a_ptr)
{
    std::vector<Color> &A = *a_ptr;
    Color pivot = A[pivot_index];
    /**
     * Keep the following invariants during partitioning.
     * bottom group: A[0, smaller - 1]
     * middle group: A[smaller, equal - 1]
     * unclassified group: A[equal, larger - 1]
     * top group: A[larger, size(A) - 1]
     */
    int smaller = 0, equal = 0, larger = A.size();

    // Keep iterating as long as there is an unclassified element.
    while (equal < larger)
    {
        // A[equal] is the incoming unclassified element.
        if (A[equal] < pivot)
        {
            std::swap(A[smaller++], A[equal++]);
        }
        else if (A[equal] == pivot)
        {
            ++equal;
        }
        else // A[equal] > pivot
        {
            std::swap(A[equal], A[--larger]);
        }
    }
}

void DutchFlagPartition(int pivot_index, std::vector<Color> *a_ptr)
{
    DutchFlagPartition_OnePass(pivot_index, a_ptr);
}

void moveZeroes(std::vector<int> &nums)
{
    std::stable_partition(nums.begin(), nums.end(), [](int num) {
        return num != 0;
    });
}

// time complexity: O(n), where n is length of A
std::vector<int> PlusOne(std::vector<int> A)
{
    ++A.back();
    for (int i = A.size() - 1; i > 0 && A[i] == 10; --i)
    {
        A[i] = 0, ++A[i - 1];
    }

    if (A[0] == 10)
    {
        // There is a carry-out, so we need one more digit to store the result.
        // A smart way to do this is to append 0 to end of the array.

        A[0] = 1;
        A.emplace_back(0);
    }

    return A;
}

bool containsDuplicate(std::vector<int> &nums)
{
    std::unordered_set<int> elements;
    for (auto num : nums)
    {
        if (elements.find(num) == elements.end())
        {
            elements.insert(num);
        }
        else
        {
            return true;
        }
    }

    return false;
}

bool isValidSudoku(std::vector<std::vector<char>> &board)
{
    // check columns
    for (int i = 0; i < board.size(); i++)
    {
        std::unordered_set<char> cols;
        for (int j = 0; j < board.size(); ++j)
        {
            if (board[i][j] == '.')
                continue;

            if (cols.find(board[i][j]) == cols.end())
            {
                cols.insert(board[i][j]);
            }
            else
            {
                return false;
            }
        }
    }

    // check rows
    for (int i = 0; i < board.size(); i++)
    {
        std::unordered_set<char> rows;
        for (int j = 0; j < board.size(); ++j)
        {
            if (board[j][i] == '.')
                continue;

            if (rows.find(board[j][i]) == rows.end())
            {
                rows.insert(board[j][i]);
            }
            else
            {
                return false;
            }
        }
    }

    // check subgrid
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            std::unordered_set<int> grid;
            for (int k = 0; k < 3; ++k)
            {
                for (int m = 0; m < 3; ++m)
                {
                    if (board[i * 3 + k][j * 3 + m] == '.')
                        continue;

                    if (grid.find(board[i * 3 + k][j * 3 + m]) == grid.end())
                    {
                        grid.insert(board[i * 3 + k][j * 3 + m]);
                    }
                    else
                    {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

// O(n * m) operations
//
std::vector<int> Multiply_PW(std::vector<int> num1, std::vector<int> num2)
{
    // maximum number of digits is m + n, where
    // m == num digits in num1 and n == num digits of num2
    std::vector<int> result(num1.size() + num2.size());

    // handle negatives
    const int sign = (num1.front() < 0) ^ (num2.front() < 0) ? -1 : 1;
    num1.front() = abs(num1.front()), num2.front() = abs(num2.front());

    int carry = 0;
    int digit = 0;

    for (int i = num1.size() - 1; i >= 0; --i)
    {
        for (int j = num2.size() - 1; j >= 0; --j)
        {
            result[i + j + 1] += num2[j] * num1[i];
            digit = result[i + j + 1] % 10;
            carry = result[i + j + 1] / 10;
            result[i + j + 1] = digit;
            result[i + j] += carry;
        }
    }

    // remove leading zeroes
    auto iter = std::find_if(result.begin(), result.end(), [](int num) {
        return num != 0;
    });

    if (iter == result.end())
    {
        return {0};
    }
    else
    {
        std::vector<int> stripped;
        for (auto it = iter; it != result.end(); it++)
        {
            stripped.push_back(*it);
        }

        stripped.front() *= sign;
        return stripped;
    }
}

std::vector<int> Multiply_EPI(std::vector<int> num1, std::vector<int> num2)
{
    const int sign = (num1.front() < 0) ^ (num2.front() < 0) ? -1 : 11;
    num1.front() = abs(num1.front()), num2.front() = abs(num2.front());

    std::vector<int> result(num1.size() + num2.size(), 0);
    for (int i = num1.size() - 1; i >= 0; --i)
    {
        for (int j = num2.size() - 1; j >= 0; --j)
        {
            result[i + j + 1] += num1[i] * num2[j];
            result[i + j] += result[i + j + 1] / 10;
            result[i + j + 1] %= 10;
        }
    }

    // Remove leading zeroes
    result = {
        std::find_if_not(result.begin(), result.end(), [](int a) { return a == 0; }),
        result.end()};

    if (result.empty())
    {
        return {0};
    }
    result.front() *= sign;
    return result;
}

std::vector<int> Multiply(std::vector<int> num1, std::vector<int> num2)
{
    return Multiply_EPI(num1, num2);
}

// O(n! ^ 2): each n have to decrement and revisit possibly
// space complexity: O(n!^2); create new vector for each test case
// could improve with memoization and iterators instead o new vector
bool CanReachEnd_BF(const std::vector<int> &max_advance_steps)
{
    // 3, 3, 1, 0, 2, 0, 1
    // try 3
    // 3 -> 0 (no)
    // 2 -> 1 -> 0 (no)
    // 1 -> 3 -> 2 -> end

    // 3, 2, 0, 0, 2, 0, 1
    // try 3
    // 3 -> 0 (no)
    // 2 -> 0 (no)
    // 1 -> 2 -> 0 (no)
    // 0 (no)

    // starting with leftmost position,
    //  try dfs approach
    //  1. see if we can reach end starting with largest step size
    //  2. if not, decrement and try again
    //  3. if we reach 0, back track. The algorithm will naturally exit of seed decremented to 0.

    int seed = max_advance_steps[0];
    bool reachedEnd = false;
    for (int i = seed; i > 0; i--)
    {
        if (i >= max_advance_steps.size() - 1)
        {
            return true;
        }

        std::vector<int> rest(max_advance_steps.begin() + i, max_advance_steps.end());
        if (CanReachEnd(rest))
        {
            return true;
        }
    }

    return reachedEnd;
}

// O(n): go through vector once
// O(1): constant space complexity
bool CanReachEnd_EPI(const std::vector<int> &max_advance_steps)
{
    // 3, 3, 1, 0, 2, 0, 1
    // what's the farthest I can get at a given point
    int furthest_reach_so_far = 0, last_index = max_advance_steps.size() - 1;
    for (int i = 0;
         i <= furthest_reach_so_far &&
         furthest_reach_so_far < last_index;
         ++i)
    {
        furthest_reach_so_far = std::max(
            furthest_reach_so_far,
            max_advance_steps[i] + i);
    }

    return furthest_reach_so_far >= last_index;
}

bool CanReachEnd(const std::vector<int> &max_advance_steps)
{
    return CanReachEnd_EPI(max_advance_steps);
}

// O(n) time complexity
// O(1) space
int DeleteDuplicates_PW(std::vector<int> *A_ptr)
{
    std::vector<int> &A = *A_ptr;

    if (A.empty())
    {
        return 0;
    }

    int j = 0;
    for (size_t i = 1; i < A.size(); i++)
    {
        if (A[i] != A[j])
        {
            A[++j] = A[i];
        }
    }

    return j + 1;
}

// O(n) time complexity
// O(1) space
int DeleteDuplicates_EPI(std::vector<int> *A_ptr)
{
    std::vector<int> &A = *A_ptr;
    if (A.empty())
    {
        return 0;
    }

    int writeIndex = 1;
    for (int i = 1; i < A.size(); ++i)
    {
        if (A[writeIndex - 1] != A[i])
        {
            A[writeIndex++] = A[i];
        }
    }

    return writeIndex;
}

int DeleteDuplicates(std::vector<int> *A_ptr)
{
    return DeleteDuplicates_EPI(A_ptr);
}

int DeleteKey(std::vector<int> *A_ptr, int key)
{
    std::vector<int> &A = *A_ptr;
    if (A.empty())
    {
        return 0;
    }

    int writeIndex = 0;
    for (int i = 0; i < A.size(); ++i)
    {
        if (A[i] != key)
        {
            A[writeIndex++] = A[i];
        }
    }

    return writeIndex;
}

int AtMostN(std::vector<int> *A_ptr)
{
    std::vector<int> &A = *A_ptr;
    if (A.empty())
    {
        return 0;
    }

    int writeIndex = 0;
    int curCount = 1;
    for (int i = 1; i < A.size(); ++i)
    {
        if (A[i] != A[writeIndex])
        {
            A[++writeIndex] = A[i];
            curCount = 1;
        }
        else if (curCount < 2)
        {
            A[++writeIndex] = A[i];
            curCount++;
        }
        else
        {
            curCount++;
        }
    }

    return writeIndex + 1;
}

// time complexity: O(n^2)
double BuyAndSellStockOnce_BF(const std::vector<double> &prices)
{
    double max = 0;
    for (auto i = 0; i < prices.size() - 1; i++)
    {
        for (auto j = i; j < prices.size(); j++)
        {
            max = std::max(prices[j] - prices[i], max);
        }
    }

    return max;
}

// time complexity: O(n)
// space complexity: O(1)
double BuyAndSellStockOnce_LINEAR(const std::vector<double> &prices)
{
    double maxDiff = 0;
    double min = std::numeric_limits<double>::max();
    for (auto price : prices)
    {
        maxDiff = std::max(maxDiff, price - min);
        min = std::min(min, price);
    }

    return maxDiff;
}

// time complexity: O(n)
// space complexity: O(1)
double BuyAndSellStockOnce_EPI(const std::vector<double> &prices)
{
    double min_price_so_far = std::numeric_limits<double>::max(), max_profit = 0;
    for (double price : prices)
    {
        double max_profit_sell_today = price - min_price_so_far;
        max_profit = std::max(max_profit, max_profit_sell_today);
        min_price_so_far = std::min(min_price_so_far, price);
    }

    return max_profit;
}

double BuyAndSellStockOnce(const std::vector<double> &prices)
{
    // TODO: write O(n log n solution)
    return BuyAndSellStockOnce_EPI(prices);
}

// time complexity: O(n)
// space complexity: O(1)
size_t longestContiguousSubarray(const std::vector<int> &nums)
{
    // 1, 2, 2, 3
    if (nums.empty())
    {
        return 0;
    }

    size_t longestSoFar = 1;
    size_t curLongest = 1;
    int curNum = nums[0];

    for (size_t i = 1; i < nums.size(); ++i)
    {
        if (curNum == nums[i])
        {
            curLongest++;
            longestSoFar = std::max(curLongest, longestSoFar);
        }
        else
        {
            curLongest = 1;
            curNum = nums[i];
        }
    }

    return longestSoFar;
}

double BuyAndSellStockTwice_BF(const std::vector<double> &prices)
{
    double max_total_profit = 0;
    for (size_t i = 0; i < prices.size(); i++)
    {
        for (size_t j = 0; j < prices.size(); j++)
        {
            for (size_t k = 0; k < prices.size(); k++)
            {
                for (size_t l = 0; l < prices.size(); l++)
                {
                    if (i < j && k < l && j < k)
                    {
                        max_total_profit = std::max(
                            max_total_profit,
                            prices[l] - prices[k] +
                                prices[j] - prices[i]);
                    }
                    else if (i < j)
                    {
                        // cover the case where only one buy/sell occurs
                        max_total_profit = std::max(
                            max_total_profit,
                            prices[j] - prices[i]);
                    }
                }
            }
        }
    }

    return max_total_profit;
}

// O(n) time, O(n) space
double BuyAndSellStockTwice_EPI(const std::vector<double> &prices)
{
    double max_total_profit = 0;
    std::vector<double> first_buy_sell_profits(prices.size(), 0);
    double min_price_so_far = std::numeric_limits<double>::max();

    // Forward phase. For each day, we record maximum profit if we sell
    // on that day.
    for (int i = 0; i < prices.size(); ++i)
    {
        min_price_so_far = std::min(min_price_so_far, prices[i]);
        max_total_profit = std::max(max_total_profit, prices[i] - min_price_so_far);
        first_buy_sell_profits[i] = max_total_profit;
    }

    // Backward phase. For each day, find the maximum profit if we make the
    // second buy on that day.
    double max_price_so_far = std::numeric_limits<double>::min();
    for (int i = prices.size() - 1; i > 0; --i)
    {
        max_price_so_far = std::max(max_price_so_far, prices[i]);
        max_total_profit =
            std::max(max_total_profit,
                     max_price_so_far - prices[i] + first_buy_sell_profits[i - 1]);
    }

    return max_total_profit;
}

double BuyAndSellStockTwice(const std::vector<double> &prices)
{
    return BuyAndSellStockTwice_EPI(prices);
}

std::vector<int> intersect(std::vector<int> &nums1, std::vector<int> &nums2)
{
    std::unordered_map<int, int> uniq1;
    std::unordered_map<int, int> uniq2;

    for (auto num : nums1)
    {
        if (uniq1.find(num) == uniq1.end())
        {
            uniq1[num] = 1;
        }
        else
        {
            uniq1[num]++;
        }
    }

    for (auto num : nums2)
    {
        if (uniq2.find(num) == uniq2.end())
        {
            uniq2[num] = 1;
        }
        else
        {
            uniq2[num]++;
        }
    }

    std::vector<int> result;
    for (auto entry : uniq1)
    {
        int key = entry.first;
        if (uniq2.find(key) != uniq2.end())
        {
            int min = std::min(
                uniq1[key],
                uniq2[key]);

            for (int i = 0; i < min; i++)
            {
                result.push_back(key);
            }
        }
    }

    return result;
}

void Rearrange_BF(std::vector<int> *A_ptr)
{
    std::vector<int> &A = *A_ptr;
    std::sort(A.begin(), A.end());
    std::vector<int> B;
    B.push_back(A[0]);

    for (size_t i = 1; i < A.size(); i += 2)
    {
        if (i + 1 < A.size())
        {
            B.push_back(A[i + 1]);
        }

        B.push_back(A[i]);
    }

    std::swap(A, B);
}

void Rearrange_EPI(std::vector<int> *A_ptr)
{
    std::vector<int> &A = *A_ptr;
    for (size_t i = 1; i < A.size(); ++i)
    {
        // if ((A[i] > A[i+1] && i % 2 == 0) ||
        //     (A[i] < A[i+1] && i % 2 == 1))

        // iterative refinement of a brute-force solution
        if ((A[i - 1] < A[i] && i % 2 == 0) ||
            (A[i - 1] > A[i] && i % 2 == 1))
        {
            std::swap(A[i - 1], A[i]);
        }
    }
}

void Rearrange(std::vector<int> *A_ptr)
{
    Rearrange_EPI(A_ptr);
}

std::vector<int> sortArrayByParity(std::vector<int> &A)
{

    // if current odd and last even swap
    int oddIdx = A.size() - 1;
    int evenIdx = 0;

    auto isEven = [](int n) {
        return n % 2 == 0;
    };

    // lhs == odd, rhs == odd => oddStart-- (don't progress even ptr)
    // lhs == odd, rhs == even => swap(odd, even), oddStart--, evenStart++
    // lhs == even => just increment even ptr (evenIdx++)
    // else (lhs == odd) => swap and decrement odd ptr
    while (oddIdx > evenIdx)
    {
        if (isEven(A[evenIdx]))
        {
            evenIdx++;
        }
        else
        {
            std::swap(A[evenIdx], A[oddIdx--]);
        }
    }

    std::vector<int> result(A);
    return result;
}

// sieve == remove all its multiples from future consideration
std::vector<int> GeneratePrimes_Sieve(int n)
{
    // Sieve of Erastothenes
    std::vector<int> primes(n + 1, 1);
    std::vector<int> results;
    primes[0] = 0;
    primes[1] = 1;
    for (size_t i = 2; i <= n; i++)
    {
        if (primes[i])
        {
            int mult = i;
            mult += i;
            while (mult <= n)
            {
                primes[mult] = 0;
                mult += i;
            }
        }
    }

    for (size_t i = 2; i <= n; i++)
    {
        if (primes[i])
        {
            results.push_back(i);
        }
    }

    return results;
}

// trial-division approach
// O(n^3/2) => O(n^3/2 / (log n)^2)
// Given n, return all primes up to and including n.
// O(n/2 + n/3 + n/5 + n/7 + n/11 + ...)
// O(n log log n) time complexity
// O(n) space complexity
std::vector<int> GeneratePrimes_EPI1(int n)
{
    std::vector<int> primes;
    // is_prime[p] represents if p is prime or not. Initially,
    // set each to true, excepting 0 and 1. Then use sieving to eliminate
    // nonprimes.
    std::deque<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; p <= n; ++p)
    {
        if (is_prime[p])
        {
            primes.emplace_back(p);
            // Sieve p's multiples
            for (int i = p * 2; i <= n; i += p)
            {
                is_prime[i] = false;
            }
        }
    }

    return primes;
}
// space and time complexity identical for sieve
// https://stackoverflow.com/a/16890100
std::vector<int> GeneratePrimes_SieveOptimized(int n)
{
    if (n < 2)
    {
        return {};
    }

    const int size = std::floor(0.5 * (n - 3)) + 1;
    std::vector<int> primes;
    primes.emplace_back(2);

    // is_prime[p] represents whether (2i + 3) is prime or not.
    // For example, is_prime[0] represents 3 is prime or not, is_prime[1]
    // represents 5, is_prime[2] represents 7, etc.
    // Initially set each to true. Then use sieving to eliminate nonprimes.
    std::deque<bool> is_prime(size, true);
    for (int i = 0; i < size; ++i)
    {
        if (is_prime[i])
        {
            int p = (i * 2) + 3;
            primes.emplace_back(p);

            // Sieving from p^2, whose value is (4i^2 + 12i + 9). The index in
            // is_prime is (2i^2 + 6i + 3) because is_prime[i] represents 2i + 3
            //
            // Note that we need to use long long for j because p^2 might overflow.
            // p^2 = 4i^2 + 12i + 9
            // index of p^2 = 2i^2 + 6i + 3 => (2 * index + 3) = 4i^2 + 12i + 9
            // index = 2i^2 + 6i + 3
            for (long long j = 2LL * i * i + 6 * i + 3; j < size; j += p)
            {
                is_prime[j] = false;
            }
        }
    }

    return primes;
}

std::vector<int> GeneratePrimes(int n)
{
    return GeneratePrimes_SieveOptimized(n);
}

// time complexity: O(n)
// space complexity: O(n)
void ApplyPermutation_BF(std::vector<int> perm, std::vector<int> *A_ptr)
{
    std::vector<int> &A = *A_ptr;
    std::vector<int> permuted(A.size());

    for (auto p : perm)
    {
        permuted[p] = A[p];
    }

    std::swap(permuted, A);
}

void ApplyPermutation_Optimal(std::vector<int> perm, std::vector<int> *A_ptr)
{
    std::vector<int> &A = *A_ptr;

    size_t i = 0;
    while (true)
    {
        if (i >= A.size())
        {
            break;
        }
        else if (i == perm[i])
        {
            i++;
            continue;
        }
        else
        {
            std::swap(A[i], A[perm[i]]);
            std::swap(perm[perm[i]], perm[i]);
        }
    }
}

// O(n) time complexity
// O(n) space complexity?
void ApplyPermutation_EPI(std::vector<int> perm, std::vector<int> *A_ptr)
{
    std::vector<int> &A = *A_ptr;
    for (int i = 0; i < A.size(); ++i)
    {
        while (perm[i] != i)
        {
            std::swap(A[i], A[perm[i]]);
            std::swap(perm[i], perm[perm[i]]);
        }
    }
}

void ApplyPermutation_NoMut(std::vector<int> perm, std::vector<int> *A_ptr)
{
    std::vector<int> &A = *A_ptr;
    for (int i = 0; i < A.size(); ++i)
    {
        while (perm[i] != i)
        {
            std::swap(A[i], A[perm[i]]);
            std::swap(perm[i], perm[perm[i]]);
        }
    }
}

void ApplyPermutation(std::vector<int> perm, std::vector<int> *A_ptr)
{

    return ApplyPermutation_Optimal(perm, A_ptr);
}

std::vector<int> NextPermutation_PW(std::vector<int> perm)
{
    std::vector<int> nums = perm;
    std::unordered_map<int, int> swap_candidates = {};
    int largestSwapIndex = -1;

    for (int i = nums.size() - 1; i > 0; --i)
    {
        if (i <= largestSwapIndex)
        {
            break;
        }

        for (int j = i - 1; j >= 0; j--)
        {
            if (nums[i] > nums[j])
            {
                swap_candidates[i] = j;
                largestSwapIndex = std::max(largestSwapIndex, j);
                break;
            }
        }
    }

    std::map<int, int> downSelected;
    for (auto c : swap_candidates)
    {
        if (c.second == largestSwapIndex)
        {
            downSelected[nums[c.first]] = c.first;
        }
    }

    if (largestSwapIndex == -1)
    {
        return {};
    }

    std::swap(nums[largestSwapIndex], nums[downSelected.begin()->second]);
    std::sort(nums.begin() + largestSwapIndex + 1, nums.end());

    return nums;
}

// O(n) complexity: each step is an iteration through an array
// All additional space complexity is O(1)
std::vector<int> NextPermutation_EPI(std::vector<int> perm)
{
    // 1. Find k such that p[k] < p[k + 1] and entries after index k appear in decreasing order
    // 2. Find the smallest p[l] such that p[l] > p[k] (such an l must exist since p[k] < p[k+1])
    // 3. Swap p[l] and p[k] (note that the sequence after position k remains in decreasing order)
    // 4. Reverse the sequence after position k

    // Find the first entry from the right that is smaller than the entry immediately after it.
    auto inversion_point = is_sorted_until(perm.rbegin(), perm.rend());
    if (inversion_point == perm.rend())
    {
        // perm is sorted in decreasing order, so it's the last permutation
        return {};
    }

    // Swap the entry referenced by the inversion point with the smallest entry
    // appearing after inversion_point that is greater than the entry referenced
    // by inversion point:
    //
    // 1.) Find the smallest entry after inversion_point that's greater than the
    //      entry referenced by inversion_point. Since perm must be sorted in
    //      decreasing order after inversion_point, we can use a fast algorithm
    //      to find this entry.

    auto least_upper_bound =
        upper_bound(perm.rbegin(), inversion_point, *inversion_point);

    // 2.) Perform the swap
    iter_swap(inversion_point, least_upper_bound);

    // Reverse the subarray that follow the inversion_point.
    reverse(perm.rbegin(), inversion_point);
    return perm;
}

std::vector<int> NextPermutation(std::vector<int> perm)
{
    return NextPermutation_EPI(perm);
}

void NextPermutationLC(std::vector<int> &nums)
{
    auto result = NextPermutation(nums);
    if (result.empty())
    {
        std::sort(nums.begin(), nums.end());
    }
    else
    {
        std::swap(nums, result);
    }
}

// space complexity: O(1)
// time complexity: O(k)
void RandomSampling_PW(int k, std::vector<int>* A_ptr)
{
    auto& A = *A_ptr;
    srand(time(NULL));

    // step through numbers, swap indices when found
    for (int i = 0; i < k; ++i)
    {
        int index = (rand() % (A.size() - i)) + i;
        std::swap(A[i], A[index]);
    }
}

// space complexity: O(1)
// time complexity: O(k)

void RandomSampling_EPI(int k, std::vector<int>* A_ptr)
{
    std::vector<int>& A = *A_ptr;
    std::default_random_engine seed((std::random_device())());

    for (int i = 0; i < k; ++i)
    {
        // Generate a random index in [i, size(A) - 1].
        
        //     Common failings of "bad" - but common enough - rand() implementations are:

        // low randomness of low-order bits;
        // short period;
        // low RAND_MAX;
        // some correlation between successive extractions (in general, LCGs produce numbers that are on a limited number of hyperplanes, although this can be somehow mitigated).

        // why use uniform_int_distribution vs. rand(): https://stackoverflow.com/a/32860886
        // https://www.youtube.com/watch?v=LDPMpc-ENqY&feature=youtu.be
        std::swap(A[i], A[std::uniform_int_distribution<int>{i, static_cast<int>(A.size()) - 1}(seed)]);
    }
}

void RandomSampling(int k, std::vector<int>* A_ptr)
{
    return RandomSampling_EPI(k, A_ptr);
}

static std::vector<int> randomSamples(1000);
static int randomSamplesSize = 0;

// space complexity: O(n) all packets stored 
// time complexity: O(nk) each packet is read followed by invoke to random sampling
std::vector<int> OnlineRandomSample_BF(std::vector<int>::const_iterator stream_begin,
    const std::vector<int>::const_iterator stream_end,
    int k)
{
    static bool initialized = false;
    
    std::default_random_engine seed((std::random_device())());

    if (!initialized)
    {
        randomSamples.clear();
    }

    for (auto iter = stream_begin; iter != stream_end; iter++)
    {
        randomSamples.push_back(*iter);
    }

    for (int i = 0; i < k; i++)
    {
        std::swap(randomSamples[i], randomSamples[std::uniform_int_distribution<int>{i, static_cast<int>(randomSamples.size()) - 1}(seed)]);
    }

    std::vector<int> results;
    for (int i = 0; i < k; i++)
    {
        results.push_back(randomSamples[i]);
    }

    return results;
}

std::vector<int> OnlineRandomSample_PW(std::vector<int>::const_iterator stream_begin,
    const std::vector<int>::const_iterator stream_end,
    int k)
{
    // how to deal with n + 1 packet
    // for each value, heads or tails swap
    // else push

    std::default_random_engine seed((std::random_device())());

    int i = 0;
    auto iter = stream_begin;
    while (randomSamplesSize < k && iter != stream_end)
    {
        // append 
        randomSamples[randomSamplesSize++] = *iter;
        iter++;
        i++;
    }
    
    i = 0;
    for (; iter != stream_end; iter++)
    {
        int res = std::uniform_int_distribution<int>{i, static_cast<int>(k)}(seed);
        if (res < k)
        {
            randomSamples[res] = *iter;
        }
    }
    
    return randomSamples;
}

// O(n); per element operations are O(1)
// O(k); extra space
std::vector<int> OnlineRandomSample_EPI(std::vector<int>::const_iterator stream_begin,
    const std::vector<int>::const_iterator stream_end,
    int k)
{
    // how to deal with n + 1 packet
    // for each value, heads or tails swap
    // else push

    std::vector<int> running_sample;

    // Storesult the first k elements.
    for (int i = 0; i < k; ++i)
    {
        running_sample.emplace_back(*stream_begin++);
    }

    std::default_random_engine seed((std::random_device())());
    // Have read the first k elements

    int num_seen_so_far = k;
    while (stream_begin != stream_end)
    {
        int x = *stream_begin++;
        ++num_seen_so_far;
        // Generate a random number in [0, num_seen_so_far - 1], and if this
        // number is in [0, k - 1], we replace that element form the sample with 
        // x.
        if (const int idx_to_replace = std::uniform_int_distribution<int>{0, num_seen_so_far - 1}(seed);
            idx_to_replace < k)
        {
            running_sample[idx_to_replace] = x;
        }
    }

    return running_sample;
}

std::vector<int> OnlineRandomSample(std::vector<int>::const_iterator stream_begin,
    const std::vector<int>::const_iterator stream_end,
    int k)
{
    return OnlineRandomSample_EPI(stream_begin, stream_end, k);
}

// space complexity: O(n) (hash table + array)
// time complexity: coupon collector's problem; first few values likely chosen quickly, last few not so much
//  O (n log n)
std::vector<int> ComputeRandomPermutation_PWBF(int n)
{
    std::vector<int> result(n);
    std::unordered_set<int> selected;
    srand(time(NULL));
    
    for (int i = 0; i < n; i++)
    {
        while (true)
        {
            int val = rand() % n;
            if (selected.find(val) == selected.end())
            {
                result[i] = val;
                selected.insert(val);
                break;
            }
        }
    }

    return result;
}

// space complexity: O(n), no additional storage
// time complexity: O(n)
std::vector<int> ComputeRandomPermutation_EPI(int n) 
{
    std::vector<int> permutation(n);
    // Initializes permutation to 0, 1, 2, ..., n - 1;
    std::iota(permutation.begin(), permutation.end(), 0);
    RandomSampling(n, &permutation);
    return permutation;
}

std::vector<int> ComputeRandomPermutation(int n)
{
    return ComputeRandomPermutation_EPI(n);
}

int fact(int n) {

    if (n == 0 || n == 1)
    {
        return 1;
    }
    else
    {
        return n * fact(n - 1);
    }
};

std::vector<int> RandomSubset_PW(int n, int k)
{
    // create a hash table of all possible (there should be n possible)
    std::vector<int> arr(n);
    std::iota(arr.begin(), arr.end(), 0);
    
    // subsets
    int numSubsets = fact(n) / (fact(n - k) * fact(k));
    std::vector<std::vector<int>> subsets;

    while (true)
    {
        if (subsets.size() == numSubsets)
        {
            break;
        }

        // get random subset
        RandomSampling(k, &arr);

        bool matches = false;
        for (auto subset: subsets)
        {
            bool matching = true;
            for (int i = 0; i < subset.size(); ++i)
            {
                if (subset[i] != arr[i])
                {
                    matching = false;
                    break;
                }
            }

            if (matching)
            {
                matches = true;
                break;
            }
        }

        if (!matches)
        {
            std::vector<int> newSubset(arr.begin(), arr.begin() + k);
            subsets.push_back(newSubset);
        }
    }

    int randIdx = rand() % numSubsets;
    return subsets[randIdx];
}

// brute force => Solution 5.14 brute force
// O(n) space, O(n) + O(k) time => offline sampling from 5.12
// time complexity: O(k) => bounded number of ops per iteration, space complexity O(k)
std::vector<int> RandomSubset_EPI(int n, int k)
{
    std::unordered_map<int, int> changed_elements;
    std::default_random_engine seed((std::random_device())());
    for (int i = 0; i < k; ++i)
    {
        // Generate a random index in [i, n - 1]
        int rand_idx = std::uniform_int_distribution<int>{i, n - 1}(seed);
        if (auto ptr1 = changed_elements.find(rand_idx),
            ptr2 = changed_elements.find(i);
            ptr1 == changed_elements.end() && ptr2 == changed_elements.end())
        {
            changed_elements[rand_idx] = i;
            changed_elements[i] = rand_idx;
        }
        else if (ptr1 == changed_elements.end() &&
                 ptr2 != changed_elements.end())
        {
            changed_elements[rand_idx] = ptr2->second;
            ptr2->second = rand_idx;
        }
        else if (ptr1 != changed_elements.end() && 
                 ptr2 == changed_elements.end())
        {
            changed_elements[i] = ptr1->second;
            ptr1->second = i;
        }
        else
        {
            int temp = ptr2->second;
            changed_elements[i] = ptr1->second;
            changed_elements[rand_idx] = temp;
        }
    }

    std::vector<int> result;
    for (int i = 0; i < k; ++i)
    {
        result.emplace_back(changed_elements[i]);
    }

    return result;
}

std::vector<int> RandomSubset(int n, int k)
{
    return RandomSubset_EPI(n, k);
}

// time complexity: O(n)
// space complexity: O(n)
int NonuniformRandomNumberGeneration_PW(const std::vector<int>& values,
                                     const std::vector<double>& probabilities)
{
    // generate a value between 0 and 1
    // step through probabilities until found value
    std::default_random_engine seed((std::random_device())());

    float result = (float)std::uniform_int_distribution<int>{0, 100}(seed) / 100;

    int selectedIdx = 0;
    float probThusFar = 0;
    for (int i = 0; i < probabilities.size(); ++i)
    {
        probThusFar += probabilities[i];
        if (probThusFar >= result)
        {
            break;
        }

        selectedIdx++;
    }

    return values[selectedIdx];
}

// time complexity to compute a single value: O(n)
// space complexity: O(n)
// after array constructed, O(log n) to find value (binary search using upper_bound)
int NonuniformRandomNumberGeneration_EPI(const std::vector<int>& values,
                                     const std::vector<double>& probabilities)
{
    std::vector<double> prefix_sums_of_probabilities;
    // Creating the endpoints for the intervals corresponding to the 
    // probabilities.

    std::partial_sum(std::cbegin(probabilities), std::cend(probabilities),
        std::back_inserter(prefix_sums_of_probabilities));
    
    std::default_random_engine seed((std::random_device())());
    const double uniform_0_1 =
        std::generate_canonical<double, std::numeric_limits<double>::digits>(seed);

    // find the index of the interval that uniform_0_1 lies in, which is the
    // return value of upper_bound() minus 1
    const int interval_idx =
        std::distance(std::cbegin(prefix_sums_of_probabilities),
            std::upper_bound(std::cbegin(prefix_sums_of_probabilities),
            std::cend(prefix_sums_of_probabilities), uniform_0_1));

    return values[interval_idx];
}

int NonuniformRandomNumberGeneration(const std::vector<int>& values,
                                     const std::vector<double>& probabilities)
{
    return NonuniformRandomNumberGeneration_EPI(values, probabilities);
}

bool IsValidSudoku_PW(std::vector<std::vector<int>>& partial_assignment)
{
    for (int i = 0; i < partial_assignment.size(); ++i)
    {
        std::unordered_set<int> cols;
        for (int j = 0; j < partial_assignment[0].size(); ++j)
        {
            int value = partial_assignment[i][j];
            if (value == 0)
            {
                continue;
            }
            else if (cols.find(value) == cols.end())
            {
                cols.insert(value);
            }
            else
            {
                return false;
            }
        }
    }

    for (int i = 0; i < partial_assignment.size(); ++i)
    {
        std::unordered_set<int> rows;
        for (int j = 0; j < partial_assignment[0].size(); ++j)
        {
            int value = partial_assignment[j][i];
            if (value == 0)
            {
                continue;
            }
            else if (rows.find(value) == rows.end())
            {
                rows.insert(value);
            }
            else
            {
                return false;
            }
        }
    }

    for (int i = 0; i < 9; i++)
    {
        std::unordered_set<int> subgrid;
        int mRow = i / 3;
        int mCol = i % 3;/* code */
        for (int j = 0; j < 3; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                int value = partial_assignment[(mRow * 3) + j][(mCol * 3) + k];
                if (value == 0)
                {
                    continue;
                }
                else if (subgrid.find(value) == subgrid.end())
                {
                    subgrid.insert(value);
                }
                else
                {
                    return false;
                }
            }
        }
    }

    return true;
}

// Return true if subarray partial_assignment[start_row, end_row - 1][start_col, end_col - 1]
// contains any duplicates in {1, 2, ...,, size(partial_assignment)}; otherwise return false.
// time complexity: nxn grid => O(n^2) + O(n^2/(sqrt(n)^2) * (sqrt(n)^2)) = O(n^2)
// space complexity: O(n) => bit array to check constraints
bool HasDuplicate(const std::vector<std::vector<int>>& partial_assignment, int start_row, int end_row, int start_col, int end_col)
{
    std::deque<bool> is_present(partial_assignment.size() + 1, false);
    for (int i = start_row; i < end_row; ++i)
    {
        for (int j = start_col; j < end_col; ++j)
        {
            if (partial_assignment[i][j] != 0 &&
                is_present[partial_assignment[i][j]]) 
            {
                return true;
            }
            is_present[partial_assignment[i][j]] = true;
        }
    }
    return false;
}

// Check if a partially filled matrix has any conflicts.
bool IsValidSudoku_EPI(std::vector<std::vector<int>>& partial_assignment)
{
    // Check row constraints.
    for (int i = 0; i < partial_assignment.size(); ++i)
    {
        if (HasDuplicate(partial_assignment, i, i + 1, 0, partial_assignment.size()))
        {
            return false;
        }
    }

    // Check column constraints.
    for (int j = 0; j < partial_assignment.size(); ++j)
    {
        if (HasDuplicate(partial_assignment, 0, partial_assignment.size(), j, j + 1))
        {
            return false;
        }
    }

    // Check region constraints.
    int region_size = sqrt(partial_assignment.size());
    for (int I = 0; I < region_size; ++I)
    {
        for (int J = 0; J < region_size; ++J)
        {
            if (HasDuplicate(partial_assignment, region_size * I,
                region_size * (I + 1), region_size * J,
                region_size * (J + 1)))
            {
                return false;
            }
        }
    }
    
    return true;
}

bool IsValidSudoku(std::vector<std::vector<int>>& partial_assignment)
{
    return IsValidSudoku_EPI(partial_assignment);
}

std::vector<int> MatrixInSpiralOrder_PW(const std::vector<std::vector<int>>& square_matrix)
{
    std::vector<int> spiral_order;

    int i = 0;
    int counter = 0;
    int maxWidth = square_matrix[0].size();
    int maxHeight = square_matrix.size();
    while (true)
    {
        // top

        bool noUpdates = true;
        for (int c = i; c < maxWidth - i; c++)
        {
            noUpdates = false;
            spiral_order.push_back(square_matrix[i][c]);
        }

        if (noUpdates)
        {
            break;
        }

        // right
        noUpdates = true;
        for (int r = i + 1; r < maxHeight -i; r++)
        {
            noUpdates = false;
            spiral_order.push_back(square_matrix[r][maxWidth - i - 1]);
        }

        if (noUpdates)
        {
            break;
        }

        // bottom
        noUpdates = true;
        for (int c = maxWidth - i - 2; c >= i; c--)
        {
            noUpdates = false;
            spiral_order.push_back(square_matrix[maxHeight - i - 1][c]);
        }

        if (noUpdates)
        {
            break;
        }

        // left
        noUpdates = true;
        for (int r = maxHeight - i - 2; r >= i + 1; r--)
        {
            noUpdates = false;
            spiral_order.push_back(square_matrix[r][i]);
        }

        if (noUpdates)
        {
            break;
        }
        i++;
    }

    return spiral_order;
}

void MatrixLayerInClockwise(const std::vector<std::vector<int>>& square_matrix,
    int offset, std::vector<int>* spiral_ordering)
{
    if (offset == square_matrix.size() - offset - 1)
    {
        // square_matrix has odd dimension, and we are at the center
        // of suqare_matrix.
        spiral_ordering->emplace_back(square_matrix[offset][offset]);
        return;
    }

    for (int j = offset; j < square_matrix.size() - offset - 1; ++j)
    {
        spiral_ordering->emplace_back(square_matrix[offset][j]);
    }
    for (int i = offset; i < square_matrix.size() - offset - 1; ++i)
    {
        spiral_ordering->emplace_back(square_matrix[i][square_matrix.size() - offset - 1]);
    }
    for (int j = offset; j < square_matrix.size() - offset - 1; --j)
    {
        spiral_ordering->emplace_back(square_matrix[square_matrix.size() - offset - 1][j]);
    }
    for (int i = square_matrix.size() - offset - 1; i > offset; --i)
    {
        spiral_ordering->emplace_back(square_matrix[i][offset]);
    }
}

// time complexity: O(n^2)
// space complexity: O(1)
std::vector<int> MatrixInSpiralOrder_EPI(const std::vector<std::vector<int>>& square_matrix) 
{
    std::vector<int> spiral_ordering;
    for (int offset = 0; offset < ceil(0.5 * square_matrix.size()); ++offset)
    {
        MatrixLayerInClockwise(square_matrix, offset, &spiral_ordering);
    }
    return spiral_ordering;
}

// time complexity: O(n^2)
std::vector<int> MatrixInSpiralOrder_EPISingleIter(const std::vector<std::vector<int>>& square_matrix) 
{
    const std::array<std::array<int, 2>, 4> kShift = {{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}};
    int dir = 0, x = 0, y = 0;
    std::vector<int> spiral_ordering;

    for (int i = 0; i < square_matrix.size() * square_matrix.size(); ++i) {
        spiral_ordering.emplace_back(square_matrix[x][y]);
        int next_x = x + kShift[dir][0], next_y = y + kShift[dir][1];
        if (next_x < 0 || next_x >= square_matrix.size() || next_y < 0 ||
            next_y >= square_matrix.size() || square_matrix[next_x][next_y] == 0)
        {
            dir = (dir + 1) % 4;
            next_x = x + kShift[dir][0], next_y = y + kShift[dir][1];
        }
        x = next_x, y = next_y;
    }

    return spiral_ordering;
}

std::vector<int> MatrixInSpiralOrder(const std::vector<std::vector<int>>& square_matrix) 
{
    return MatrixInSpiralOrder_EPISingleIter(square_matrix);
}

// space complexity: O(n^2)
// time complexity: O(n^2)
void RotateMatrix_BF(std::vector<std::vector<int>>* square_matrix_ptr)
{
    std::vector<std::vector<int>>& square_matrix = *square_matrix_ptr;
    std::vector<std::vector<int>> result;
    for (int i = 0; i < square_matrix.size(); ++i) 
    {
        std::vector<int> new_row;
        result.push_back(new_row);
        for (int j = 0; j < square_matrix.size(); ++j)
        {
            result[i].push_back(0);
        }
    }

    for (int i = 0; i < square_matrix.size(); ++i)
    {
        for (int j = 0; j < square_matrix.size(); ++j)
        {
            result[j][square_matrix.size() - 1 - i] = square_matrix[i][j];
        }
    }

    std::swap(result, square_matrix);
}

// space complexity: O(1)
// time complexity: O(n^2)
void RotateMatrix_InPlace(std::vector<std::vector<int>>* square_matrix_ptr)
{
    std::vector<std::vector<int>>& square_matrix = *square_matrix_ptr;

    for (int j = 0; j < square_matrix.size() / 2; ++j)
    {
        for (int i = 0; i < (square_matrix.size() - 1 - j * 2); ++i)
        {
            int temp0 = square_matrix[j][i + j];
            int temp1 = square_matrix[i + j][square_matrix.size() - 1 - j];
            int temp2 = square_matrix[square_matrix.size() - 1 - j][square_matrix.size() - 1 - i - j];
            int temp3 = square_matrix[square_matrix.size() - 1 - i - j][j];
            std::cout << "temps: " << temp0 << ", " << temp1 << ", " << temp2 << ", " << temp3 << std::endl;
            square_matrix[i + j][square_matrix.size() - 1 - j] = temp0;
            square_matrix[square_matrix.size() - 1 - j][square_matrix.size() - 1 - i - j] = temp1;
            square_matrix[square_matrix.size() - 1 - i - j][j] = temp2;
            square_matrix[j][i + j] = temp3;
        }
    }
}

// space complexity: O(1)
// time complexity: O(n^2)
void RotateMatrix_EPI(std::vector<std::vector<int>>* square_matrix_ptr)
{
    std::vector<std::vector<int>>& square_matrix = *square_matrix_ptr;
    const int matrix_size = square_matrix.size() - 1;
    for (int i = 0; i < square_matrix.size() / 2; ++i) {
        for (int j = i; j < matrix_size - i; ++j) {
            // Perform a 4-way exchange
            int temp1 = square_matrix[matrix_size - j][i];
            int temp2 = square_matrix[matrix_size - i][matrix_size - j];
            int temp3 = square_matrix[j][matrix_size - i];
            int temp4 = square_matrix[i][j];
            square_matrix[i][j] = temp1;
            square_matrix[matrix_size - j][i] = temp2;
            square_matrix[matrix_size - i][matrix_size - j] = temp3;
            square_matrix[j][matrix_size - i] = temp4;
        }
    }
}

void RotateMatrix(std::vector<std::vector<int>>* square_matrix_ptr)
{
    RotateMatrix_EPI(square_matrix_ptr);
}

std::vector<std::vector<int>> GeneratePascalTriangle_PW(int num_rows)
{
    std::vector<std::vector<int>> rows;

    if (num_rows == 0)
    {
        return rows;
    }

    std::vector<int> seed = { 1 };
    rows.push_back(seed);
    
    for (size_t i = 1; i < num_rows; i++)
    {
        int row_length = i + 1;
        std::vector<int> new_row(row_length);

        // initialize end points
        new_row[0] = 1;
        new_row[row_length - 1] = 1;
        for (int j = 1; j < row_length - 1; j++)
        {
            int firstOp = rows[i - 1][j - 1] ;
            int secondOp = rows[i - 1][j];
            new_row[j] =  firstOp + secondOp;
        }

        rows.push_back(new_row);
    }

    return rows;

}

// time complexity: O(1 + 2 + ... + n) = O(n(n + 1)/2) = O(n^2)
// space compexity: O(n^2), same reason)
std::vector<std::vector<int>> GeneratePascalTriangle_EPI(int num_rows)
{
    std::vector<std::vector<int>> pascal_triangle;
    for (int i = 0; i < num_rows; ++i) {
        std::vector<int> curr_row;
        for (int j = 0; j <= i; ++j) {
            // Sets this entry to the sum of the two above adjacent entries if they exist.
            curr_row.emplace_back(0 < j && j < i ? pascal_triangle.back()[j - 1] + pascal_triangle.back()[j] : 1);
        }
        pascal_triangle.emplace_back(curr_row);
    }
    return pascal_triangle;
}

std::vector<std::vector<int>> GeneratePascalTriangle(int num_rows)
{
    return GeneratePascalTriangle_EPI(num_rows);
}

// space complexity: O(N), where N is number or rows
// time complexity: O(N^2) = O(N + (N - 1) + (N - 2))
std::vector<int> GeneratePascalRow(int num_rows)
{
    // size of vector == num_rows

    if (num_rows <= 0) return {};
    std::vector<int> row(num_rows);

    row[0] = 1;
    for (int i = 1; i <= num_rows; ++i)
    {
        row[0] = 1;
        row[i - 1] = 1;
        int prev = row[0];
        for (int j = 1; j < i - 1; ++j)
        {
            int temp = row[j];
            row[j] = prev + row[j];
            prev = temp;           
        }
    }

    return row;
}

std::vector<int> runningSum_PW1(std::vector<int>& nums)
{
    std::vector<int> result(nums.size());
    for (int i = 0; i < nums.size(); ++i)
    {
        for (int j = 0; j <= i; ++j)
        {
            result[i] += nums[j];
        }
    }

    return result;
}

std::vector<int> runningSum_PW2(std::vector<int>& nums)
{
    std::vector<int> result;
    std::copy(nums.begin(), nums.end(), std::back_inserter(result));
    std::partial_sum(result.begin(), result.end(), result.begin(), std::plus<int>());
    return result;
}

std::vector<int> runningSum_PW3(std::vector<int>& nums)
{
    std::partial_sum(nums.begin(), nums.end(), nums.begin(), std::plus<int>());
    return nums;
}

std::vector<int> runningSum_PW4(std::vector<int>& nums)
{
    for (int i = 1; i < nums.size(); ++i)
    {
        nums[i] += nums[i - 1];
    }

    return nums;
}

std::vector<int> runningSum(std::vector<int>& nums)
{
    return runningSum_PW4(nums);
}

// space complexity: O(1)
// time complexity: O(N^2)
int numIdenticalPairs_PW(std::vector<int>& nums)
{
    int numPairs = 0;
    for (int i = 0; i < nums.size(); ++i)
    {
        for (int j = i + 1; j < nums.size(); ++j)
        {
            if (nums[i] == nums[j])
            {
                numPairs++;
            }
        }
    }
    return numPairs;
}

// space complexity: O(1)
// time complexity: O(2*N)
int numIdenticalPairs_PW2(std::vector<int>& nums)
{
    std::unordered_map<int, int> counts;
    for (int i = 0; i < nums.size(); ++i)
    {
        counts[nums[i]]++;
    }

    int numPairs = 0;
    for (auto pair: counts)
    {
        int count = pair.second;

        // number of pairs for a given number is equal to to sum of arithmetic sequence
        // think 1,1,1,1 => 3 + 2 + 1
        // 3, 3, 3 => 2 + 1
        // 5, 5, 5, 5, 5 => 4 + 3 + 2 + 1 = ((5) * (4)) / 2
        numPairs += (count) * (count - 1) / 2;
    }

    return numPairs;
}

int numIdenticalPairs(std::vector<int>& nums)
{
    return numIdenticalPairs_PW2(nums);
}

bool isBoomerang(std::vector<std::vector<int>>& points)
{
    auto point0 = points[0];
    auto point1 = points[1];
    auto point2 = points[2];

    auto samePoint = [](std::vector<int> p1, std::vector<int> p2) {
        return p1[0] == p2[0] && p1[1] == p2[1];
    };
    auto undefinedSlope = [](std::vector<int> p1, std::vector<int> p2) {
        return (p2[0] - p1[0]) == 0;
    };
    auto slope = [](std::vector<int> p1, std::vector<int> p2) {
        return (float)(p2[1] - p1[1]) / (float)(p2[0] - p1[0]);
    };

    if (samePoint(point0, point1) || samePoint(point0, point2) || samePoint(point1, point2))
    {
        return false;
    }
    else if (undefinedSlope(point0, point1) && undefinedSlope(point1, point2))
    {
        return false;
    }
    else if (undefinedSlope(point0, point1))
    {
        return true;
    }
    else if (undefinedSlope(point1, point2))
    {
        return true;
    }
    else 
    {
        return slope(point1, point2) != slope(point0, point1);
    }

    return false;
}

std::vector<int> kWeakestRows(std::vector<std::vector<int>>& mat, int k)
{
    std::vector<std::pair<int, int>> rows;
    for (int i = 0; i < mat.size(); ++i)
    {
        int num_soldiers = std::count_if(mat[i].begin(), mat[i].end(), [](int i) {
            return i == 1;
        });

        auto p = std::make_pair(i, num_soldiers);
        rows.push_back(p);
    }

    std::sort(rows.begin(), rows.end(), [](auto a, auto b) {

        if (a.second == b.second) 
        {
            return a.first < b.first;
        }

        return a.second < b.second;
    });
    
    std::vector<int> ordered_rows(k);
    for (int i = 0; i < k; ++i)
    {
        ordered_rows[i] = rows[i].first;
    }

    return ordered_rows;
}

bool isOneBitCharacter(std::vector<int>& bits)
{   
    // 1, 1, 0      => last character must be 0
    // 1, 1, 1, 0   => last character must be 10
    int i = 0;
    bool iActive = false;
    for (; i < bits.size() - 1; i++)
    {
        if (bits[i] == 1)
        {
            if (iActive)
            {
                iActive = false;
            }
            else
            {
                iActive = true;
            }
        }
        else
        { 
            if (iActive)
            {
                iActive = false;
            }
        }
    }

    // zero
    if (!iActive)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// time complexity: O(n + n log n)
// space complexity: O(n)
std::vector<int> addToArrayForm(std::vector<int>& A, int K)
{
    int carry = 0;
    std::vector<int> result;
    int i;
    for (i = 0; K != 0 && i < A.size(); ++i)
    {
        int op1 = K % 10;
        int op2 = A[A.size() - i - 1];
        int sum = (carry + op1 + op2);
        carry = sum / 10;
        sum = sum % 10;
        K /= 10;

        result.push_back(sum);
    }

    // if K still has characters
    while (K)
    {
        int sum = carry + K % 10;
        carry = sum / 10;
        sum = sum % 10;
        result.push_back(sum);
        K /= 10;
    }

    // if A still has characters
    while (i < A.size())
    {
        int sum = carry + A[A.size() - i - 1] % 10;
        carry = sum / 10;
        sum = sum % 10;
        result.push_back(sum);
        i++;
    }

    if (carry)
    {
        result.push_back(carry);
    }

    std::reverse(result.begin(), result.end());

    return result;
}


// time complexity: O(n log n + n)
// space complexity: O(1)
int arrayPairSum(std::vector<int>& nums)
{
    std::sort(nums.begin(), nums.end());

    int sum = 0;
    for (int i = 0; i < nums.size(); i += 2)
    {
        sum += nums[i];
    }

    return sum;
}

// time complexity: O(g log g + s log s + s)
// space complexity: O(1)
int findContentChildren(std::vector<int>& g, std::vector<int>& s)
{
    int j = 0;
    int total = 0;

    std::sort(g.begin(), g.end());
    std::sort(s.begin(), s.end());

    for (int i = 0; i < s.size() && j < g.size(); ++i)
    {
        if (s[i] >= g[j])
        {
            j++;
            total++;
        }
    }

    return total;
}

// time complexity: O(n + n) for time to find pawn, plus time to iterate possible pieces
// space complexity: O(1)
int numRookCaptures(std::vector<std::vector<char>>& board)
{
    int rookRow = 0;
    int rookCol = 0;
    for (int i = 0; i < board.size(); ++i)
    {
        for (int j = 0; j < board.size(); ++j)
        {
            if (board[i][j] == 'R')
            {
                rookRow = i;
                rookCol = j;
                break;
            }
        }
    }

    int pawnCount = 0;

    // top
    for (int i = rookRow; i >= 0; i--)
    {
        if (board[i][rookCol] == 'p')
        {
            pawnCount++;
            break;
        }
        else if (board[i][rookCol] == 'B')
        {
            break;
        }
    }

    // bottom
    for (int i = rookRow; i < board.size(); ++i)
    {
        if (board[i][rookCol] == 'p')
        {
            pawnCount++;
            break;
        }
        else if (board[i][rookCol] == 'B')
        {
            break;
        }
    }

    // left
    for (int i = rookCol; i >= 0; --i)
    {
        if (board[rookRow][i] == 'p')
        {
            pawnCount++;
            break;
        }
        else if (board[rookRow][i] == 'B')
        {
            break;
        }
    }

    // right
    for (int i = rookCol; i < board.size(); ++i)
    {
        if (board[rookRow][i] == 'p')
        {
            pawnCount++;
            break;
        }
        else if (board[rookRow][i] == 'B')
        {
            break;
        }
    }

    return pawnCount;
}

// time complexity: O(n log n + n)
// space complexity: O(n)
int thirdMax_BF(std::vector<int>& nums)
{
    std::set<int> unique_nums;
    for (int i = 0; i < nums.size(); ++i)
    {
        unique_nums.insert(nums[i]);
    }

    auto iter = unique_nums.end();
    if (unique_nums.size() < 3)
    {
        return *(--iter);
    }
    else 
    {
        int count = 3;
        while (count--)
        {
            iter--;
        }
        return *(iter);
    }
}

// space complexity: O(1)
// time complexity: O(n log n + n log n + n)
int thirdMax_PW2(std::vector<int>& nums)
{
    std::sort(nums.begin(), nums.end());
    auto last = std::unique(nums.begin(), nums.end());
    nums.erase(last, nums.end());
    
    if (nums.size() < 3)
    {
        return nums[nums.size() - 1];
    }
    else
    {
        return nums[nums.size() - 3];
    }
}

// space complexity: O(1)
// time complexity: O(n + n log n)
int thirdMax_PW3(std::vector<int>& nums)
{
    std::sort(nums.begin(), nums.end());
    auto first = nums[0],
         second = first,
         third = first;
    
    int count = 1;
    for (int i = 1; i < nums.size(); ++i)
    {
        if (nums[i] > first)
        {
            third = second;
            second = first;
            first = nums[i];
            count++;
        }
        else if (nums[i] > second && nums[i] != first)
        {
            third = second;
            second = nums[i];
            count++;
        }
        else if (nums[i] > third && nums[i] != first && nums[i] != second)
        {
            third = nums[i];
            count++;
        }
    }

    if (count < 3)
    {
        return first;
    }
    else 
    {
        return third;
    }
}

// space complexity: O(1)
// time complexity: O(n)
int thirdMax_PW4(std::vector<int>& nums)
{
    auto first = std::numeric_limits<int>::min(),
         second = first,
         third = first;
    
    int count = 0;
    bool minFlag = false;
    for (int i = 0; i < nums.size(); ++i)
    {
        if (nums[i] > first)
        {
            third = second;
            second = first;
            first = nums[i];
            count++;
        }
        else if (nums[i] > second && nums[i] != first)
        {
            third = second;
            second = nums[i];
            count++;
        }
        else if (nums[i] > third && nums[i] != first && nums[i] != second)
        {
            third = nums[i];
            count++;
        }
        else if (nums[i] == std::numeric_limits<int>::min())
        {
            minFlag = true;
        }
    }

    if (minFlag) 
    {
        count++;
    }

    if (count < 3)
    {
        return first;
    }
    else 
    {
        return third;
    }
}

int thirdMax(std::vector<int>& nums)
{
    return thirdMax_PW4(nums);
}

// time complexity: O(2 * n)
// space comlexity: O(n)
bool canPlaceFlowers_PW1(std::vector<int>& flowerbed, int n)
{
    std::vector<int> toBeTaken(flowerbed.size());
    for (int i = 0; i < flowerbed.size(); ++i)
    {   
        // is left valid, check taken, or to be taken
        if (flowerbed[i])
        {
            continue;
        }
        if ((i - 1 < 0 || ((i-1) >= 0 && !(flowerbed[i-1] || toBeTaken[i - 1]))) &&
            (i + 1 >= flowerbed.size() || ((i+1) < flowerbed.size() && !(flowerbed[i+1] || toBeTaken[i + 1]))))
        {
            toBeTaken[i] = 1;
        }
        else
        {
            toBeTaken[i] = 0;
        }
    }

    int maxCount = std::count_if(toBeTaken.begin(), toBeTaken.end(), [](int i) {
        return i == 1;
    });

    return maxCount >= n;
}

// time complexity: O(n)
// space comlexity: O(1)
bool canPlaceFlowers_PW2(std::vector<int>& flowerbed, int n)
{
    int maxCount = 0;
    for (int i = 0; i < flowerbed.size(); ++i)
    {   
        // is left valid, check taken, or to be taken
        if (flowerbed[i])
        {
            continue;
        }
        else if (
            (i - 1 < 0 || !(flowerbed[i-1])) &&
            (i + 1 >= flowerbed.size() || !flowerbed[i+1])
        )
        {
            flowerbed[i] = 1;
            maxCount++;
        }
        else
        {
            // do nothing
        }
    }

    return maxCount >= n;
}

// time complexity: O(2 * n)
// space comlexity: O(n)
bool canPlaceFlowers(std::vector<int>& flowerbed, int n)
{
    return canPlaceFlowers_PW2(flowerbed, n);
}

// time complexity: O(n)
// space complexity: O(1)
bool validMountainArray_PW1(std::vector<int>& arr)
{
    enum class SearchState
    {
        NONE,
        ASCENT,
        FOUND_PEAK,
        DESCENT
    };

    SearchState state = SearchState::ASCENT;
    int curMax = arr[0];
    int ascentSize = 0;
    int curMin = std::numeric_limits<int>::max();

    if (arr.size() < 3)
    {
        return false;
    }
    
    for (int i = 1; i < arr.size(); ++i)
    {
        if (state == SearchState::ASCENT && arr[i] > arr[i - 1])
        {
            ascentSize++;
            continue;
        }
        else if (state == SearchState::ASCENT && arr[i] < arr[i - 1])
        {
            state = SearchState::DESCENT;
        }
        else if (state == SearchState::ASCENT && arr[i] == arr[i - 1])
        {
            return false;
        }
        else if (state == SearchState::DESCENT && arr[i] >= arr[i - 1])
        {
            return false;
        }
    }

    if (state != SearchState::DESCENT || !ascentSize)
    {
        return false;
    }
    
    return true;
}

// time complexity: O(n)
// space complexity: O(1)
bool validMountainArray_PW2(std::vector<int>& arr)
{
    if (arr.size() < 3)
    {
        return false;
    }

    int i = 1;

    // walk up
    while (i < arr.size() && arr[i] > arr[i - 1])
    {
        i++;
    }

    if (i == 1 || i == arr.size())
    {
        return false;
    }

    // walk down
    while (i < arr.size() && arr[i] < arr[i - 1])
    {
        i++;
    }

    return i == arr.size();
}

bool validMountainArray(std::vector<int>& arr)
{
    return validMountainArray_PW2(arr);
}

void factors(int num, std::map<int, int>& fs)
{
    for (int i = 1; i <= num; ++i)
    {
        if (num % i == 0 && i >= 2)
        {
            fs[i]++;
        }
    }
}

// space complexity: O(n)
// time complexity: O(n)
bool hasGroupsSizeX(std::vector<int>& deck)
{
    std::unordered_map<int, int> count;
    for (int i = 0; i < deck.size(); ++i)
    {
        count[deck[i]]++;
    }

    // get set of factors for all card counts
    std::map<int, int> fs;
    for (auto pair: count)
    {
        factors(pair.second, fs);
    }

    // find the gcd, this represents number of cards in each group
    for (auto it = fs.rbegin(); it != fs.rend(); it++)
    {
        if (it->second == count.size())
        {
            return true;
        }
    }

    return false;
}

// time complexity: O(n)
// space complexity: O(1)
double average(std::vector<int>& salary)
{
    int max = std::numeric_limits<int>::min();
    int min = std::numeric_limits<int>::max();
    int sum = 0;

    for (int i = 0; i < salary.size(); ++i)
    {
        if (salary[i] > max)
        {
            max = salary[i];
        }
        if (salary[i] < min)
        {
            min = salary[i];
        }

        sum += salary[i];
    }

    sum -= max;
    sum -= min;

    return (double)sum / (double)(salary.size() - 2);
}

// time complexity: O(n)
// space complexity: O(n)
int calPoints(std::vector<std::string>& ops)
{
    std::vector<int> records;
    for (auto op: ops)
    {
        if (op == "C")
        {
            records.pop_back();
        }
        else if (op == "+")
        {
            int i = records.size() - 1;
            records.push_back(records[i] + records[i - 1]);
        }
        else if (op == "D")
        {
            int i = records.size() - 1;
            records.push_back(records[i] * 2);
        }
        else
        {
            records.push_back(std::stoi(op));
        }
    }

    return std::accumulate(records.begin(), records.end(), 0);
}

// time complexity: O(n)
// space complexity: O(1)
int maxProfit(std::vector<int>& prices)
{
    int profit = 0;
    if (prices.empty())
    {
        return 0;
    }
    int curMin = prices[0];
    int curMax = prices[0];
    int maxIdx = 0, minIdx = 0;
    for (int i = 0; i < prices.size(); ++i)
    {
        if (prices[i] < curMax && maxIdx > minIdx)
        {
            profit += curMax - curMin;
            curMin = prices[i];
            curMax = prices[i];
            maxIdx = i;
            minIdx = i;
        }
        else if (prices[i] < curMin)
        {
            curMin = prices[i];
            curMax = prices[i];
            minIdx = i;
        }
        else if (prices[i] > curMax)
        {
            curMax = prices[i];
            maxIdx = i;
        }
    }

    if (maxIdx > minIdx)
    {
        profit += curMax - curMin;
    }

    return profit;
}

// time complexity: O(1)
// space complexity: O(n)
std::vector<bool> prefixesDivBy5(std::vector<int>& A)
{
    std::vector<bool> results;
    int num = 0;
    for (int i = 0; i < A.size(); ++i)
    {
        num <<= 1;
        num += A[i];
        results.push_back(num % 5 == 0);

        // confusing part, how does it work? Walk through a few examples.
        //  main idea: effect of multiplying x by 2, adding 1 will have same relationship to 5, as x mod 5
        //  example: x = 7, x mod 5 = 2, x * 2 + 1 = 15 (divisible by 5), x mod 5 * 2 + 1 = 5 (divisible by 5)
        //  example: x = 4, x mod 3 = 1, x * 2 + 1 = 9 (divisible by 3), x mod 3 * 2 + 1 = 3 (divisible by 3)
          
        num %= 5;
    }
    
    return results;
}


// space comlexity: O(n * log n)
// time complexity: O(log n)
int search_PW1(std::vector<int>& nums, int target)
{
    if (nums.size() == 1 && nums[0] != target)
    {
        return -1;
    }   
    else if (nums[nums.size() / 2] == target)
    {
        return nums.size() / 2;
    }
    else if (nums[nums.size() / 2] > target)
    {
        std::vector<int> lesser;
        std::copy(nums.begin(), nums.begin() + nums.size() / 2, std::back_inserter(lesser));
        int idx = search(lesser, target);
        if (idx == -1) return -1;
        return idx;
    }
    else
    {
        std::vector<int> greater;
        std::copy(nums.begin() + nums.size() / 2, nums.end(), std::back_inserter(greater));
        int idx = search(greater, target);
        if (idx == -1) return -1;
        return nums.size() / 2 + idx;
    }
}

int search_recurse(std::vector<int>& nums, int target, int l, int r)
{
    int index = (r - l) / 2 + l;
    if (r <= l)
    {
        return nums[l] == target ? l : -1;
    }
    else if (nums[index] == target)
    {
        return index;
    }
    else if (nums[index] > target)
    {
        return search_recurse(nums, target, l, index - 1);
    }
    else 
    {
        return search_recurse(nums, target, index + 1, r);
    }
}

// space comlexity: O(1)
// time complexity: O(log n)
int search_PW2(std::vector<int>& nums, int target)
{
    return search_recurse(nums, target, 0, nums.size() - 1);
}

// space comlexity: O(n * log n)
// time complexity: O(log n)
int search(std::vector<int>& nums, int target)
{
    return search_PW2(nums, target);
}

// time complexity: O(n log n + n)
// space complexity: O(1)
bool canMakeArithmeticProgression(std::vector<int>& arr)
{
    std::sort(arr.begin(), arr.end());
    if (arr.size() <= 2)
    {
        return true;
    }
    int diff = arr[1] - arr[0];
    for (int i = 2; i < arr.size(); i++)
    {
        if ((arr[i] - arr[i - 1]) != diff)
        {
            return false;
        }
    }
    return true;
}

// time complexity: O((n + m) * i + n * m)
// space complexity: O(n * m)
int oddCells(int n, int m, std::vector<std::vector<int>>& indices)
{
    std::vector<int> values(n * m, 0);
    for (auto index: indices)
    {
        // row
        int row = index[0];
        int col = index[1];
        for (int i = 0; i < m; ++i)
        {
            values[row * m + i] += 1;
        }

        for (int j = 0; j < n; ++j)
        {
            values[j * m + col] += 1;
        }
    }

    int numOdds = 0;
    for (int i = 0; i < values.size(); ++i)
    {
        if (values[i] % 2 == 1)
        {
            numOdds++;
        }
    }

    return numOdds;
}

// time complexity: O(n * m * k), where n is size of arr, m is size of pieces, k is average size of piece
// space complexity: O(m), same size as pieces
bool canFormArray(std::vector<int>& arr, std::vector<std::vector<int>>& pieces)
{
    std::vector<int> used(pieces.size());
    int i = 0;
    bool foundPiece = false;
    for (int i = 0; i < arr.size(); )
    {
        for (int j = 0; j < pieces.size() && i < arr.size(); ++j)
        {
            if (arr[i] == pieces[j][0] && !used[j])
            {
                foundPiece = true;
                for (int k = 0; k < pieces[j].size(); ++k)
                {
                    if (arr[i] != pieces[j][k])
                    {
                        return false;
                    }

                    i++;
                }

                used[j] = 1;
            }
        }
        
        if (!foundPiece && i <= arr.size() - 1)
        {
            return false;
        }

        foundPiece = false;
    }
    return true;
}

// time complexity: O(n)
// space complexity: O(1)
bool kLengthApart(std::vector<int>& nums, int k)
{
    int lastOne = -1;
    for (int i = 0; i < nums.size(); ++i)
    {
        if (nums[i] == 1 && lastOne == -1)
        {
            lastOne = i;
        }
        else if (nums[i] == 1)
        {
            if (i - lastOne - 1 < k)
            {
                return false;
            }

            lastOne = i;
        }
    }

    return true;
}

// time complexity: O(n)
// space complexity: O(1)
bool checkStraightLine(std::vector<std::vector<int>>& coordinates)
{
    if (coordinates.size() < 2)
    {
        return false;
    }

    int denom = coordinates[1][0] - coordinates[0][0];
    int num   = coordinates[1][1] - coordinates[0][1];

    float slope = 0;
    if (denom)
    {
        slope = (float)num / (float)denom;
    }

    for (int i = 2; i < coordinates.size(); ++i)
    {
        int curDenom = coordinates[i][0] - coordinates[i-1][0];
        int curNum = coordinates[i][1] - coordinates[i-1][1];

        if (!denom && curDenom)
        {
            return false;
        }
        else if (denom && !curDenom)
        {
            return false;
        }
        else if (denom && slope != ((float)curNum / (float)curDenom))
        {
            return false;
        }
    }

    return true;
}

// time complexity: O(N^2)
// space complexity: O(1)
bool checkIfExist(std::vector<int>& arr)
{          
    for (int i = 0; i < arr.size() - 1; ++i)
    {
        for (int j = i + 1; j < arr.size(); ++j)
        {
            if (arr[j] == 2 * arr[i] || arr[i] == 2 * arr[j])
            {
                return true;
            }
        }
    }
    
    return false;
}

// time complexity: O(n)
// space complexity: O(1)
bool check(std::vector<int>& nums)
{
    bool startFound = false;
    int first = nums[0];
    for (int i = 1; i < nums.size(); ++i)
    {
        if (nums[i] < nums[i - 1] && !startFound)
        {
            if (nums[i] > first)
            {
                return false;
            }

            startFound = true;
        }
        else if (nums[i] < nums[i - 1] && startFound)
        {
            return false;
        }
        else if (startFound && nums[i] > first) // weird condition
        {
            return false;
        }
    }

    return true;
}

// time complexity: O(sqrt(n))
// space complexity: O(1)
std::vector<int> constructRectangle(int area)
{  
    for (int i = floor(sqrt(area)); i > 0; --i)
    {
        if (area % i == 0)
        {
            return {area / i, i};
        }
    }

    return {};
}

// time complexity: O(n * log n)
// space complexity: O(2n), n for n elements in set, indices across all n elements
bool containsNearbyDuplicate(std::vector<int>& nums, int k)
{
    std::unordered_map<int, std::set<int>> m;

    for (int i = 0; i < nums.size(); ++i)
    {
        if (m.find(nums[i]) == m.end())
        {
            m[nums[i]] = { i };
        }
        else
        {
            if (i - (*m[nums[i]].rbegin()) <= k)
            {
                return true;
            }

            m[nums[i]].insert(i);
        }
    }

    return false;
}

// time complexity: O(n)
// space complexity: O(1)
int countMatches_PW1(std::vector<std::vector<std::string>>& items, std::string ruleKey, std::string ruleValue)
{
    int index = -1;
    if (ruleKey == "type") index = 0;
    else if (ruleKey == "color") index = 1;
    else if (ruleKey == "name") index = 2;

    int count = 0;
    for (auto item: items)
    {
        if (item[index] == ruleValue)
        {
            count++;
        }
    }
    return count;
}

// time complexity: O(n)
// space complexity: O(1)
int countMatches_PW2(std::vector<std::vector<std::string>>& items, std::string ruleKey, std::string ruleValue)
{
    int index = -1;
    if (ruleKey == "type") index = 0;
    else if (ruleKey == "color") index = 1;
    else if (ruleKey == "name") index = 2;

    return std::count_if(items.begin(), items.end(), [&](const std::vector<std::string>& s) {
        return s[index] == ruleValue;
    });
}

int countMatches(std::vector<std::vector<std::string>>& items, std::string ruleKey, std::string ruleValue)
{
    return countMatches_PW2(items, ruleKey, ruleValue);
}

// time complexity: O(n x m)
// space complexity: O(1)
int countNegatives(std::vector<std::vector<int>>& grid)
{
    int count = 0;
    for (int i = 0; i < grid.size(); ++i)
    {
        for (int j = grid[i].size() - 1; j >= 0; --j)
        {
            if (grid[i][j] >= 0)
            {
                break;
            }
            else
            {
                count++;
            }
        }
    }

    return count;
}

// time complexity: O(n*n-1), worst case each insert requires a shift e.g. index = {0, 0, 0, 0, 0}
// space complexity: O(n)
std::vector<int> createTargetArray(std::vector<int>& nums, std::vector<int>& index)
{
    std::vector<int> result(nums.size(), -1);
    for (int i = 0; i < index.size(); ++i)
    {
        int idx = index[i];
        if (result[idx] != -1)
        {
            for (int j = result.size() - 1; j > idx; j--)
            {
                result[j] = result[j - 1];
            }
            result[idx] = nums[i];
        }
        else
        {
            result[idx] = nums[i];
        }
    }

    return result;
}

// time complexity: O(n)
// space complexity: O(1)
int minOperations(std::vector<std::string>& logs)
{
    int minSteps = 0;
    for (auto log: logs)
    {
        if (log[0] != '.')
        {
            minSteps++;
        }
        else if (log[0] == '.' && log[1] == '.')
        {
            if (minSteps == 0)
            {
                // already at main folder
                continue;
            }

            minSteps--;
        }
        else
        {
            // ./ => no change
        }
    }

    return minSteps;
}

// time complexity: O(n)
// space complexity: O(n) (return string)
std::vector<int> diStringMatch(std::string S)
{
    std::vector<int> result;
    int leftCounter = 0;
    int rightCounter = S.size();

    for (int i = 0; i < S.size(); ++i)
    {
        if (S[i] == 'I')
        {
            result.emplace_back(leftCounter++);            
        }
        else
        {
            result.emplace_back(rightCounter--);
        }
    }

    if (leftCounter < rightCounter)
    {
        result.emplace_back(leftCounter);
    }
    else 
    {
        result.emplace_back(rightCounter);
    }

    return result;
}

// time complexity: O(n)
// space complexity: O(n)
std::vector<int> decode(std::vector<int>& encoded, int first)
{
    std::vector<int> result;
    result.emplace_back(first);

    for (int i = 0; i < encoded.size(); ++i)
    {
        result.emplace_back(encoded[i] ^ result[i]);
    }

    return result;
}

// time complexity: O(m), where m is length of result
// space complexity: O(m)
std::vector<int> decompressRLElist(std::vector<int>& nums)
{
    std::vector<int> result;
    for (int i = 0; i < nums.size(); i += 2)
    {
        for (int j = 0; j < nums[i]; j++)
        {
            result.push_back(nums[i + 1]);
        }
    }

    return result;
}

// time complexity: O(n + 2*n log 2*n), where n is number of pairs
// space complexity: O(2*n)
std::string destCity(std::vector<std::vector<std::string>>& paths)
{
    std::set<std::string> destinations;
    std::set<std::string> starts;

    for (auto pair: paths)
    {
        destinations.insert(pair[1]);
        starts.insert(pair[0]);
    }

    std::string finalDest = "";
    for (auto dest: destinations)
    {
        if (starts.find(dest) == starts.end())
        {
            finalDest = dest; 
            break;
        }
    }

    return finalDest;
}

// time complexity: O(n^3)
// space complexity: O(1)
int countGoodTriplets(std::vector<int>& arr, int a, int b, int c)
{
    int count = 0;
    for (int i = 0; i < arr.size() - 2; ++i)
    {
        for (int j = i + 1; j < arr.size() - 1; ++j)
        {
            if (std::abs(arr[j] - arr[i]) > a)
            {
                continue;
            }

            for (int k = j + 1; k < arr.size(); ++k)
            {
                if (std::abs(arr[k] - arr[j]) > b || (std::abs(arr[k] - arr[i]) > c))
                {
                    continue;
                }

                count++;
            }
        }
    }

    return count;
}

// time complexity: O(n * k)
// space complexity: O(n)
std::vector<int> decrypt(std::vector<int>& code, int k)
{
    std::vector<int> result(code.size(), 0);

    if (k > 0)
    {
        for (int i = 0; i < code.size(); ++i)
        {
            for (int j = i + 1; j <= i + k; j++)
            {
                result[i] += code[j % code.size()];
            }
        }
    }
    else if (k == 0)
    {
        // do nothing
    }
    else
    {
        for (int i = 0; i < code.size(); ++i)
        {
            for (int j = i - 1; j >= i + k; j--)
            {
                int idx = j;
                if (idx < 0) idx = code.size() - std::abs(idx);
                result[i] += code[idx];
            }
        }
    }


    return result;
}

// time complexity: O(n + n + n * k), where k is number of elements which have same degree
// space complexity: O(n + 2*n), extra n is for maxElements and maxValues
int findShortestSubArray_PW1(std::vector<int>& nums)
{
    std::unordered_map<int, int> count;
    for (auto num: nums)
    {
        count[num]++;
    }

    int maxElement = count.begin()->first;
    int maxValue = count.begin()->second;

    std::vector<int> maxElements;
    std::vector<int> maxValues;
    maxElements.push_back(maxElement);
    maxValues.push_back(maxValue);

    for (auto pair: count)
    {
        if (pair.second > maxValue)
        {
            maxElements.clear();
            maxValues.clear();
             
            maxElement = pair.first;
            maxValue = pair.second;
            maxElements.push_back(maxElement);
            maxValues.push_back(maxValue);
        }
        else if (pair.second == maxValue && pair.first != maxElement)
        {
            maxElements.push_back(pair.first);
            maxValues.push_back(pair.second);
        }
    }

    int shortestArray = std::numeric_limits<int>::max();

    for (size_t i = 0; i < maxElements.size(); ++i)
    {
        int maxElement = maxElements[i];

        int startIdx = 0;
        int endIdx = nums.size() - 1;

        while (nums[startIdx] != maxElement) startIdx++;
        while (nums[endIdx] != maxElement) endIdx--;

        shortestArray = std::min(shortestArray, endIdx + 1 - startIdx);
    }


    return shortestArray;
}

// time complexity: O(n)
// space complexity: O(n) (count, left, right)
int findShortestSubArray_PW2(std::vector<int>& nums)
{
    std::unordered_map<int, int> count, left, right;
    size_t i = 0;
    for (auto num: nums)
    {
        count[num]++;
        right[num] = i;

        if (left.find(num) == left.end())
        {
            left[num] = i;
        }

        i++;
    }

    int maxElement = count.begin()->first;
    int maxValue = count.begin()->second;

    int degree = 0;

    for (auto pair: count)
    {
        if (pair.second > degree)
        {
            degree = pair.second;
        }
    }

    int shortestArray = std::numeric_limits<int>::max();

    for (auto pair: count)
    {
        if (pair.second == degree)
            shortestArray = std::min(right[pair.first] + 1 - left[pair.first], shortestArray);
    }


    return shortestArray;
}

int findShortestSubArray(std::vector<int>& nums)
{
    return findShortestSubArray_PW2(nums);
}

// time complexity: O(m * n), where is m is number of strings and n is size of each string
// space complexity: O(1)
int minDeletionSize(std::vector<std::string>& strs)
{
    int count = 0;
    for (int i = 0; i < strs[0].size(); ++i)
    {
        for (int j = 1; j < strs.size(); ++j)
        {
            if (strs[j][i] < strs[j - 1][i]) 
            {
                count++;
                break;
            }
        }
    }

    return count;
}

// time complexity: O(n)
// space complexity: O(n)
bool containsPattern(std::vector<int>& arr, int m, int k)
{
    std::vector<int> pattern;
    int count = 0;

    for (int i = 0; i < arr.size(); ++i)
    {
        if (pattern.empty())
        {
            count = 0;
            for (int j = i; j < i + m; j++)
            {
                if (j >= arr.size()) { return false; }

                pattern.push_back(arr[j]);
            }

            count++;
        }

        for (int j = i + m; j < arr.size(); j += m)
        {
            bool foundPattern = true;
            for (int l = 0; l < m; l++)
            {
                if ((l + j) >= arr.size()) 
                {
                    foundPattern = false;
                    break;
                }

                if (arr[l + j] != pattern[l]) 
                {
                    foundPattern = false;
                    break;
                }
            }

            if (foundPattern) 
            {
                count++;
            }
            else
            {
                break;
            }
        }

        if (count < k) pattern.clear();
        else { break; }
    }

    return count >= k;
}

// time complexity: O(n^2)
// space complexity: O(n)
std::vector<int> finalPrices(std::vector<int>& prices)
{
    std::vector<int> result(prices.size());
    for (int i = 0; i < prices.size(); ++i)
    {
        result[i] = prices[i];
        for (int j = i + 1; j < prices.size(); ++j)
        {
            if (prices[j] <= prices[i])
            {
                result[i] -= prices[j];
                break;
            }
        }
    }
    
    return result;
}

// space complexity: O(n)
// time complexity: O(n)
int distributeCandies_PW1(std::vector<int>& candyType)
{
    std::set<int> types;

    for (auto type: candyType)
    {
        types.insert(type);
    }

    return std::min(types.size(), candyType.size() / 2);
}

// space complexity: O(1)
// time complexity: O(n log n + n)
int distributeCandies_PW2(std::vector<int>& candyType)
{
    std::sort(candyType.begin(), candyType.end());
    int numTypes = 1;
    for (int i = 1; i < candyType.size(); ++i)
    {
        if (candyType[i] != candyType[i - 1])
        {
            numTypes++;
        }
    }

    int half = candyType.size() / 2;
    return std::min(numTypes, half);
}

int distributeCandies(std::vector<int>& candyType)
{
    return distributeCandies_PW2(candyType);
}

// time complexity: O(n)
// space complexity: O(n)
std::vector<int> distributeCandies(int candies, int num_people) 
{
    std::vector<int> result(num_people);

    int i = 1;
    while (candies)
    {
        result[(i - 1) % num_people] += std::min(i, candies);
        candies -= i;
        if (candies <= 0) break;
        i++;
    }

    return result;
}

// time complexity: O(n)
// space complexity: O(1)
int distanceBetweenBusStops(std::vector<int>& distance, int start, int destination)
{
    int forward = 0;
    int i = start;
    while (i != destination)
    {
        forward += distance[i];
        i++;
        if (i >= distance.size())
        {
            i = 0;
        }
    }

    int backward = 0;
    i = start;
    while (i != destination)
    {
        backward += distance[i > 0 ? i - 1 : distance.size() - 1];
        i--;
        if (i < 0)
        {
            i = distance.size() - 1;
        }
    }

    return std::min(forward, backward);
}

// time complexity: O(n^2)
// space complexity: O(1)
void duplicateZeros_PW1(std::vector<int>& arr)
{
    for (int i = 0; i < arr.size(); ++i)
    {
        if (!arr[i])
        {
            for (int j = arr.size() - 1; j > i; j--)
            {
                arr[j] = arr[j - 1];
            }
            
            if (i < arr.size() - 1)
            {
                arr[i + 1] = 0;
            }

            i++;
        }
    }
}

// time complexity: O(n)
// space complexity: O(1)
void duplicateZeros_PW2(std::vector<int>& arr)
{
    int possibleDups = 0;
    int length_ = arr.size() - 1;

    // Find number of zeros to be duplicated
    for (int left = 0; left <= length_ - possibleDups; left++)
    {
        if (arr[left] == 0) {
            if (left == length_ - possibleDups) {
                arr[length_] = 0;
                length_ -= 1;
                break;
            }
            possibleDups++;
        }
    }

    // Start backwards from the last element which would be part of 
    // new array
    int last = length_ - possibleDups;

    // Copy zero twice, and non-zero once.
    for (int i = last; i >= 0; i--)
    {
        if (arr[i] == 0)
        {
            arr[i + possibleDups] = 0;
            possibleDups--;
            arr[i + possibleDups] = 0;
        }
        else
        {
            arr[i + possibleDups] = arr[i];
        }
    }
}

void duplicateZeros(std::vector<int>& arr)
{
    duplicateZeros_PW2(arr);
}

// time complexity: O(n)
// space complexity: O(n)
std::vector<int> sumZero(int n)
{
    std::vector<int> result;
    for (int i = 1; i <= n / 2; i++)
    {
        result.push_back(i);
        result.push_back(-i);
    }

    if (n % 2 == 1) result.push_back(0);
    return result;
}

// time complexity: O(n log n * n)
// space complexity: O(n), recursive
int getImportance(std::vector<Employee*> employees, int id)
{
    auto it = std::find_if(employees.begin(), employees.end(), [id](Employee* employee){
        return employee->id == id;
    });

    auto e_fold = [&employees](int i, int e) {
        return i + getImportance(employees, e);
    };
 
    return (*it)->importance + std::accumulate((*it)->subordinates.begin(), (*it)->subordinates.end(), 0, e_fold);
}

// time complexity: O(n)
// space complexity: O(1)
int findSpecialInteger(std::vector<int>& arr)
{
    int curCount = 1;
    for (int i = 1; i < arr.size(); ++i)
    {
        if (arr[i] == arr[i - 1])
        {
            curCount++;
            if (((float)curCount / (float)arr.size()) > 0.25)
            {
                return arr[i];
            }
        }
        else
        {
            curCount = 1;
        }
    }
    return arr[0];
}

// time complexity: O(A.length + B.length)
// space complexity: O(B.length)
std::vector<int> fairCandySwap(std::vector<int>& A, std::vector<int>& B)
{
    std::vector<int> result;

    int aSize = std::accumulate(A.begin(), A.end(), 0);
    int bSize = std::accumulate(B.begin(), B.end(), 0);
    int diff = (bSize - aSize) / 2;

    std::unordered_set<int> bSet;
    for (int i = 0; i < B.size(); ++i)
    {
        bSet.insert(B[i]);
    }

    for (auto bar: A)
    {
        if (bSet.find(bar + diff) != bSet.end())
        {
            result.push_back(bar);
            result.push_back(*bSet.find(bar+diff));
            return result;
        }
    }
    return result;
}

// time complexity: O(n log n + n)
// space complexity: O(1)
int findLucky(std::vector<int>& arr)
{
    if (arr.empty()) return -1;

    int curFreq = 1;
    int lucky = -1;

    std::sort(arr.begin(), arr.end());

    for (int i = 1; i < arr.size(); ++i)
    {
        if (arr[i] != arr[i - 1])
        {
            if (curFreq == arr[i - 1])
            {
                lucky = arr[i - 1];
            }

            curFreq = 1;
        }
        else
        {
            curFreq++;
        }
    }

    if (curFreq == arr[arr.size() - 1])
    {
        lucky = arr[arr.size() - 1];
    }

    return lucky;
}

// time complexity: O(n)
// space complexity: O(1)
std::vector<int> findDisappearedNumbers(std::vector<int>& nums)
{
    std::vector<int> disappeared;
    std::sort(nums.begin(), nums.end());

    for (int k = 1; k < nums[0]; ++k)
    {
        disappeared.push_back(k);
    }

    for (int i = 1; i < nums.size(); ++i)
    {
        if (nums[i] == nums[i - 1])
        {
            // continue
        }
        else if (nums[i] != nums[i - 1])
        {
            for (int k = nums[i - 1] + 1; k < nums[i]; ++k)
            {
                disappeared.push_back(k);
            }
        }
    }

    for (int k = nums[nums.size() - 1] + 1; k <= nums.size(); ++k)
    {
        disappeared.push_back(k);
    }

    return disappeared;
}

// time complexity: O(n)
// space complexity: O(1)
int findNumbers(std::vector<int>& nums)
{
    int numEven = 0;

    auto findDigits = [](int num) {
        int numDigits = 0;
        while (num)
        {
            numDigits++;
            num /= 10;
        }
        return numDigits;
    };

    for (int i = 0; i < nums.size(); ++i)
    {
        if (findDigits(nums[i]) % 2 == 0) 
        {
            numEven++;
        }
    }

    return numEven;
}

// time complexity: O(1)
// space complexity: O(1)
int nearestValidPoint(int x, int y, std::vector<std::vector<int>>& points)
{
    int manhattanDistance = std::numeric_limits<int>::max();
    int index = -1;
    for (int i = 0; i < points.size(); ++i)
    {
        if (x == points[i][0] || y == points[i][1])
        {
            int dist = sqrt(pow(abs(x - points[i][0]), 2) + pow(abs(y - points[i][1]), 2));
            if (dist < manhattanDistance)
            {
                index = i;
            }
            manhattanDistance = std::min(dist, manhattanDistance);
        }
    }
    return index;
}

// time complexity: O(n)
// space complexity: O(1)
int largestAltitude(std::vector<int>& gain)
{
    int maxAlt = 0;
    int curAlt = 0;
    for (int i = 0; i < gain.size(); ++i)
    {
        curAlt += gain[i];
        maxAlt = std::max(maxAlt, curAlt);
    }
    return maxAlt;
}

// time complexity: O(N)
// space complexity: O(1)
std::vector<std::vector<int>> flipAndInvertImage(std::vector<std::vector<int>>& image)
{
    for (int i = 0; i < image.size(); ++i)
    {
        int max = round((float)image[i].size() / (float)2);
        for (int j = 0; j < max; ++j)
        {
            std::swap(image[i][j], image[i][image[i].size() - 1 - j]);
            image[i][image[i].size() - 1 - j] = !image[i][image[i].size() - 1 - j];

            if (j != (image[i].size() - 1 - j))
            {
                image[i][j] = !image[i][j];
            }
        }
    }
    return image;
}

// time complexity: O(n)
// space complexity: O(1)
char nextGreatestLetter_PW1(std::vector<char>& letters, char target)
{
    int diff = std::numeric_limits<int>::max();
    char c = target;
    int currentDiff;
    for (int i = 0; i < letters.size(); ++i)
    {
        currentDiff = letters[i] >= target ? letters[i] - target : letters[i] + 'z' + 1 - target;
        if (letters[i] != target && currentDiff < diff)
        {
            diff = std::min(diff, currentDiff);
            c = letters[i];
        }
    }

    return c;
}

// time complexity: O(n)
// space complexity: O(1)
char nextGreatestLetter_PW2(std::vector<char>& letters, char target)
{
    std::vector<bool> seen(26, false);
    for (char c: letters)
        seen[c - 'a'] = true;

    while (true) 
    {
        target++;
        if (target > 'z') target = 'a';
        if (seen[target - 'a']) return target;
    }
}

char nextGreatestLetter(std::vector<char>& letters, char target)
{
    return nextGreatestLetter_PW2(letters, target);
}

// time complexity: O(m * n)
// space complexity: O(1)
int findTheDistanceValue(std::vector<int>& arr1, std::vector<int>& arr2, int d)
{
    int distance = 0;
    for (int i = 0; i < arr1.size(); ++i)
    {
        bool foundMatch = false;
        for (int j = 0; j < arr2.size(); ++j)
        {
            if (abs(arr1[i] - arr2[j]) > d)
            {
                continue;
            }
            else
            {
                foundMatch = true;
                break;
            }
        }
        if (!foundMatch)
        {
            distance++;
        }
    }
    return distance;
}

// time complexity: O(2 * n)
// space complexity: O(2 * n)
int findJudge_PW1(int N, std::vector<std::vector<int>>& trust)
{
    std::vector<int> trusted(N);
    std::vector<int> trusts(N);

    for (auto pair: trust)
    {
        trusted[pair[1]-1]++;
        trusts[pair[0]-1]++;
    }

    for (size_t i = 0; i < trusted.size(); ++i)
    {
        if (trusted[i] == trusted.size() - 1 && trusts[i] == 0)
        {
            return i + 1;
        }
    }

    return -1;
}

// time complexity: O(2 * n)
// space complexity: O(n)
int findJudge_PW2(int N, std::vector<std::vector<int>>& trust)
{
    std::vector<int> trusts(N);
    for (auto pair: trust)
    {
        trusts[pair[1]-1]++;    // others trust him
        trusts[pair[0]-1]--;    // he trusts others
    }

    for (size_t i = 0; i < trusts.size(); ++i)
    {
        if (trusts[i] == N - 1)
        {
            return i + 1;
        }
    }

    return -1;
}

int findJudge(int N, std::vector<std::vector<int>>& trust)
{
    return findJudge_PW2(N, trust);
}

// time complexity: O(n), one iteration through edges, one through edge counts
// space complexity: O(n), where n is number of nodes
int findCenter_PW1(std::vector<std::vector<int>>& edges)
{
    std::unordered_map<int, int> edgeCount;
    for (auto edge: edges)
    {
        edgeCount[edge[1]]++;
        edgeCount[edge[0]]++;
    }

    int center = 0;
    for (auto count: edgeCount)
    {
        if (count.second == (edgeCount.size() - 1))
        {
            center = count.first;
            break;
        }
    }

    return center;
}

// time complexity: O(1)
// space complexity: O(1)
int findCenter_PW2(std::vector<std::vector<int>>& edges)
{
    return edges[0][0] == edges[1][0] || edges[0][0] == edges[1][1] ? edges[0][0] : edges[0][1];
}

int findCenter(std::vector<std::vector<int>>& edges)
{
    return findCenter_PW2(edges);
}

// time complexity: O(n)
// space complexity: O(1)
int maximumWealth(std::vector<std::vector<int>>& accounts)
{
    int maxWealth = 0;
    for (int i = 0; i < accounts.size(); ++i)
    {
        maxWealth = std::max(maxWealth, std::accumulate(accounts[i].begin(), accounts[i].end(), 0));
    }

    return maxWealth;
}

// time complexity: O(n)
// space complexity: O(1)
std::vector<bool> kidsWithCandies(std::vector<int>& candies, int extraCandies)
{
    int maxCandies = *std::max_element(candies.begin(), candies.end());
    std::vector<bool> result(candies.size());
    for (int i = 0; i < candies.size(); ++i)
    {
        if ((candies[i] + extraCandies) >= maxCandies) result[i] = true;
    }

    return result;
}

// time complexity: O(n^2)
// space complexity: O(n)
std::vector<int> minOperations_PW1(std::string boxes)
{
    std::vector<int> indices;
    for (size_t i = 0; i < boxes.size(); ++i)
    {
        if (boxes[i] == '1')
            indices.push_back(i);
    }

    std::vector<int> numOps(boxes.size());
    for (int i = 0; i < numOps.size(); ++i)
    {
        numOps[i] = 0;
        for (int j = 0; j < indices.size(); ++j)
        {
            numOps[i] += abs(indices[j] - i);
        }
    }

    return numOps;
}

// time complexity: O(n)
// space complexity: O(1)
std::vector<int> minOperations_PW2(std::string boxes)
{
    int distanceRight = 0, distanceLeft = 0;
    int onesLeft = 0;
    int onesRight = 0;
    for (size_t i = 1; i < boxes.size(); ++i)
    {
        if (boxes[i] == '1')
        {
            distanceRight += i;
            onesRight += 1;
        }
    }

    std::vector<int> numOps(boxes.size());
    numOps[0] = distanceRight;

    for (size_t i = 1; i < numOps.size(); ++i)
    {
        distanceLeft += onesLeft;

        if (boxes[i - 1] == '1')
        {
            distanceLeft += 1;
            onesLeft++;
        }
        if (boxes[i] == '1')
        {
            distanceRight -= 1;
            onesRight--;
        }

        distanceRight -= onesRight;

        numOps[i] = distanceLeft + distanceRight;
    }
    
    return numOps;
}

std::vector<int> minOperations(std::string boxes)
{
    return minOperations_PW2(boxes);
}

// time complexity: O(n^2)
// space complexity: O(1)
std::vector<int> smallerNumbersThanCurrent_PW1(std::vector<int>& nums)
{
    std::vector<int> numSmaller(nums.size());
    for (int i = 0; i < nums.size(); ++i)
    {
        for (int j = 0; j < nums.size(); ++j)
        {
            if (nums[j] < nums[i])
            {
                numSmaller[i]++;
            }
        }
    }
    return numSmaller;
}

// time complexity: O(n)
// space complexity: O(1)
std::vector<int> smallerNumbersThanCurrent_PW2(std::vector<int>& nums)
{
    std::vector<int> numSmaller(nums.size());
    std::vector<int> count(101);

    for (size_t i = 0; i < nums.size(); ++i) 
    {
        count[nums[i]]++;
    }
    for (size_t i = 1; i <= 100; ++i)
    {
        count[i] += count[i - 1];
    }
    for (int i = 0; i < nums.size(); ++i)
    {
        if (nums[i] == 0)
        {
            numSmaller[i] = 0;
        }
        else
        {
            numSmaller[i] = count[nums[i] - 1];
        }
    }
    return numSmaller;
}

std::vector<int> smallerNumbersThanCurrent(std::vector<int>& nums)
{
    return smallerNumbersThanCurrent_PW2(nums);
}

// time complexity: O(n + n + n log n)
// space complexity: O(2 * n)
int heightChecker_PW1(std::vector<int>& heights)
{
    std::vector<std::pair<int, int>> actual;
    int numMismatched = 0;

    size_t i = 0;
    for (auto height: heights)
    {
        actual.push_back({ i++, height});
    }
    std::sort(actual.begin(), actual.end(), [](std::pair<int, int> p1, std::pair<int, int> p2) {
        return p1.second < p2.second;
    });
    i = 0;
    for (auto pair: actual)
    {
        if (pair.first != i && actual[pair.first].second != pair.second)
        {
            numMismatched++;
        }
        i++;
    }
    return numMismatched;
}

// time complexity: O(n + n + n log n)
// space complexity: O(n)
int heightChecker_PW2(std::vector<int>& heights)
{
    std::vector<int> actual;
    std::copy(heights.begin(), heights.end(), std::back_inserter(actual));
    std::sort(actual.begin(), actual.end());
    int numMismatched = 0;
    for (int i = 0; i < heights.size(); ++i)
    {
        if (actual[i] != heights[i])
        {
            numMismatched++;
        }
    } 
    return numMismatched;
}

int heightChecker(std::vector<int>& heights)
{
    return heightChecker_PW2(heights);
}

// time complexity: O(n)
// space complexity: O(n)
int getMaximumGenerated(int n)
{
    int i = 0;
    std::vector<int> nums(n + 1);
    while (i <= n)
    {
        if (i == 0 || i == 1)
        {
            nums[i] = i;
        }
        
        if ((2 * i) >= 2 && (2 * i) <= n)
        {
            nums[2 * i] = nums[i];
        }
        
        if ((2 * i + 1) >= 2 && (2 * i + 1) <= n)
        {
            nums[2 * i + 1] = nums[i] + nums[i + 1];
        }

        i++;
    }

    return *std::max_element(nums.begin(), nums.end());
}

// space complexity: O(n)
// time complexity: O(n)
std::vector<std::vector<int>> floodFill_PW1(std::vector<std::vector<int>>& image, int sr, int sc, int newColor)
{
    std::queue<std::pair<int, int>> coords;
    coords.push({ sc, sr });
    int curColor = image[sr][sc];

    if (curColor == newColor) return image;

    int width = image[0].size(); 
    int height = image.size();

    while (!coords.empty())
    {
        auto curCoord = coords.front();
        int row = curCoord.second;
        int col = curCoord.first;
        coords.pop();

        if (image[row][col] == curColor)
        {
            image[row][col] = newColor;
        }

        if (((row + 1) < height) && image[row + 1][col] == curColor)
        {
            coords.push({col, row + 1});
        }
        if (((row - 1) >= 0) && image[row - 1][col] == curColor)
        {
            coords.push({col, row - 1});
        }
        if (((col + 1) < width) && image[row][col + 1] == curColor)
        {
            coords.push({col + 1, row});
        }
        if (((col - 1) >= 0) && image[row][col - 1] == curColor)
        {
            coords.push({col - 1, row});
        }
    }
    return image;
}

void dfs(std::vector<std::vector<int>>& image, int r, int c, int curColor, int newColor)
{
    if (image[r][c] == curColor)
    {
        image[r][c] = newColor;
        if ((r + 1) < image.size()) dfs(image, r + 1, c, curColor, newColor); 
        if ((r - 1) >= 0) dfs(image, r - 1, c, curColor, newColor); 
        if ((c + 1) < image[0].size()) dfs(image, r, c+1, curColor, newColor);
        if ((c - 1) >= 0) dfs(image, r, c-1, curColor, newColor);
    }
}

std::vector<std::vector<int>> floodFill_PW2(std::vector<std::vector<int>>& image, int sr, int sc, int newColor)
{
    if (image[sr][sc] == newColor) return image;

    dfs(image, sr, sc, image[sr][sc], newColor);
    return image;
}

std::vector<std::vector<int>> floodFill(std::vector<std::vector<int>>& image, int sr, int sc, int newColor)
{
    return floodFill_PW2(image, sr, sc, newColor);
}

// time complexity: O(n)
// space complexity: O(n)
std::vector<std::vector<int>> imageSmoother(std::vector<std::vector<int>>& M)
{
    std::vector<std::vector<int>> result(M.size());
    for (size_t i = 0; i < M.size(); ++i)
    {
        std::vector<int> rowData(M[0].size());
        result[i] = rowData;
        for (size_t j = 0; j < M[0].size(); ++j)
        {
            int sum = 0;
            int numPixels = 0;

            for (int k = -1; k <= 1; ++k)
            {
                for (int l = -1; l <= 1; ++l)
                {
                    int row = k + i;
                    int col = j + l;

                    if (row < 0 || row >= M.size() || col < 0 || col >= M[0].size())
                    {
                        continue;
                    }
                    else
                    {
                        numPixels++;
                        sum += M[row][col];
                    }
                }
            }

            result[i][j] = floor((float)sum/(float)numPixels);
        }
    }

    return result;
}

// time complexity: O(n log n)
// space complexity: O(1)
int majorityElement_PW1(std::vector<int>& nums)
{
    std::sort(nums.begin(), nums.end());
    return nums[nums.size() / 2];
}

int majorityElement_PW2(std::vector<int>& nums)
{
    std::unordered_map<int, int> counts;
    for (size_t i = 0; i < nums.size(); ++i)
    {
        counts[nums[i]]++;
    }

    int majority = 0;
    for (auto pair: counts)
    {
        if (pair.second >= round((float)nums.size() / (float)2))
        {
            majority = pair.first;
            break;
        }
    }

    return majority;
}

// time complexity: O(n)
// space complexity: O(1)
// Boyer Moore voting
int majorityElement_PW3(std::vector<int>& nums)
{
    int count = 0;
    int candidate = -1;
    for (auto num : nums) {
        if (count == 0) {
            candidate = num;
        }
        count += (num == candidate) ? 1 : -1;
    }

    return candidate;
}

int majorityElement(std::vector<int>& nums)
{
    return majorityElement_PW3(nums);
}

// time complexity: O(n + n log n)
// space complexity: O(1)
std::vector<std::vector<int>> allCellsDistOrder(int R, int C, int r0, int c0)
{
    std::vector<std::vector<int>> cells;
    for (int i = 0; i < R; ++i)
    {
        for (int j = 0; j < C; ++j)
        {
            cells.push_back({ i, j });
        }
    }

    std::sort(cells.begin(), cells.end(), [r0, c0](std::vector<int> cellA, std::vector<int> cellB) {
        auto distanceA = abs(cellA[0] - r0) + abs(cellA[1] - c0);
        auto distanceB = abs(cellB[0] - r0) + abs(cellB[1] - c0);
        return distanceA < distanceB;
    });

    return cells;
}

// time complexity: O(n), traverse twice
// space complexity: O(1)
int countGoodRectangles_PW1(std::vector<std::vector<int>>& rectangles)
{
    int maxWidth = std::numeric_limits<int>::min();
    for (auto rect: rectangles)
    {
        maxWidth = std::max(maxWidth, std::min(rect[0], rect[1]));
    }

    return std::count_if(rectangles.begin(), rectangles.end(), [maxWidth](std::vector<int> rect) {
        return maxWidth == std::min(rect[0], rect[1]);
    });
}

// time complexity: O(n)
// space complexity: O(n)
int countGoodRectangles_PW2(std::vector<std::vector<int>>& rectangles)
{
    int maxWidth = std::numeric_limits<int>::min();
    std::unordered_map<int, int> widths;
    for (auto rect: rectangles)
    {
        maxWidth = std::max(maxWidth, std::min(rect[0], rect[1]));
        widths[std::min(rect[0], rect[1])]++;
    }

    return widths[maxWidth];
}

// time complexity: O(n)
// space complexity: O(1)
int countGoodRectangles_PW3(std::vector<std::vector<int>>& rectangles)
{
    int maxWidth = std::numeric_limits<int>::min();
    int count = 0;
    for (auto rect: rectangles)
    {
        int curWidth = std::min(rect[0], rect[1]);
        if (curWidth > maxWidth)
        {
            maxWidth = std::max(maxWidth, curWidth);
            count = 1;
        }
        else if (curWidth == maxWidth)
        {
            count++;
        }
    }

    return count;
}

int countGoodRectangles(std::vector<std::vector<int>>& rectangles)
{
    return countGoodRectangles_PW3(rectangles);
}

// time complexity: O(n)
// space complexity: O(1)
int diagonalSum(std::vector<std::vector<int>>& mat)
{
    int sum = 0;
    for (int i = 0; i < mat.size(); ++i)
    {
        sum += mat[i][i];
        sum += mat[i][mat.size() - 1 - i];
    }

    if (mat.size() % 2 == 1)
        sum -= mat[mat.size() / 2][mat.size() / 2];

    return sum;
}

// time complexity: O(n)
// space complexity: O(1)
std::vector<int> selfDividingNumbers(int left, int right)
{
    std::vector<int> nums;
    for (int i = left; i <= right; ++i)
    {
        int temp1 = i;
        int temp2 = i;
        bool selfDividing = true;
        while (temp1)
        {
            if (!((temp1 % 10) == 0) && (temp2 % (temp1 % 10)) == 0)
            {
                // do nothing
            }
            else
            {
                selfDividing = false;
                break;
            }

            temp1 /= 10;
        }

        if (selfDividing)
        {
            nums.push_back(temp2);
        }
    }

    return nums;
}

// time complexity: O(n)
// space complexity: O(1)
int arraySign(std::vector<int>& nums)
{
    return std::accumulate(nums.begin(), nums.end(), 1, [](int acc, int num) {
        return acc * (num < 0 ? -1 : (num > 0 ? 1 : 0));
    });
}

// time complexity: O(n)
// space complexity: O(n)
int sumOfUnique(std::vector<int>& nums)
{
    std::unordered_map<int, int> count;
    for (int i = 0; i < nums.size(); ++i)
    {
        count[nums[i]]++;
    }

    int sum = 0;
    for (auto pair: count)
    {
        if (pair.second == 1)
        {
            sum += pair.first;
        }
    }

    return sum;
}

// time complexity: O(n)
// space complexity: O(1)
int maxProduct(std::vector<int>& nums)
{
    if (nums.size() < 2) 
    {
        return 0;
    }

    int max1 = nums[0];
    int max2 = nums[1] > max1 ? nums[1] : nums[0];
    if (max2 == nums[0]) 
    {
        max1 = nums[1];
    }
    
    for (int i = 2; i < nums.size(); ++i)
    {
        int cur = nums[i];
        if (cur >= max2)
        {
            max1 = max2;
            max2 = cur;
        }
        else if (cur >= max1)
        {
            max1 = cur;
        }
    }

    return (max1 - 1) * (max2 - 1);
}

// time complexity: O(n)
// space complexity: O(1)
int busyStudent(std::vector<int>& startTime, std::vector<int>& endTime, int queryTime)
{
    int numBusy = 0;
    for (int i = 0; i < endTime.size(); ++i)
    {
        if (queryTime >= startTime[i] && queryTime <= endTime[i])
        {
            ++numBusy;
        }
    }

    return numBusy;
}

// time complexity: O(n)
// space complexity: O(n)
std::vector<std::vector<int>> matrixReshape(std::vector<std::vector<int>>& nums, int r, int c)
{
    if ((r * c) > (nums.size() * nums[0].size()))
    {
        return nums;
    }

    std::vector<std::vector<int>> result(r);
    for (int i = 0; i < r; ++i)
    {
        std::vector<int> row(c);
        result[i] = row;
    }

    for (int i = 0; i < nums.size(); ++i)
    {
        for (int j = 0; j < nums[i].size(); ++j)
        {
            int el = i * nums[i].size() + j;
            int transR = el / c;
            int transC = el % c;
            result[transR][transC] = nums[i][j];
        }
    }

    return result;
}

// time complexity: O(n)
// space complexity: O(1)
int smallestRangeI(std::vector<int>& A, int K)
{
    int max = *std::max_element(A.begin(), A.end());
    int min = *std::min_element(A.begin(), A.end());

    if (max == min) 
    {
        return 0;
    }

    return (max - min) <= 2 * K ? 0 : max - min - 2 * K;
}

// time complexity: O(n)
// space complexity: O(1)
bool isToeplitzMatrix(std::vector<std::vector<int>>& matrix)
{
    for (int i = 1; i < matrix.size(); ++i)
    {
        for (int j = 1; j < matrix[0].size(); ++j)
        {
            if (matrix[i][j] != matrix[i - 1][j - 1])
            {
                return false;
            }
        }
    }

    return true;
}

std::vector<int> numMovesStones(int a, int b, int c)
{
    std::vector<int> sorted = { a , b , c};
    std::sort(sorted.begin(), sorted.end());
    a = sorted[0];
    b = sorted[1];
    c = sorted[2];

    std::vector<int> result(2);
    if (b - a == 1 && c - b == 1)
    {
        result[0] = 0;
        result[1] = 0;
    }
    else if ((b - a == 1) || (c - b == 1))
    {
        result[0] = 1;
        result[1] = ((b - a) > (c - b) ? b - a : c - b) - 1;
    }
    
    return result;
}

// time complexity: O(n)
// space complexity: O(n)
std::vector<std::string> summaryRanges(std::vector<int>& nums)
{
    if (nums.empty())
    {
        return {};
    }

    std::vector<std::string> ranges;
    std::string range = std::to_string(nums[0]);
    int numConsec = 1;
    for (int i = 1; i < nums.size(); ++i)
    {
        if ((nums[i] - 1) > nums[i - 1])
        {
            if (numConsec > 1)
            {
                range += "->";
                range += std::to_string(nums[i - 1]);
                ranges.push_back(range);
            }
            else
            {
                ranges.push_back(range);
            }

            numConsec = 1;
            range = std::to_string(nums[i]);
        }
        else
        {
            numConsec++;
        }
    }

    if (numConsec > 1)
    {
        range += "->";
        range += std::to_string(nums[nums.size() - 1]);
        ranges.push_back(range);
    }
    else
    {
        ranges.push_back(range);
    }

    return ranges;
}

// time complexity: O(n + n log n)
// space complexity: O(1)
std::vector<int> sortedSquares(std::vector<int>& nums)
{
    std::vector<int> result;
    for (auto num: nums)
    {
        result.push_back(pow(num, 2));
    }

    std::sort(result.begin(), result.end());
    return result;
}

// time complexity: O(n)
// space complexity: O(n)
bool uniqueOccurrences(std::vector<int>& arr)
{
    std::unordered_map<int, int> counts;
    std::unordered_set<int> unique_counts;
    for (size_t i = 0; i < arr.size(); ++i)
    {
        counts[arr[i]]++;
    }

    for (auto pair: counts)
    {
        if (unique_counts.find(pair.second) != unique_counts.end())
        {
            return false;
        }
        else
        {
            unique_counts.insert(pair.second);
        }
    }

    return true;
}

// time complexity: O(n^3)
// space complexity: O(1)
std::vector<int> nextGreaterElement_PW1(std::vector<int>& nums1, std::vector<int>& nums2)
{
    std::vector<int> arr = {};
    for (int i = 0; i < nums1.size(); ++i)
    {
        for (int j = 0; j < nums2.size(); ++j)
        {
            if (nums2[j] == nums1[i])
            {
                bool foundGreater = false;
                int k = j;
                for (; k < nums2.size(); ++k)
                {
                    if (nums2[k] > nums1[i])
                    {
                        foundGreater = true;
                        break;
                    }
                }

                if (foundGreater)
                {
                    arr.push_back(nums2[k]);
                }
                else
                {
                    arr.push_back(-1);
                }
            }
        }
    }

    return arr;
}

// time complexity: O(n^2)
// space complexity: O(n)
std::vector<int> nextGreaterElement_PW2(std::vector<int>& nums1, std::vector<int>& nums2)
{
    std::vector<int> arr = {};
    std::unordered_map<int, int> pos;
    for (int i = 0; i < nums2.size(); ++i)
    {
        pos[nums2[i]] = i;
    }

    for (int i = 0; i < nums1.size(); ++i)
    {
        bool foundGreater = false;
        int j = pos[nums1[i]];
        for (; j < nums2.size(); ++j)
        {
            if (nums2[j] > nums1[i])
            {
                foundGreater = true;
                break;
            }
        }

        if (foundGreater)
        {
            arr.push_back(nums2[j]);
        }
        else
        {
            arr.push_back(-1);
        }
    }

    return arr;
}

std::vector<int> nextGreaterElement(std::vector<int>& nums1, std::vector<int>& nums2)
{
    return nextGreaterElement_PW2(nums1, nums2);
}

// time complexity: O(n)
// space complexity: O(1)
int minStartValue(std::vector<int>& nums)
{
    int min = nums[0];
    int cur = min;
    for (int i = 1; i < nums.size(); ++i)
    {
        cur += nums[i];
        min = std::min(min, cur);
    }

    return min < 1 ? 1 - min : 1;
}

// time complexity: O(n log n)
// space complexity: O(1)
std::vector<int> sortByBits(std::vector<int>& arr)
{
    auto numOnes = [](int num) {

        int numOnes = 0;
        while (num) 
        {
            numOnes += num % 2;
            num /= 2;
        }

        return numOnes;
    };

    std::sort(arr.begin(), arr.end(), [&](int a, int b) {
        
        if (numOnes(a) < numOnes(b))
        {
            return 1;
        }
        else if (numOnes(a) == numOnes(b))
        {
            return a < b ? 1 : a == b;
        }
        else
        {
            return 0;
        }
    });

    return arr;
}

// time complexity: O(n)
// space complexity: O(1)
std::vector<int> replaceElements(std::vector<int>& arr)
{
    int curMax = arr[arr.size() - 1];
    arr[arr.size() - 1] = -1;
    for (int i = arr.size() - 2; i >= 0; --i)
    {
        int newMax = std::max(curMax, arr[i]);
        arr[i] = curMax;
        curMax = newMax;
    }
    return arr;
}

// time complexity: O(mn)
// space complexity: O(m + n)
std::vector<int> luckyNumbers (std::vector<std::vector<int>>& matrix)
{
    std::vector<int> lucky;
    std::set<int> minRow;
    std::set<int> maxCol;

    for (int i = 0; i < matrix.size(); ++i)
    {
        int min = matrix[i][0];
        for (int j = 0; j < matrix[0].size(); ++j)
        {
            min = std::min(matrix[i][j], min);
        }
        minRow.insert(min);
    }

    for (int i = 0; i < matrix[0].size(); ++i)
    {
        int max = matrix[0][i];
        for (int j = 0; j < matrix.size(); ++j)
        {
            max = std::max(matrix[j][i], max);
        }
        maxCol.insert(max);
    }

    for (auto row: minRow)
    {
        if (maxCol.find(row) != maxCol.end())
        {
            lucky.push_back(row);
        }
    }

    return lucky;
}

std::vector<int> intersection(std::vector<int>& nums1, std::vector<int>& nums2)
{
    return {};
}

// time complexity: O(n log n + n + n)
// space complexity: O(1)
std::vector<std::vector<int>> minimumAbsDifference(std::vector<int>& arr)
{
    std::sort(arr.begin(), arr.end());
    int absDiff = std::numeric_limits<int>::max();
    for (size_t i = 1; i < arr.size(); ++i)
    {
        int dist = arr[i] - arr[i - 1];
        absDiff = std::min(absDiff, dist);
    }

    std::vector<std::vector<int>> dists;
    for (size_t i = 1; i < arr.size(); ++i)
    {
        int dist = arr[i] - arr[i - 1];
        if (dist == absDiff)
        {
            dists.push_back({ arr[i - 1], arr[i] });
        }
    }

    return dists;
}

// time complexity: O(n + n log n)
// space complexity: O(n)
std::vector<int> frequencySort(std::vector<int>& nums)
{
    std::vector<int> result = nums;
    std::unordered_map<int, int> counts;
    for (auto num: nums)
    {
        counts[num]++;
    }
    std::sort(result.begin(), result.end(), [&](int a, int b) {
        int countA = counts[a];
        int countB = counts[b];
        if (countA == countB)
        {
            return a > b;
        } 
        else
        {
            return countA < countB;
        }
    });

    return result;
}

// time complexity: O(n + n)
// space complexity: O(n)
int repeatedNTimes_PW1(std::vector<int>& A)
{
    std::map<int, int> counts;
    for (auto a: A)
    {
        counts[a]++;
    }

    int maxEl = counts.begin()->first;
    int max = counts.begin()->second;

    for (auto count: counts)
    {
        max = std::max(count.second, max);
        if (max == count.second)
        {
            maxEl = count.first;
        }
    }
    return maxEl;
}

// time complexity: O(n log n)
// space complexity: O(1)
int repeatedNTimes_PW2(std::vector<int>& A)
{
    std::sort(A.begin(), A.end());
    return A[A.size() / 2] == A[A.size() / 2 + 1] ? A[A.size() / 2] : A[A.size() / 2 - 1];
}

int repeatedNTimes(std::vector<int>& A)
{
    return repeatedNTimes_PW2(A);
}

// time complexity: O(n)
// space complexity: O(1)
int countBalls(int lowLimit, int highLimit)
{
    std::vector<int> counts(46); // max size is 9 * 5 (45)

    auto sumDigits = [](int num) {
        int sum = 0;
        while (num)
        {
            sum += num % 10;
            num /= 10;
        }
        return sum;
    };

    for (int i = lowLimit; i <= highLimit; ++i)
    {
        int sum = sumDigits(i);
        counts[sum]++;
    }

    return *std::max_element(counts.begin(), counts.end());
}

// time complexity: O(n)
// space complexity: O(1)
int getMinDistance(std::vector<int>& nums, int target, int start)
{
    int minDist =  std::numeric_limits<int>::max();
    int curDist = minDist;
    for (int i = 0; i < nums.size(); ++i)
    {
        if (nums[i] == target)
        {
            curDist = abs(i - start);
            minDist = std::min(curDist, minDist);
        }
    }
    return minDist;
}

// time complexity: O(n)
// space complexity: O(n)
std::vector<std::vector<int>> transpose(std::vector<std::vector<int>>& matrix)
{
    int newWidth = matrix.size();
    int newHeight = matrix[0].size();

    std::vector<std::vector<int>> transposed;
    transposed.resize(newHeight);
    for (int i = 0; i < newHeight; ++i)
    {
        transposed[i].resize(newWidth);
    }

    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix[i].size(); ++j)
        {
            int pos = i * matrix[i].size() + j; 
            int row = pos % newWidth;
            int col = pos / newWidth;
            transposed[j][i] = matrix[i][j];
        }
    }

    return transposed;
}

// time complexity: O(n log n + n)
// space complexity: O(n)
bool isAlienSorted(std::vector<std::string>& words, std::string order)
{
    std::vector<std::string> sorted = words;
    std::sort(sorted.begin(), sorted.end(), [&](std::string a, std::string b) {
        for (size_t i = 0; i < a.size() && i < b.size(); ++i)
        {
            if (a[i] == b[i])
            {
                continue;
            }
            else
            {
                return order.find(a[i]) < order.find(b[i]);
            }
        }

        return a.size() < b.size();
    });

    for (size_t i = 0; i < words.size(); ++i)
    {
        if (words[i] != sorted[i])
        {
            return false;
        }
    }

    return true;
}

// time complexity: O(n + n log n)
// space complexity: O(n)
int lastStoneWeight(std::vector<int>& stones)
{
    std::multiset<int> stoness;
    for (auto s: stones)
    {
        stoness.insert(s);
    }

    while (stoness.size() > 1)
    {
        auto largest = --stoness.end();
        auto secondLargest = --(--stoness.end());

        if (*largest != *secondLargest)
        {
            int newStone = *largest - *secondLargest;
            stoness.erase(secondLargest, stoness.end());

            stoness.insert(newStone);
        }
        else
        {
            stoness.erase(secondLargest, stoness.end());
        }
    }
    return stoness.size() ? *stoness.begin() : 0;
}

// time complexity: O(n)
// space complexity: O(1)
int findMaxConsecutiveOnes(std::vector<int>& nums)
{
    int max = 0;
    int cur = 0;
    for (size_t i = 0; i < nums.size(); ++i)
    {
        if (nums[i])
        {
            ++cur;
        }
        else
        {
            max = std::max(cur, max);
            cur = 0;
        }
    }

    max = std::max(cur, max);

    return max;
}

// time complexity: O(n)
// space complexity: O(1)
int dominantIndex(std::vector<int>& nums)
{
    int max = 0, maxEl = 0, max2 = 0, maxEl2 = 0;

    for (int i = 0; i < nums.size(); ++i)
    {
        if (nums[i] > max)
        {
            max2 = max;
            maxEl2 = maxEl;
            max = nums[i];
            maxEl = i;
        }
        else if (nums[i] > max2)
        {
            max2 = nums[i];
            maxEl2 = i;
        }
    }

    if (max2 == 0) 
    {
        return maxEl;
    }

    return max / max2 >= 2 ? maxEl : -1;
}

// time complexity: O(n)
// space complexity: O(1)
bool lemonadeChange(std::vector<int>& bills)
{
    int num5s = 0;
    int num10s = 0;
    for (int i = 0; i < bills.size(); ++i)
    {
        if (bills[i] == 5)
        {
            ++num5s;
        }
        else if (bills[i] == 10)
        {
            if (num5s < 1)
            {
                return false;
            }
            else
            {
                --num5s;
                ++num10s;
            }
        }
        else if (bills[i] == 20)
        {
            if (num5s >= 3 || (num5s >= 1 && num10s >= 1))
            {
                if (num10s >= 1)
                {
                    num5s -= 1;
                    num10s -= 1;
                }
                else 
                {
                    num5s -= 3;
                }
            }
            else
            {
                return false;
            }
        }
    }

    return true;
}

// time complexity: O(n)
// space complexity: O(n)
std::vector<std::string> findRelativeRanks(std::vector<int>& score)
{
    std::map<int, std::string> ranks;
    for (size_t i = 0; i < score.size(); ++i)
    {
        ranks[score[i]] = "";
    }

    size_t i = 0;
    std::vector<std::string> medals = { "Gold Medal", "Silver Medal", "Bronze Medal"};
    for (auto it = ranks.rbegin(); it != ranks.rend(); it++)
    {
        if (i < 3)
        {
            it->second = medals[i];
        }
        else
        {
            it->second = std::to_string(i + 1);
        }

        i++;
    }

    std::vector<std::string> scores;
    for (auto s: score)
    {
        scores.push_back(ranks[s]);
    }

    return scores;
}

// time complexity: O(n log n + n log n = n)
// space complexity: O(1)
int numEquivDominoPairs(std::vector<std::vector<int>>& dominoes)
{
    for (auto& pair: dominoes)
    {
        std::sort(pair.begin(), pair.end());
    }

    std::sort(dominoes.begin(), dominoes.end(), [](std::vector<int> a, std::vector<int> b) {
    
        if (a[0] == b[0])
        {
            return a[1] < b[1];
        }
        else
        {
            return a[0] < b[0];
        }
    });

    int curNumEqualPairs = 1;
    int numEqualPairs = 0;
    for (size_t i = 1; i < dominoes.size(); ++i)
    {
        if ((dominoes[i][0] == dominoes[i-1][0]) &&
            (dominoes[i][1] == dominoes[i-1][1]))
        {
            ++curNumEqualPairs;
        }
        else
        {
            if (curNumEqualPairs > 1)
            {
                numEqualPairs += (curNumEqualPairs * (curNumEqualPairs - 1)) / 2;
            }

            curNumEqualPairs = 1;
        }
    }

    if (curNumEqualPairs > 1)
    {
        numEqualPairs += (curNumEqualPairs * (curNumEqualPairs - 1)) / 2;
    }

    return numEqualPairs;
}

// time complexity: O(n)
// space complexity: O(n)
std::vector<std::vector<int>> groupThePeople(std::vector<int>& groupSizes)
{
    std::map<int, std::vector<int>> people;
    std::vector<std::vector<int>> result;
    for (int i = 0; i < groupSizes.size(); ++i)
    {
        people[groupSizes[i]].push_back(i);
    }

    for (auto it = people.begin(); it != people.end(); ++it)
    {
        std::vector<int> newGroup;
        for (int j = 0; j < it->second.size(); ++j)
        {
            if (newGroup.size() == it->first)
            {
                result.push_back(newGroup);
                newGroup.clear();
            }
            newGroup.push_back(it->second[j]);
        }
        result.push_back(newGroup);
    }

    return result;
}

// time complexity: O(n log n + n)
// space complexity: O(1)
int maxIceCream(std::vector<int>& costs, int coins)
{
    std::sort(costs.begin(), costs.end());

    int i = 0;
    for (; i < costs.size(); ++i)
    {
        coins -= costs[i];

        if (coins < 0)
        {
            break;
        }
    }

    return i;
}

// time complexity: O(n log n)
// space complexity: O(1)
int maxCoins(std::vector<int>& piles)
{
    std::sort(piles.begin(), piles.end());
    int i = 0, k = piles.size() - 1, j = k - 1;

    int coins = 0;
    while (j > i)
    {
        coins += piles[j];
        ++i;
        k -= 2;
        j -= 2;
    }

    return coins;
}

// time complexity: O(n * k^2)
// space complexity: O(n)
std::vector<std::vector<int>> matrixBlockSum(std::vector<std::vector<int>>& mat, int k)
{
    std::vector<std::vector<int>> result(mat.size());
    for (int i = 0; i < mat.size(); ++i)
    {
        result[i].resize(mat[i].size());
        for (int j = 0; j < mat[i].size(); ++j)
        {
            for (int m = -k + i; m <= k + i; ++m)
            {
                if (m < 0 || m >= mat.size())
                {
                    continue;
                }

                for (int n = -k + j; n <= k + j; ++n)
                {
                    if (n < 0 || n >= mat[i].size())
                    {
                        continue;
                    }

                    result[i][j] += mat[m][n];
                }
            }
        }
    }

    return result;
}

// time complexity: O(n)
// space complexity: O(1)
int countBattleships(std::vector<std::vector<char>>& board)
{
    int numBattleships = 0;
    for (int i = 0; i < board.size(); ++i)
    {
        for (int j = 0; j < board[i].size(); ++j)
        {
            if (board[i][j] == '.')
            {
                continue;
            }

            // check top
            int y1 = i - 1;
            int x1 = j;

            // check left
            int y2 = i;
            int x2 = j - 1;

            bool matchFound = false;

            if (y1 >= 0 && board[y1][x1] == 'X')
            {
                matchFound = true;
            }
            else if (x2 >= 0 && board[y2][x2] == 'X')
            {
                matchFound = true;
            }

            if (!matchFound)
            {
                ++numBattleships;
            }
        }
    }

    return numBattleships;
}

// time complexity: O(n)
// space complexity: O(1)
std::vector<int> findDuplicates(std::vector<int>& nums)
{
    std::vector<int> duplicates;
    for (size_t i = 0; i < nums.size(); ++i)
    {
        nums[abs(nums[i]) - 1] = -nums[abs(nums[i]) - 1];
        if (nums[abs(nums[i]) - 1] > 0) 
        {
            duplicates.push_back(abs(nums[i]));
        }
    }

    return duplicates;
}

// time complexity: O(n log n)
// space complexity: O(n)
int minSetSize(std::vector<int>& arr)
{
    std::map<int, int> counts;
    for (size_t i = 0; i < arr.size(); ++i)
    {
        ++counts[arr[i]];
    }

    std::multimap<int, int> countsR;
    for (auto pair: counts)
    {
        countsR.insert({pair.second, pair.first});
    }

    int count = 0;
    int numInts = 0;
    for (auto it = countsR.rbegin(); it != countsR.rend(); it++)
    {
        count += it->first;
        numInts++;
        if (count >= arr.size() / 2)
        {
            break;
        }
    }

    return numInts;
}

// time complexity: O(n)
// space complexity: O(1)
std::vector<int> getSumAbsoluteDifferences(std::vector<int>& nums)
{
    std::vector<int> result(nums.size());
    std::unordered_map<int, int> cache;

    int sumGreater = std::accumulate(nums.begin(), nums.end(), 0);
    int numGreater = nums.size();
    int sumLesser = 0;
    int numLesser = 0;

    for (int i = 0; i < nums.size(); ++i)
    {
        sumGreater -= nums[i];
        numGreater--;
        result[i] += sumGreater - (numGreater * nums[i]) + (numLesser * nums[i]) - sumLesser;

        numLesser++;
        sumLesser += nums[i];
    }
    return result;
}

// time complexity: O(n)
// space complexity: O(n)
void gameOfLife(std::vector<std::vector<int>>& board)
{
    std::vector<std::vector<int>> nextState(board.size());
    for (size_t i = 0; i < board.size(); ++i)
    {
        nextState[i].resize(board[i].size());
        for (size_t j = 0; j < board[i].size(); ++j)
        {
            int numNeighbors = 0;
            for (int k = -1; k <= 1; ++k)
            {
                for (int l = -1; l <= 1; ++l)
                {
                    int r = i + k;
                    int c = j + l;
                    if ((r != i || c != j) && 
                        (r >= 0 && r < board.size()) &&
                        (c >= 0 && c < board[i].size()))
                    {
                        if (board[r][c] > 0)
                        {
                            numNeighbors++;
                        }
                    }
                }
            }

            if (board[i][j] && numNeighbors < 2)
            {
                nextState[i][j] = 0;
            }
            else if (board[i][j] && numNeighbors >= 2 && numNeighbors <= 3)
            {
                nextState[i][j] = 1;
            }
            else if (board[i][j] && numNeighbors > 3)
            {
                nextState[i][j] = 0;
            }
            else if (!board[i][j] && numNeighbors == 3)
            {
                nextState[i][j] = 1;
            }
        }
    }

    std::swap(nextState, board);
}

// time complexity: O(n)
// space complexity: O(1)
std::vector<int> productExceptSelf(std::vector<int>& nums)
{
    int countZeroes = 0;
    int product = 1;
    std::vector<int> result(nums.size());
    for (int i = 0; i < nums.size(); ++i)
    {
        if (!nums[i])
        {
            ++countZeroes;
        }
        else
        {
            product *= nums[i];
        }
    }

    for (int i = 0; i < nums.size(); ++i)
    {
        if (countZeroes > 1)
        {
            result[i] = 0;
        }
        else if (countZeroes && nums[i])
        {
            result[i] = 0;
        }
        else if (nums[i] == 0)
        {
            result[i] = product;
        }
        else
        {
            result[i] = product / nums[i];
        }
    }

    return result;
}

// time complexity: O(n)
// space complexity: O(1)
int numberOfArithmeticSlices(std::vector<int>& nums)
{
    int curSeq = 0;
    int sum = 0;
    int total = 0;
    for (int i = 2; i < nums.size(); ++i)
    {
        if ((nums[i - 1] - nums[i - 2]) == (nums[i] - nums[i - 1]))
        {
            curSeq++;
            sum += curSeq;
        }
        else
        {
            total += sum;
            curSeq = 0;
            sum = 0;
        }
    }

    total += sum;

    return total;
}