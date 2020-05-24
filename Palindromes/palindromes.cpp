#include <vector>
#include <iostream>

class Solution {
public:
    bool isPalindrome(int x) {
        
        bool ret = true;
        if (x < 0)
        {
            ret = false;
        }
        else
        {
            std::vector<int> digits;
            int scale = 1;
            int xCopy = x;
            while (x)
            {
                digits.push_back(x % 10);
                scale *= 10;
                x /= 10;
            }
            
            int xReversed = 0;
            scale /= 10;
            for (auto& d: digits)
            {
                std::cout << "Digit: " << d << std::endl;
                xReversed += scale * d;
                scale /= 10;
            }
            
            std::cout << "xCopy: " << xCopy << std::endl;
            std::cout << "xReversed: " << xReversed << std::endl;
            std::cout << digits.size() << std::endl;

            ret = xCopy == xReversed;
        }

        return ret;
    }
};

int main()
{
    Solution sol;
    sol.isPalindrome(121);
}