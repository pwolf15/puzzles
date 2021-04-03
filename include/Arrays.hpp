#ifndef ARRAYS_HPP
#define ARRAYS_HPP

#include <vector>
#include <string>

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

std::vector<int> ComputeRandomPermutation(int n);

std::vector<int> RandomSubset(int n, int k);

int NonuniformRandomNumberGeneration(const std::vector<int>& values,
                                     const std::vector<double>& probabilities);

bool IsValidSudoku(std::vector<std::vector<int>>& partial_assignment);

std::vector<int> MatrixInSpiralOrder(const std::vector<std::vector<int>>& square_matrix);

void RotateMatrix(std::vector<std::vector<int>>* square_matrix_ptr);

class RotatedMatrix {
public:
    explicit RotatedMatrix(std::vector<std::vector<int>>* square_matrix)
        : square_matrix_(*square_matrix) {}

    int ReadIntry(int i, int j) const {
        return square_matrix_[square_matrix_.size() - 1 - j][i];
    }

    void WriteEntry(int i, int j, int v) {
        square_matrix_[square_matrix_.size() - 1 - j][i] = v;
    }

private:
    std::vector<std::vector<int>>& square_matrix_;
};

std::vector<std::vector<int>> GeneratePascalTriangle(int num_rows);

std::vector<int> GeneratePascalRow(int num_rows);

std::vector<int> runningSum(std::vector<int>& nums);

int numIdenticalPairs(std::vector<int>& nums);

bool isBoomerang(std::vector<std::vector<int>>& points);

std::vector<int> kWeakestRows(std::vector<std::vector<int>>& mat, int k);

bool isOneBitCharacter(std::vector<int>& bits);

std::vector<int> addToArrayForm(std::vector<int>& A, int K);

int arrayPairSum(std::vector<int>& nums);

int findContentChildren(std::vector<int>& g, std::vector<int>& s);

int numRookCaptures(std::vector<std::vector<char>>& board);

int thirdMax(std::vector<int>& nums);

bool canPlaceFlowers(std::vector<int>& flowerbed, int n);

bool validMountainArray(std::vector<int>& arr);

bool hasGroupsSizeX(std::vector<int>& deck);

double average(std::vector<int>& salary);

int calPoints(std::vector<std::string>& ops);

int maxProfit(std::vector<int>& prices);

std::vector<bool> prefixesDivBy5(std::vector<int>& A);

int search(std::vector<int>& nums, int target);

bool canMakeArithmeticProgression(std::vector<int>& arr);

int oddCells(int n, int m, std::vector<std::vector<int>>& indices);

bool canFormArray(std::vector<int>& arr, std::vector<std::vector<int>>& pieces);

bool kLengthApart(std::vector<int>& nums, int k);

bool checkStraightLine(std::vector<std::vector<int>>& coordinates);

bool checkIfExist(std::vector<int>& arr);

bool check(std::vector<int>& nums);

std::vector<int> constructRectangle(int area);

bool containsNearbyDuplicate(std::vector<int>& nums, int k);

int countMatches(std::vector<std::vector<std::string>>& items, std::string ruleKey, std::string ruleValue);

int countNegatives(std::vector<std::vector<int>>& grid);

std::vector<int> createTargetArray(std::vector<int>& nums, std::vector<int>& index);

int minOperations(std::vector<std::string>& logs);

std::vector<int> diStringMatch(std::string S);

std::vector<int> decode(std::vector<int>& encoded, int first);

std::vector<int> decompressRLElist(std::vector<int>& nums);

std::string destCity(std::vector<std::vector<std::string>>& paths);

int countGoodTriplets(std::vector<int>& arr, int a, int b, int c);

std::vector<int> decrypt(std::vector<int>& code, int k);

int findShortestSubArray(std::vector<int>& nums);

int minDeletionSize(std::vector<std::string>& strs);

bool containsPattern(std::vector<int>& arr, int m, int k);

std::vector<int> finalPrices(std::vector<int>& prices);

int distributeCandies(std::vector<int>& candyType);

std::vector<int> distributeCandies(int candies, int num_people);

int distanceBetweenBusStops(std::vector<int>& distance, int start, int destination);

void duplicateZeros(std::vector<int>& arr);

std::vector<int> sumZero(int n);

class Employee {
public:
    int id;
    int importance;
    std::vector<int> subordinates;
};

int getImportance(std::vector<Employee*> employees, int id);

int findSpecialInteger(std::vector<int>& arr);

std::vector<int> fairCandySwap(std::vector<int>& A, std::vector<int>& B);

int findLucky(std::vector<int>& arr);

std::vector<int> findDisappearedNumbers(std::vector<int>& nums);

int findNumbers(std::vector<int>& nums);

int nearestValidPoint(int x, int y, std::vector<std::vector<int>>& points);

int largestAltitude(std::vector<int>& gain);

std::vector<std::vector<int>> flipAndInvertImage(std::vector<std::vector<int>>& image);

char nextGreatestLetter(std::vector<char>& letters, char target);

int findTheDistanceValue(std::vector<int>& arr1, std::vector<int>& arr2, int d);

int findJudge(int N, std::vector<std::vector<int>>& trust);

#endif // ARRAYS_HPP