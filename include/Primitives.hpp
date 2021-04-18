#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP


#include <vector>
#include <stdint.h>
#include <string>
#include <iostream>

short CountBits(unsigned int x);

// Given a non-negative integer num, 
// repeatedly add all its digits until the result has only one digit.
int addDigits(int num);

// Write a function that takes an unsigned integer and return the number of '1' bits it has 
// (also known as the Hamming weight).
// redundant with EPI Count Bits
int hammingWeight(uint32_t n);

bool isPowerOfThree(int n);

int missingNumber(std::vector<int>& nums);

int countPrimes(int n);

bool isPowerOfFour(int n);

void magicSquare(int n);

int numSteps(int n);

bool checkPerfectNumber(int num);

int binaryGap(int n);

bool hasAlternatingBits(int n);

std::vector<std::string> readBinaryWatch(int num);

int totalMoney(int n);

int bitwiseComplement(int N);

std::vector<int> getNoZeroIntegers(int n);

int countOdds(int low, int high);

int numberOfMatches(int n);

std::string dayOfTheWeek(int day, int month, int year);

int dayOfYear(std::string date);

bool divisorGame(int N);

int countLargestGroup(int n);

int trailingZeroes(int n);

int fib(int n);

int minPartitions(std::string n);

class Guesser 
{
public:

    Guesser(int seed): m_seed(seed)
    {

    }

    int guess(int n) 
    {
        if (n > m_seed)
        {
            return -1;
        }
        else if (n == m_seed)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }

    // time complexity: O(log n)
    // space complexity: O(1)
    int guessNumber(int n)
    {
        int lower = 0;
        int upper = n;
        int myGuess = (upper - lower) / 2;
        int result = guess(myGuess);
        while (result != 0)
        {
            if (result == 1)
            {
                lower = myGuess + 1;
                myGuess = (upper - lower) / 2 + lower;
            }
            else if (result == -1)
            {
                upper = myGuess - 1;
                myGuess = (upper - lower) / 2 + lower;
            }
            result = guess(myGuess);
        }
        return myGuess;
    }
private:
    int m_seed;
};

bool isHappy(int n);

int findKthPositive(std::vector<int>& arr, int k);

int xorOperation(int n, int start);

int subtractProductAndSum(int n);

int maximum69Number (int num);

#endif // PRIMITIVES_HPP