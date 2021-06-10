#include "Stacks.hpp"

#include <stack>
#include <iostream>

void PrintLinkedListInReverse(std::shared_ptr<ListNodeEPI<int>> head)
{
    std::stack<int> nodes;
    while (head) {
        nodes.push(head->data);
        head = head->next;
    }
    while (!empty(nodes)) {
        std::cout << nodes.top() << std::endl;
        nodes.pop();
    }
}

int clumsy(int n)
{
    enum Op
    {
        TIMES,
        DIVIDE,
        PLUS,
        MINUS
    };

    std::stack<Op> opsS1;
    std::stack<Op> opsS2;
    std::stack<int> nums1;
    std::stack<int> nums2;

    int fact = 0;
    int i = 0;

    while (n)
    {
        nums1.push(n);

        if (nums1.size() >= 2 && !opsS1.empty() && opsS1.top() < Op::PLUS)
        {
            Op op = opsS1.top();
            opsS1.pop();

            int argB = nums1.top();
            nums1.pop();
            int argA = nums1.top();
            nums1.pop();

            if (op == Op::TIMES)
            {
                nums1.push((Op)argA * argB);
            }
            else if (op == Op::DIVIDE)
            {
                nums1.push((Op)argA / argB);
            }
        }
        
        opsS1.push((Op)(i % 4));

        ++i;
        --n;
    }

    opsS1.pop();

    while(!opsS1.empty())
    {
        opsS2.push(opsS1.top());
        opsS1.pop();
    }

    while (!nums1.empty())
    {
        nums2.push(nums1.top());
        nums1.pop();
    }

    while (!opsS2.empty())
    {
        int argA = nums2.top();
        nums2.pop();

        int argB = nums2.top();
        nums2.pop();

        Op op = opsS2.top();
        opsS2.pop();

        if (op == Op::PLUS)
        {
            nums2.push(argA + argB);
        }
        else if (op == Op::MINUS)
        {
            nums2.push(argA - argB);
        }
    }

    return nums2.top();
}