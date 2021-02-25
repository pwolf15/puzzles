#include "Trees.hpp"
#include <limits>
#include <iostream>
#include <queue>
#include <numeric>

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
std::vector<double> averageOfLevels(TreeNode* root)
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