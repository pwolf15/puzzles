#include "Trees.hpp"
#include <limits>
#include <iostream>
#include <queue>
#include <numeric>
#include <vector>
#include <string>
#include <stack>

TreeNode* sortedArrayToBST(std::vector<int>& nums)
{
    if (nums.empty())
    {
        return nullptr;
    }
    auto tree = new TreeNode(nums[nums.size() / 2]);
    std::vector<int> left;
    std::vector<int> right;
    std::copy(nums.begin(), nums.begin() + nums.size() / 2, std::back_inserter(left));
    std::copy(nums.begin() + nums.size() / 2 + 1, nums.end(), std::back_inserter(right));
    tree->left = sortedArrayToBST(left);
    tree->right = sortedArrayToBST(right);
    
    return tree;
}

bool isValidBSTUtil(TreeNode* root, long int min, long int max)
{
    if (root == nullptr)
    {
        return true;
    }

    if (root->left && (root->left->val >= root->val || root->left->val <= min)) return false;
    if (root->right && (root->right->val <= root->val || root->right->val >= max)) return false;

    return isValidBSTUtil(root->left, min, root->val) && isValidBSTUtil(root->right, root->val, max);
}

bool isValidBST(TreeNode *root)
{
    return isValidBSTUtil(root, std::numeric_limits<long int>::min(), std::numeric_limits<long int>::max());
}

// space complexity: O(n)
// time complexity: O(n)
std::vector<double> averageOfLevels_PW(TreeNode* root)
{
    std::queue<TreeNode*> nodes;
    std::vector<double> averages;

    nodes.push(root);
    while (!nodes.empty())
    {
        std::queue<TreeNode*> new_nodes;
        std::vector<long long> level;

        while (!nodes.empty())
        {
            auto top = nodes.front();
            nodes.pop();
            level.push_back(top->val);
            if (top->left)
            {
                new_nodes.push(top->left);
            }
            if (top->right)
            {
                new_nodes.push(top->right);
            }
        }

        if (!level.empty())
        {
            long long sum = std::accumulate(level.begin(), level.end(), 0.0);
            averages.push_back(sum / (double)level.size());
        }

        std::swap(new_nodes, nodes);
    }
    
    return averages;
}

// space complexity: O(n)
// time complexity: O(n)
std::vector<double> averageOfLevels_PW2(TreeNode* root)
{
    std::queue<TreeNode*> nodes;
    std::vector<double> averages;
    double sum = 0;
    int count = 0;

    nodes.push(root);
    while (!nodes.empty())
    {
        std::queue<TreeNode*> new_nodes;
        std::vector<long long> level;
        sum = 0;
        count = 0;

        while (!nodes.empty())
        {
            auto top = nodes.front();
            sum += top->val;
            count++;

            nodes.pop();
            if (top->left)
            {
                new_nodes.push(top->left);
            }
            if (top->right)
            {
                new_nodes.push(top->right);
            }
        }

        if (count)
        {
            averages.push_back(sum / (double)count);
        }

        std::swap(new_nodes, nodes);
    }
    
    return averages;
}

std::vector<double> averageOfLevels(TreeNode* root)
{
    return averageOfLevels_PW2(root);
}

// time complexity: O(n)
// space complexity: O(n * log n)
std::vector<std::string> binaryTreePaths(TreeNode* root)
{
    if (root == nullptr) 
    {
        return {};
    }
    else {
        std::vector<std::string> left = binaryTreePaths(root->left);
        std::vector<std::string> right = binaryTreePaths(root->right);
        std::vector<std::string> paths;
        if (!left.empty())
        {
            for (auto path: left)
            {
                path = std::to_string(root->val) + "->" + path;
                paths.emplace_back(path);
            }
        }
        if (!right.empty())
        {
            for (auto path: right)
            {
                path = std::to_string(root->val) + "->" + path;
                paths.emplace_back(path);
            }
        }

        if (right.empty() && left.empty())
        {
            paths.emplace_back(std::to_string(root->val));
        }

        return paths;
    }
}

// time complexity: O(n), visit each node only once
// space complexity: O(n^2), construct new string for each node visit
std::string tree2str(TreeNode* t)
{
    if (!t) return "";
    std::string result = "";

    result += std::to_string(t->val);
    std::string left = tree2str(t->left);
    std::string right = tree2str(t->right);

    if (!right.empty())
    {
        // if right non-empty, always append both.
        //  case 1: left non-empty, would append in any case
        //  case 2: left empty, need to append to disambiguate with right-empty case
        result += "(" + left + ")";
        result += "(" + right + ")";
    }
    else if (!left.empty())
    {
        // if left non-empty and right empty, always append only left
        result += "(" + left + ")";
    }
    return result;
}

int sumNodes(TreeNode* root)
{
    if (!root)
    {
        return 0;
    }
    else {
        return root->val + sumNodes(root->left) + sumNodes(root->right);
    }
}

void tilt(TreeNode* root, std::vector<int>& tiltValues)
{
    if (!root)
    {
        return;
    }
    else if (!root->left && !root->right)
    {
        tiltValues.push_back(0);
        return;
    }
    else
    {
        int val = abs(sumNodes(root->left) - sumNodes(root->right));
        tiltValues.push_back(val);
        tilt(root->left, tiltValues);
        tilt(root->right, tiltValues);
    }
}

int findTilt(TreeNode* root)
{
    std::vector<int> tiltValues;
    tilt(root, tiltValues);

    return std::accumulate(tiltValues.begin(), tiltValues.end(), 0);
}
