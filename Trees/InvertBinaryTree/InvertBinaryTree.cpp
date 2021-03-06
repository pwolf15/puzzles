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
    TreeNode* invertTree(TreeNode* root) {
        
        if (root == nullptr)
        {
            return root;
        }
        else
        {
            auto left= invertTree(root->right);
            auto right = invertTree(root->left);
            root->left = left;
            root->right = right;
            return root;
        }
    }
};

int main()
{

    Solution sol;

    const std::vector<TreeNode *> tests = {
        createTree({4,2,7,1,3,6,9}),
    };

    const std::vector<TreeNode *> expected = {
       createTree({4,7,2,9,6,3,1}),
    };

    int i = 0;
    for (auto test : tests)
    {
        auto soln = sol.invertTree(test);
        printTreeBreadthFirst(test);
        assert(equal(soln, expected[i]));
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}