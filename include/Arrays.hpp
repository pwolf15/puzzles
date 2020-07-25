#ifndef ARRAYS_HPP
#define ARRAYS_HPP


#include <vector>

// Given a sorted array nums, 
//  remove the duplicates in-place such that 
//  each element appear only once and return the new length.
// Do not allocate extra space for another array, 
// you must do this by modifying the input array in-place with O(1) extra memory.
int removeDuplicates(std::vector<int>& nums); 

// Given an array, rotate the array to the right by k steps, where k is non-negative.
void rotate(std::vector<int>& nums, int k);

// You are given an n x n 2D matrix representing an image.
// Rotate the image by 90 degrees (clockwise).
void rotate(std::vector<std::vector<int>>& matrix);

void EvenOdd(std::vector<int>* A_ptr);

typedef enum { kRed, kWhite, kBlue } Color;

void DutchFlagPartition(int pivot_index, std::vector<Color>* a_ptr);

#endif // ARRAYS_HPP