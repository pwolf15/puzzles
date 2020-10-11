#include "Arrays.hpp"

#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <deque>
#include <cmath>
#include <map>

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