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
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        
        if (root == nullptr)
        {
            return true;
        }

        if (isBalanced(root->left) && isBalanced(root->right))
        {
            int left = getHeight(root->left);
            int right = getHeight(root->right);
            return std::abs(left - right) <= 1;
        }
        else
        {
            return false;
        }
    }
private:
    int getHeight(TreeNode* root) {

        if (root == nullptr)
        {
            return 0;
        }
        else
        {
            return 1 + std::max(getHeight(root->left), getHeight(root->right));
        }
        
    }
};

int main()
{

    Solution sol;

    const std::vector<TreeNode *> tests = {
        createTree({3,9,20,-1,-1,15,7}),
        createTree({1,2,2,3,3,-1,-1,4,4}),
        createTree({1,2,2,3,-1,-1,3,4,-1,-1,4}),
    };

    const std::vector<bool> expected = {
       true,
       false,
       false,
    };

    int i = 0;
    for (auto test : tests)
    {
        auto soln = sol.isBalanced(test);
        assert(soln == expected[i]);
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}