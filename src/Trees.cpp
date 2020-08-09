#include "Trees.hpp"
#include <limits>

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