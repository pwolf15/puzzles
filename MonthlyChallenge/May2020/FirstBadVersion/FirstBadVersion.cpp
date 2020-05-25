#include <vector>
#include <iostream>
#include <assert.h>
#include <sstream>
#include <string>
#include <iterator>
#include <algorithm>

using namespace std;

// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

static int badVersion = 1;
static int depth = 0;

static bool isBadVersion(int version)
{
    return version >= badVersion ? true : false;
}

class Solution {
public:
    int firstBadVersion(int n) 
    {
        return firstBadVersionBinary(n);
    }

private:
    int bruteForce(int n) 
    {
        for (int i = 0; i < n; ++i)
        {
            if (isBadVersion(i))
                return i;
        }

        return n;
    }

    int firstBadVersionBinary(int n)
    {
        depth = 0;

        if (n == 1)
        {
            return isBadVersion(n);
        }

        return binarySearch(n / 2, n / 2 + 1);
    }

    int binarySearch(int curN, int N) 
    {   
        if (N == 1)
        {
            return curN;
        }
        else if (!isBadVersion(curN - 1) && isBadVersion(curN))
        {
            return curN;
        }
        else if (isBadVersion(curN))
        {
            return binarySearch(curN - N / 2, N / 2);
        }
        else if (!isBadVersion(curN))
        {
            return binarySearch(curN + N / 2, N / 2 + 1);
        }
    }
};

int search(int* arr, int pos, int i, int size)
{
    std::cout << "Pos: " << pos << std::endl;
    std::cout << "Size: " << size << std::endl;
    depth++;

    if (depth >= 20)
    {
        exit(1);
    }
    if (arr[pos] == i)
    {
        return pos;
    }
    else if (arr[pos] > i)
    {
        return search(arr, pos - size / 2, i, size / 2);
    }
    else if (arr[pos] < i)
    {
        return search(arr, pos + size / 2, i, size / 2 + 1);
    }
}

int main()
{

    Solution sol;

    const std::vector<int> tests = {
        1,
        5,
        5,
        10000,
        500000,
        2
    };

    const std::vector<int> expected = {
        1,
        3,
        4,
        3673,
        367223,
        2
    };

    int i = 0;
    for (auto test : tests)
    {
        badVersion = expected[i];
        auto soln = sol.firstBadVersion(tests[i]);
        std::cout << "Soln: " << soln << std::endl;
        assert(expected[i] == soln);
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    // std::vector<int> arr;
    // for (int i = 0; i < 500000; ++i)
    // {
    //     arr.push_back(i);
    // }
    // std::cout << search(&arr[0], 250000,  367223, 250000) << std::endl;

    return 0;
}