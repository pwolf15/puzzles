#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <queue>
#include <cmath>

#include "Trees.hpp"

using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution
{
public:
    bool isSymmetric(TreeNode *root)
    {

        if (root == nullptr)
        {
            return true;
        }
        else
        {
            return isSymmetricRecursive(root->left, root->right);
        }
    }

private:
    bool isSymmetricRecursive(TreeNode *left, TreeNode *right)
    {
        if (left == nullptr && right == nullptr)
        {
            return true;
        }
        else if (left == nullptr || right == nullptr)
        {
            return false;
        }
        else if (left->val == right->val)
        {
            return isSymmetricRecursive(left->right, right->left) && isSymmetricRecursive(left->left, right->right);
        }
        else
        {
            return false;
        }
    }
};

int main()
{

    Solution sol;

    const std::vector<TreeNode *> tests = {
        createTree({1, 2, 2, 3, 4, 4, 3}),
        createTree({1, 2, 2, -1, 3, -1, 3}),
        createTree({1,2,2}),
        createTree({1,2,2,-1,3,-1,3}),
    };

    const std::vector<bool> expected = {
        true,
        false,
        true,
        false,
    };

    int i = 0;
    for (auto test : tests)
    {
        auto soln = sol.isSymmetric(test);
        printTreeBreadthFirst(test);
        assert(soln == expected[i]);
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}