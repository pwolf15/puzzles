#ifndef ARRAYS_HPP
#define ARRAYS_HPP

#include <vector>

// Given a sorted array nums,
//  remove the duplicates in-place such that
//  each element appear only once and return the new length.
// Do not allocate extra space for another array,
// you must do this by modifying the input array in-place with O(1) extra memory.
int removeDuplicates(std::vector<int> &nums);

// Given an array, rotate the array to the right by k steps, where k is non-negative.
void rotate(std::vector<int> &nums, int k);

// You are given an n x n 2D matrix representing an image.
// Rotate the image by 90 degrees (clockwise).
void rotate(std::vector<std::vector<int>> &matrix);

void EvenOdd(std::vector<int> *A_ptr);

typedef enum
{
    kRed,
    kWhite,
    kBlue
} Color;

void DutchFlagPartition(int pivot_index, std::vector<Color> *a_ptr);

void moveZeroes(std::vector<int> &nums);

std::vector<int> PlusOne(std::vector<int> nums);

bool containsDuplicate(std::vector<int> &nums);

bool isValidSudoku(std::vector<std::vector<char>> &board);

std::vector<int> Multiply(std::vector<int> num1, std::vector<int> num2);

bool CanReachEnd(const std::vector<int> &max_advance_steps);

int DeleteDuplicates(std::vector<int> *A_ptr);

int DeleteKey(std::vector<int> *A_ptr, int key);

int AtMostN(std::vector<int> *A_ptr);

double BuyAndSellStockOnce(const std::vector<double> &prices);

size_t longestContiguousSubarray(const std::vector<int> &nums);

double BuyAndSellStockTwice(const std::vector<double> &prices);

std::vector<int> intersect(std::vector<int> &nums1, std::vector<int> &nums2);

void Rearrange(std::vector<int> *A_ptr);

std::vector<int> sortArrayByParity(std::vector<int> &A);

std::vector<int> GeneratePrimes(int n);

void ApplyPermutation(std::vector<int> perm, std::vector<int>* A_ptr);

std::vector<int> NextPermutation(std::vector<int> perm);

std::vector<int> NextPermutationEPI(std::vector<int> perm);

void NextPermutationLC(std::vector<int> &nums);

void RandomSampling(int k, std::vector<int>* A_ptr);

// Assumption: there at least k elements in the stream.
std::vector<int> OnlineRandomSample(std::vector<int>::const_iterator stream_begin,
    const std::vector<int>::const_iterator stream_end,
    int k);

#endif // ARRAYS_HPP