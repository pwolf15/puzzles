#include "Arrays.hpp"

#include <algorithm>

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
void rotate_simple(std::vector<int>& nums, int k)
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
void rotate(std::vector<int>& nums, int k)
{
    rotate_simple(nums, k);
}

#include <iostream>

// You are given an n x n 2D matrix representing an image.
// Rotate the image by 90 degrees (clockwise).
void rotate(std::vector<std::vector<int>>& matrix)
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
void EvenOdd_BF(std::vector<int>* A_ptr)
{
    std::vector<int>& A = *A_ptr;
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
void EvenOdd_InPlace(std::vector<int>* A_ptr)
{
    std::vector<int>& A = *A_ptr;

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

void EvenOdd_Book(std::vector<int>* A_ptr)
{
    std::vector<int>& A = *A_ptr;
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

void EvenOdd(std::vector<int>* A_ptr)
{
    return EvenOdd_Book(A_ptr);
}

// O(3n) space complexity
// O(4n) time complexity (search, search, search, generate)
void DutchFlagPartition_BF(int pivot_index, std::vector<Color>* a_ptr)
{
    std::vector<Color>& A = *a_ptr;
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
void DutchFlagPartition_n2(int pivot_index, std::vector<Color>* a_ptr)
{
    std::vector<Color>& A = *a_ptr;
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
void DutchFlagPartition_n(int pivot_index, std::vector<Color>* a_ptr)
{
    std::vector<Color>& A = *a_ptr;
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

void DutchFlagPartition_OnePass(int pivot_index, std::vector<Color>* a_ptr)
{
    std::vector<Color>& A = *a_ptr;
    Color pivot = A[pivot_index];
    /**
     * Keep the following invariants during partitioning.
     * bottom group: A[0, smaller - 1]
     * middle group: A[smaller, equal - 1]
     * unclassified group: A[equal, larger - 1]
     * top group: A[larger, size(A) - 1]
     */ 
    int smaller = 0, equal   = 0, larger  = A.size();
    
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

void DutchFlagPartition(int pivot_index, std::vector<Color>* a_ptr)
{
    DutchFlagPartition_OnePass(pivot_index, a_ptr);
}

