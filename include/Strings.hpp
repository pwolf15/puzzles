#ifndef STRINGS_HPP
#define STRINGS_HPP

#include <string>
#include <vector>

// Given a string, find the first non-repeating character in it and return its index. 
// If it doesn't exist, return -1.
int firstUniqChar(std::string s);

// Given two strings s and t , write a function to determine if t is an anagram of s.
bool isAnagram(std::string s, std::string t);

bool detectCapitalUse(std::string word);

bool isPalindrome(std::string s);

std::string sumTwo(std::string A, std::string B);

void reverseString(std::vector<char> &s);

std::string addBinary(std::string a, std::string b);

bool IsPalindromic(const std::string& s);

#endif // STRINGS_HPP