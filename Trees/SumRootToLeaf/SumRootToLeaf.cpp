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
    int sumNumbers(TreeNode* root) {
        if (root == nullptr)
        {
            return 0;
        }
        else if (root->left == nullptr && root->right == nullptr)
        {
            return root->val;
        }
        else
        {
        
        }
        
    }
};

int main()
{

    Solution sol;

    const std::vector<TreeNode *> tests = {
        createTree({4,9,0,5,1}),
    };

    const std::vector<int> expected = {
       true
    };

    int i = 0;
    for (auto test : tests)
    {
        auto soln = sol.sumNumbers(test);

        // printTreeBreadthFirst(soln);
        assert(soln == expected[i]);
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}