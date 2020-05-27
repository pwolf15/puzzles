#include <vector>
#include <iostream>
#include <assert.h>
#include <sstream>
#include <string>
#include <iterator>
#include <algorithm>

using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        
        int mIndex = 0;
        int nIndex = 0;

        while (true)
        {
            if (mIndex == m + n)
            {
                // completed merge
                break;
            }
            else if (mIndex == m)
            {
                // finished nums1 elements, add on remaining nums2 elements
                for (int i = nIndex; i < n; ++i)
                {
                    nums1[mIndex++] = nums2[i];
                }
            }
            else if (nIndex == n && mIndex < m)
            {
                // finished nums2 elements (nums2 is empty)
                break;
            }
            else if (nums1[mIndex] > nums2[nIndex])
            {

                // swap nums1 and nums2 elements if nums1 value > nums2
                auto temp = nums1[mIndex];
                nums1[mIndex++] = nums2[nIndex];
                nums2[nIndex] = temp;
                std::sort(nums2.begin(), nums2.end());
            }
            else if (nums1[mIndex] <= nums2[nIndex])
            {
                // skip to next element of nums1 if less than nums2 element
                mIndex++;
            }
        }
    }
};

int main()
{

    Solution sol;

    struct Test {
        std::vector<int> nums1;
        std::vector<int> nums2;
        int m;
        int n;
    };

    std::vector<Test> tests;

    Test test1;
    test1.nums1 = { 1, 2, 3, 0, 0, 0 };
    test1.nums2 = { 2, 5, 6 };
    test1.m = 3;
    test1.n = 3;

    tests.push_back(test1);

    Test test2;
    test2.nums1 = { };
    test2.nums2 = { };
    test2.m = 0;
    test2.n = 0;
    tests.push_back(test2);

    Test test3;
    test3.nums1 = { 1, 2, 3, 4, 5, 0, 0, 0, 0, 0 };
    test3.nums2 = { 6, 7, 8, 9, 10};
    test3.m = 5;
    test3.n = 5;
    tests.push_back(test3);

    Test test4;
    test4.nums1 = { 1 };
    test4.nums2 = { };
    test4.m = 1;
    test4.n = 0;
    tests.push_back(test4);

    Test test5;
    test5.nums1 = { 4, 5, 6, 0, 0, 0 };
    test5.nums2 = { 1, 2, 3 };
    test5.m = 3;
    test5.n = 3;
    tests.push_back(test5);

    const std::vector<std::vector<int>> expected = {
        { 1, 2, 2, 3, 5, 6 },
        { },
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
        { 1 },
        { 1, 2, 3, 4, 5, 6 },
    };

    int i = 0;
    for (auto test: tests)
    {
        sol.merge(test.nums1, test.m, test.nums2, test.n);
        assert(test.nums1 == expected[i]);
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}