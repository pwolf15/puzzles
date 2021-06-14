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

// time complexity: O(n)
// space complexity: O(n)
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

// time complexity: O(n)
// space complexity: O(n)
int Evaluate(const std::string& expression)
{
    int result = 0;
    std::string cur = "";
    std::stack<int> ops;
    for (int i = 0; i < expression.size(); ++i)
    {
        if (expression[i] == ',')
        {
            // delimiter
            if (cur == "+")
            {
                auto op1 = ops.top();
                ops.pop();
                auto op2 = ops.top();
                ops.pop();

                ops.push(op1 + op2);
                std::cout << op1 << ", " << op2 << std::endl;
                std::cout << ops.top() << std::endl;
            }
            else if (cur == "-")
            {
                auto op1 = ops.top();
                ops.pop();
                auto op2 = ops.top();
                ops.pop();

                ops.push(op2 - op1);
                std::cout << op1 << ", " << op2 << std::endl;
            }
            else if (cur == "/")
            {
                auto op1 = ops.top();
                ops.pop();
                auto op2 = ops.top();
                ops.pop();

                ops.push(op2 / op1);
                std::cout << op1 << ", " << op2 << std::endl;
            }
            else if (cur == "*")
            {
                auto op1 = ops.top();
                ops.pop();
                auto op2 = ops.top();
                ops.pop();
                ops.push(op1 * op2);

                std::cout << op2 << ", " << op1 << std::endl;
            }
            else
            {
                ops.push(std::atoi(cur.c_str()));
            }

            cur = "";
        }
        else
        {
            cur += expression[i];
        }
    }

    if (cur == "+")
    {
        auto op1 = ops.top();
        ops.pop();
        auto op2 = ops.top();
        ops.pop();

        ops.push(op2 + op1);
        std::cout << op1 << ", " << op2 << std::endl;
        std::cout << ops.top() << std::endl;
    }
    else if (cur == "-")
    {
        auto op1 = ops.top();
        ops.pop();
        auto op2 = ops.top();
        ops.pop();

        ops.push(op2 - op1);
        std::cout << op1 << ", " << op2 << std::endl;
    }
    else if (cur == "/")
    {
        auto op1 = ops.top();
        ops.pop();
        auto op2 = ops.top();
        ops.pop();

        ops.push(op2 / op1);
        std::cout << op1 << ", " << op2 << std::endl;
    }
    else if (cur == "*")
    {
        auto op1 = ops.top();
        ops.pop();
        auto op2 = ops.top();
        ops.pop();
        ops.push(op2 / op1);

        std::cout << op1 << ", " << op2 << std::endl;
    }
    else
    {
        ops.push(std::atoi(cur.c_str()));
    }

    result = ops.top();

    return result;
}

int evalRPN(std::vector<std::string>& tokens)
{
    int result = 0;
    std::stack<int> ops;
    for (int i = 0; i < tokens.size(); ++i)
    {
        if (tokens[i] == "+")
        {
            auto op1 = ops.top();
            ops.pop();
            auto op2 = ops.top();
            ops.pop();

            ops.push(op1 + op2);
            std::cout << op1 << ", " << op2 << std::endl;
            std::cout << ops.top() << std::endl;
        }
        else if (tokens[i] == "-")
        {
            auto op1 = ops.top();
            ops.pop();
            auto op2 = ops.top();
            ops.pop();

            ops.push(op2 - op1);
            std::cout << op1 << ", " << op2 << std::endl;
        }
        else if (tokens[i] == "/")
        {
            auto op1 = ops.top();
            ops.pop();
            auto op2 = ops.top();
            ops.pop();

            ops.push(op2 / op1);
            std::cout << op1 << ", " << op2 << std::endl;
        }
        else if (tokens[i] == "*")
        {
            auto op1 = ops.top();
            ops.pop();
            auto op2 = ops.top();
            ops.pop();
            ops.push(op1 * op2);

            std::cout << op2 << ", " << op1 << std::endl;
        }
        else
        {
            ops.push(std::atoi(tokens[i].c_str()));
        }
    }

    result = ops.top();

    return result;   
}