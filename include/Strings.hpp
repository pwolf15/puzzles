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

bool halvesAreAlike(std::string s);

int titleToNumber(std::string columnTitle);

std::vector<std::string> commonChars(std::vector<std::string>& A);

bool areAlmostEqual(std::string s1, std::string s2);

std::string interpret(std::string command);

std::string toGoatLatin(std::string S);

std::string generateTheString(int n);

char findTheDifference(std::string s, std::string t);

int countCharacters(std::vector<std::string>& words, std::string chars);

std::string sortString(std::string s);

std::string gcdOfStrings(std::string str1, std::string str2);

bool isIsomorphic(std::string s, std::string t);

std::vector<std::string> findWords(std::vector<std::string>& words);

int balancedStringSplit(std::string s);

std::string toLowerCase(std::string str);

std::string removeOuterParentheses(std::string S);

std::string truncateSentence(std::string s, int k);

int uniqueMorseRepresentations(std::vector<std::string>& words);

bool squareIsWhite(std::string coordinates);

std::string mergeAlternately(std::string word1, std::string word2);

bool judgeCircle(std::string moves);

std::string reverseWords(std::string s);

std::vector<int> shortestToChar(std::string s, char c);

int numUniqueEmails(std::vector<std::string>& emails);

std::string removeDuplicates(std::string S);

bool checkIfPangram(std::string sentence);

bool canConstruct(std::string ransomNote, std::string magazine);

int maxNumberOfBalloons(std::string text);

#endif // STRINGS_HPP