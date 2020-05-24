#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        
        // if num1Idx + num2Idx == medianIdx, break
        const auto medIdx = (nums1.size() + nums2.size()) / 2;
        auto curIdx = 0;
        auto it1 = nums1.begin();
        auto it2 = nums2.begin();
        auto activeSearch = 1;
        
        std::cout << "Median index: " << medIdx << std::endl;

        while (true)
        {
            if (curIdx == medIdx)
            {

            }
        }

        return 0;
    }
};

int main()
{
    Solution sol;
    std::vector<int> v1 = { 1, 3 };
    std::vector<int> v2 = { 3, 4 };
    auto result = sol.findMedianSortedArrays(v1, v2);
    std::cout << "Answer: " << result << std::endl;

    v1 = { 1, 3 };
    v2 = { 2 };
    result = sol.findMedianSortedArrays(v1, v2);
    std::cout << "Answer: " << result << std::endl;

    v1 = { 1, 3 };
    v2 = { 2 };
    result = sol.findMedianSortedArrays(v1, v2);
    std::cout << "Answer: " << result << std::endl;
    
    v1 = { 1, 3, 5, 7, 9, 11 }; 
    v2 = { 2 };
    // 1. which one is bigger: 2
    // 2. find first one bigger: i1
    // 3. if index is bigger exit? no
    // 4. find median index (4) (4 - 1 - 1) => i2 => answer = 5

    
    // 2 larger than 1, search v1
    // 3 larger than 2 (i1 = 1, i2 = 1), 
    // medIndex = 4
    // 5 larger than 3 (i1 = 1, i2 = 2)
    // 5 larger than 4 (i1 = 2, i2 = 2)
    // 
    v1 = { 1, 3, 4, 9}; 
    v2 = { 2, 5, 6 };

    std::cout << "Size: " << v1.size() + v2.size() << std::endl;
    result = sol.findMedianSortedArrays(v1, v2);
    std::cout << "Answer: " << result << std::endl;

    // 2 larger than 1, search v1 (medIndex )
    // 3 larger than 2 (i1 = 0, i2 = 1)
    // medIndex = curIndex 


    v1 = { 1, 3, 4, 9}; 
    v2 = { 2 };

    std::cout << "Size: " << v1.size() + v2.size() << std::endl;
    result = sol.findMedianSortedArrays(v1, v2);
    std::cout << "Answer: " << result << std::endl;

    // medIndex = 2
    // 3 larger than 1, search v1
    // 4 larger than 3 (i1 = 3, i2 = 1); 3 + 1
    // medIndex = curIndex (curIndex - i2 - 2)
    // 3 larger than 2 (i1 = 1, i2 = 0); 
    // curIndex + 1 must equal medIndex

    v1 = { 1, 2, 4, 9}; 
    v2 = { 3 };

    std::cout << "Size: " << v1.size() + v2.size() << std::endl;
    result = sol.findMedianSortedArrays(v1, v2);
    std::cout << "Answer: " << result << std::endl;

    // medIndex = 4
    // 2 larger than 1, search v1
    // 3 larger than 2 (i1 = 1, i2 = 0), search 2
    // 4 larger than 3 (i1 = 1, i2 = 1), 
    // 4 equal to 4 (i1 = 2, i2 = 1)
    // medIndex = curIndex + 1;


    v1 = { 1, 3, 4, 9}; 
    v2 = { 2, 4, 6, 7 };

    std::cout << "Size: " << v1.size() + v2.size() << std::endl;
    result = sol.findMedianSortedArrays(v1, v2);
    std::cout << "Answer: " << result << std::endl;

    v1 = { 1, 2, 3, 4, 5};
    v2 = { 1, 2, 3, 4, 5};

    // medIndex = 5;
    // 


    return 0;
}