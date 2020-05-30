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
    int maxDepth(TreeNode* root) {
        
        if (root == nullptr)
        {
            return 0;
        }
        else
        {
            auto maxDepthLeft = maxDepth(root->left);
            auto maxDepthRight = maxDepth(root->right);
            auto depth = maxDepthLeft > maxDepthRight ? maxDepthLeft : maxDepthRight;
            return 1 + depth;
        }
    }
private:
};

int main()
{

    Solution sol;

    const std::vector<TreeNode *> tests = {
        createTree({1 }),
        createTree({1, 2, 2}),
        createTree({3,9,20,-1,-1,15,7}),
        createTree({1, 2, 2, 3, 3, 3, 3, 4})
    };

    const std::vector<int> expected = {
        1,
        2,
        3,
        4
    };

    int i = 0;
    for (auto test : tests)
    {
        auto soln = sol.maxDepth(test);
        printTreeBreadthFirst(test);
        std::cout << "Solution: " << soln << std::endl;
        assert(soln == expected[i]);
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}