#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <algorithm>
#include <set>

using namespace std;

class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {
        
    }
    
    void push(int x) {
        minVec.push_back(x);
        minSet.insert(x);
    }
    
    void pop() {

        if (minSet.empty() || minVec.empty())
        {
            return;
        }

        auto value = top();
        auto itr = minSet.find(value);
        if(itr != minSet.end()){
            minSet.erase(itr);
        }

        minVec.pop_back();
    }
    
    int top() {

        if (minVec.empty())
        {
            return 0;
        }

        return minVec[minVec.size() - 1];
    }
    
    int getMin() {

        if (minSet.empty())
        {
            return 0;
        }

        return *(minSet.begin());
    }

    std::vector<int> minVec;
    std::multiset<int> minSet;

};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

int main()
{

    MinStack minStack;
    // for (int i = 0; i < 100; i++)
    // {
    //     minStack.push(i);
    // }

    std::cout << minStack.top() << std::endl;
    std::cout << minStack.getMin() << std::endl;

    for (int i = -1; i >= -100; i--)
    {
        minStack.push(i);
    }

    std::cout << minStack.top() << std::endl;
    std::cout << minStack.getMin() << std::endl;
    minStack.pop();
    std::cout << minStack.top() << std::endl;
    std::cout << minStack.getMin() << std::endl;
    minStack.push(-100);
    minStack.push(-100);
    minStack.pop();
    std::cout << minStack.top() << std::endl;
    std::cout << minStack.getMin() << std::endl;
    minStack.pop();
    std::cout << minStack.top() << std::endl;
    std::cout << minStack.getMin() << std::endl;

    return 0;
}