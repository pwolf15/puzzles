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
    int countNodes(TreeNode* root) {
        if (root == nullptr)
        {
            return 0;
        }
        else
        {
            return 1 + countNodes(root->left) + countNodes(root->right);
        }
    }
};

int main()
{

    Solution sol;

    const std::vector<TreeNode *> tests = {
        createTree({1,2,3,4,5,6}),
    };

    const std::vector<int> expected = {
       6
    };

    int i = 0;
    for (auto test : tests)
    {
        auto soln = sol.countNodes(test);
        std::cout << soln << std::endl;
        assert(soln == expected[i]);
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}