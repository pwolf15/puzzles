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
    bool hasPathSum(TreeNode* root, int sum) {
        
        if (root == nullptr)
        {
            return false;
        }
        else if (root->left == nullptr && root->right == nullptr)
        {
            return root->val == sum;
        }
        else
        {
            return 
                hasPathSum(root->left, sum - root->val) || 
                hasPathSum(root->right, sum - root->val);
        }
        
    }
};

int main()
{

    Solution sol;

    const std::vector<TreeNode *> tests = {
        createTree({5,4,8,11, -1,13,4,7,2,-1, -1, -1,1}),
    };

    const std::vector<bool> expected = {
       true
    };

    int i = 0;
    for (auto test : tests)
    {
        auto soln = sol.hasPathSum(test, 22);
        // printTreeBreadthFirst(soln);
        assert(soln == expected[i]);
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}