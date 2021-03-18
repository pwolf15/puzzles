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

int StringToInt(const std::string& s);

std::string IntToString(int i);

std::string ConvertBase(const std::string& num_as_string, int b1, int b2);

int SSDecodeColID(const std::string& col);

int SSDecodeColIDBase0(const std::string& col);

int ReplaceAndRemove(int size, char s[]);

bool IsPalindrome(const std::string& s);

void ReverseWords(std::string * s);

std::string ReverseWordsLC(std::string s);

std::string LookAndSay(int n);

int RomanToInteger(const std::string& s);

std::vector<std::string> GetValidIpAddress(const std::string& s);

std::string SnakeString(const std::string& s);

std::string ZigZagString(const std::string& s);

std::string Encode(const std::string& s);

std::string Decode(const std::string& s);

int findStr(const std::string& s, const std::string& t);

std::vector<std::string> letterCasePermutation(std::string S);

std::string addStrings(std::string num1, std::string num2);

bool buddyStrings(std::string A, std::string B);

std::string convertToTitle(int n);

std::string defangIPaddr(std::string address);

bool backspaceCompare(std::string S, std::string T);

std::string convertToBase7(int num);

bool arrayStringsAreEqual(std::vector<std::string>& word1, std::vector<std::string>& word2);

int isPrefixOfWord(std::string sentence, std::string searchWord);

int maxPower(std::string s);

bool checkOnesSegment(std::string s);

std::string toHex(int num);

bool isLongPressedName(std::string name, std::string typed);

int countConsistentStrings(std::string allowed, std::vector<std::string>& words);

std::string freqAlphabets(std::string s);

#endif // STRINGS_HPP