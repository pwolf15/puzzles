#include "Stacks.hpp"

#include <stack>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <functional>

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
int Evaluate_PW(const std::string& expression)
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

// time complexity: O(n)
// space complexity: O(n)
int Evaluate_EPI(const std::string& expression)
{
    std::stack<int> intermediate_results;
    std::stringstream ss(expression);
    std::string token;
    const char kDelimiter = ',';
    const std::unordered_map<std::string, std::function<int(int, int)>> kOperators = 
    {
        { "+", [](int x, int y) -> int { return x + y; }},
        { "-", [](int x, int y) -> int { return x - y; }},
        { "*", [](int x, int y) -> int { return x * y; }},
        { "/", [](int x, int y) -> int { return x / y; }},
    };

    while (getline(ss, token, kDelimiter))
    {
        if (kOperators.count(token))
        {
            const int y = intermediate_results.top();
            intermediate_results.pop();
            const int x = intermediate_results.top();
            intermediate_results.pop();
            intermediate_results.emplace(kOperators.at(token)(x, y));
        }
        else
        {
            intermediate_results.emplace(std::stoi(token));
        }
    }

    return intermediate_results.top();
}

int Evaluate(const std::string& expression)
{
    return Evaluate_EPI(expression);
}

// time complexity: O(n)
// space complexity: O(n)
int evalRPN_PW(std::vector<std::string>& tokens)
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

int evalRPN_EPI(std::vector<std::string>& tokens)
{
    std::stack<int> intermediate_results;
    const std::unordered_map<std::string, std::function<int(int, int)>> kOperators = 
    {
        { "+", [](int x, int y) -> int { return x + y; }},
        { "-", [](int x, int y) -> int { return x - y; }},
        { "*", [](int x, int y) -> int { return x * y; }},
        { "/", [](int x, int y) -> int { return x / y; }},
    };

    for (size_t i = 0; i < tokens.size(); ++i)
    {
        std::string token = tokens[i];
        if (kOperators.count(token))
        {
            const int y = intermediate_results.top();
            intermediate_results.pop();
            const int x = intermediate_results.top();
            intermediate_results.pop();
            intermediate_results.emplace(kOperators.at(token)(x, y));
        }
        else
        {
            intermediate_results.emplace(std::stoi(token));
        }
    }

    return intermediate_results.top();
}

int evalRPN(std::vector<std::string>& tokens)
{
    return evalRPN_EPI(tokens);
}

// time complexity: O(n)
// space complexity: O(n)
bool isWellFormed_PW(const std::string& s)
{
    std::stack<char> braces;
    for (int i = 0; i < s.size(); ++i)
    {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{')
        {
            braces.push(s[i]);
        }
        else
        {
            if (braces.empty())
            {
                return false;
            }

            char c = braces.top();
            braces.pop();

            bool invalid = false;
            if (s[i] == ')')
            {
                invalid = c != '(';
            }
            else if (s[i] == ']')
            {
                invalid = c != '[';
            }
            else if (s[i] == '}')
            {
                invalid = c != '{';
            }

            if (invalid)
            {
                return false;
            }
        }
    }

    if (!braces.empty())
    {
        return false;
    }

    return true;
}

// time complexity: O(n)
// space complexity: O(n)
bool isWellFormed_EPI(const std::string& s)
{
    std::stack<char> left_chars;
    const std::unordered_map<char, char> kLookup = 
    {
        { '(', ')' }, {'{', '}'}, {'[', ']'}
    };
    for (int i = 0; i < std::size(s); ++i)
    {
        if (kLookup.count(s[i]))
        {
            left_chars.emplace(s[i]);
        }
        else
        {
            if (std::empty(left_chars) || 
                kLookup.at(left_chars.top()) != s[i])
            {
                // Unmatched right char or mismatched chars
                return false;
            }
            left_chars.pop();
        }
    }
    return std::empty(left_chars);
}

bool isWellFormed(const std::string& s)
{
    return isWellFormed_EPI(s);
}

// time complexity: O(n)
// space complexity: O(n)
std::string ShortestEquivalentPath_PW(const std::string& path)
{
    std::string curDir = "";
    std::stack<std::string> dirs;

    for (int i = 1; i < path.size(); ++i)
    {
        if (path[i] == '/' && !curDir.empty())
        {
            if (curDir == "..")
            {
                if (!dirs.empty())
                {
                    dirs.pop();
                }
            }
            else if (curDir == ".")
            {

            }
            else 
            {
                dirs.push(curDir);
            }

            curDir = "";
        }
        else if (path[i] == '/')
        {

        }
        else
        {
            curDir += path[i];
        }
    }

    if (!curDir.empty())
    {
        if (curDir == "..")
        {
            if (!dirs.empty())
            {
                dirs.pop();
            }
        }
        else if (curDir == ".")
        {

        }
        else 
        {
            dirs.push(curDir);
        }

        curDir = "";
    }

    std::string absPath = "";

    while (!dirs.empty())
    {
        if (!absPath.empty())
        {
            absPath = dirs.top() + "/" + absPath;
        }
        else
        {
            absPath = dirs.top();
        }

        dirs.pop();
    }

    if (path[0] == '/')
    {
        absPath = "/" + absPath;
    }

    return absPath;
}

std::string ShortestEquivalentPath_EPI(const std::string& path)
{
    if (std::empty(path)) 
    {
        throw std::invalid_argument("Empty string is not a valid path.");
    }
    
    std::vector<std::string> path_names;
    // Special case: starts with "/", which is an absolute path
    if (path.front() == '/')
    {
        path_names.emplace_back("/");
    }

    std::stringstream ss(path);
    std::string token;
    while (std::getline(ss, token, '/'))
    {
        if (token == "..")
        {
            if (std::empty(path_names) || path_names.back() == "..")
            {
                path_names.emplace_back(token);
            }
            else
            {
                if (path_names.back() == "/")
                {
                    throw std::invalid_argument("Path error");
                }
                path_names.pop_back();
            }
        }
        else if (token != "." && token != "") 
        {
            // Must be a name.
            path_names.emplace_back(token);
        }
    }

    std::string result;
    if (!std::empty(path_names))
    {
        result = path_names.front();
        for (int i = 1; i < std::size(path_names); ++i)
        {
            if (i == 1 && result == "/")
            {
                result += path_names[i];
            }
            else
            {
                result += "/" + path_names[i];
            }
        }
    }

    return result;
}

std::string ShortestEquivalentPath(const std::string& path)
{
    return ShortestEquivalentPath_EPI(path);
}

// time complexity: O(n)
// space complexity: O(n)
std::vector<int> ExamineBuildsWithSunset_PW(
    std::vector<int>::const_iterator sequence_begin,
    std::vector<int>::const_iterator sequence_end
)
{
    int building_idx = 0;
    struct Building {
        int id;
        int height;
    };

    std::vector<int> result;
    std::stack<Building> curBuildings;
    while (sequence_begin != sequence_end)
    {
        while (!curBuildings.empty() && *sequence_begin >= curBuildings.top().height)
        {
            curBuildings.pop();
        }
        curBuildings.push(Building{building_idx++,*sequence_begin++});
    }

    while (!curBuildings.empty())
    {
        result.push_back(curBuildings.top().id);
        curBuildings.pop();
    }

    return result;
}

// time complexity: O(n)
// space complexity: O(n)
std::vector<int> ExamineBuildsWithSunset_EPI(
    std::vector<int>::const_iterator sequence_begin,
    std::vector<int>::const_iterator sequence_end
)
{
    int building_idx = 0;
    struct BuildingWithHeight {
        int id, height;
    };
    std::stack<BuildingWithHeight> candidates;
    while (sequence_begin != sequence_end)
    {
        int building_height = *sequence_begin++;
        while (!std::empty(candidates) && building_height >= candidates.top().height)
        {
            candidates.pop();
        }
        candidates.emplace(BuildingWithHeight{building_idx++, building_height});
    }

    std::vector<int> buildings_with_sunset;
    while (!std::empty(candidates))
    {
        buildings_with_sunset.emplace_back(candidates.top().id);
        candidates.pop();
    }
    return buildings_with_sunset;
}

std::vector<int> ExamineBuildsWithSunset(
    std::vector<int>::const_iterator sequence_begin,
    std::vector<int>::const_iterator sequence_end
)
{
    return ExamineBuildsWithSunset_PW(sequence_begin, sequence_end);
}

std::vector<std::vector<int>> BinaryTreeDepthOrder(
    const std::unique_ptr<BinaryTreeNode<int>>& tree
)
{
    std::vector<std::vector<int>> depthOrder;
    std::queue<BinaryTreeNode<int>*> cur;

    if (!tree)
    {
        return {};
    }
    
    cur.push(tree.get());

    if (!cur.empty())
    {
        depthOrder.push_back({});
    }

    while (true)
    {
        std::queue<BinaryTreeNode<int>*> nextCur;
        while (!cur.empty())
        {
            auto node = cur.front();
            cur.pop();
            depthOrder.back().push_back(node->data);

            if (node->left)
            {
                nextCur.push(node->left.get());
            }
            if (node->right)
            {
                nextCur.push(node->right.get());
            }
        }

        if (nextCur.empty())
        {
            break;
        }
        else 
        {
            std::swap(cur, nextCur);
            depthOrder.push_back({});
        }
    }

    return depthOrder;
}