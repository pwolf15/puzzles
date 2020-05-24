#include <string>
#include <stack>
#include <iostream>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        
        bool valid = true;
        std::stack<char> st;
        for (auto c: s)
        {
            if (c == ')')
            {
                char a = st.top();
                st.pop();
                if (a != '(')
                {
                    valid = false;
                    break;
                }
            }
            else if (c == '}')
            {
                char a = st.top();
                st.pop();
                if (a != '{')
                {
                    valid = false;
                    break;
                }
            }
            else if (c == ']')
            {
                char a = st.top();
                st.pop();
                if (a != '[')
                {
                    valid = false;
                    break;
                }
            }
            else 
            {
                st.push(c);
            }
        }
        
        if (!st.empty())
        {
            valid = false;
        }
        
        return valid;
        
    }
};

int main()
{
    Solution sol;
    std::cout << sol.isValid("]") << std::endl;
}