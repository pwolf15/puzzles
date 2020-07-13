#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <queue>
#include <cmath>
#include <queue>

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
    int widthOfBinaryTree(TreeNode* root) {
        

        // auto search = root;
        // nodes.push(search);

        // int maxWidth    = 0;
        // int curWidth    = 0;
        // while (search)
        // {
        //     if (search->lef
        //     std::queue<TreeNode*> nodes;
        // }
    }
};

int main()
{

    Solution sol;

    const std::vector<TreeNode *> tests = {
        // createTree({3,9,20,-1,-1,15,7}),
        // createTree({}),
        createTree({1, 2}),
    };

    const std::vector<int> expected = {
       2,
    //    0,
    //    2,
    };

    int i = 0;
    for (auto test : tests)
    {
        auto soln = sol.widthOfBinaryTree(test);
        std::cout << soln << std::endl;
        assert(soln == expected[i]);
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}