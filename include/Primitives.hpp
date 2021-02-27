#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP


#include <vector>
#include <stdint.h>

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

#endif // PRIMITIVES_HPP