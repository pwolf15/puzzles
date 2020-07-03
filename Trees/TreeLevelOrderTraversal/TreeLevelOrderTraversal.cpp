#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <queue>
#include <cmath>
#include <tuple>

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
    vector<vector<int>> levelOrderBottom(TreeNode* root) {

        vector<vector<int>> levelOrder;
        std::queue<std::pair<int, TreeNode*>> nodes;

        if (root == nullptr)
        {
            return levelOrder;
        }
        
        nodes.push({0, root});
        levelOrder.push_back({});
        
        while (!nodes.empty())
        {
            int level;
            TreeNode* cur;
            std::tie( level, cur ) = nodes.front();
            nodes.pop();

            if (levelOrder.size() < (level + 1))
            {
                levelOrder.resize(level + 1);
                levelOrder[level] = {};
            }

            levelOrder[level].push_back(cur->val);

            if (cur->left)
            {
                nodes.push({ level + 1, cur->left });
            }
            if (cur->right)
            {
                nodes.push({ level + 1, cur->right });
            }
        }

        return std::vector<std::vector<int>>(levelOrder.rbegin(), levelOrder.rend());
    }
};

int main()
{

    Solution sol;

    const std::vector<TreeNode *> tests = {
        createTree({3,9,20,-1,-1,15,7}),
        createTree({1,2,-1,3,-1,4,-1,5, -1})
    };

    const std::vector<vector<vector<int>>> expected = {
        {
            {15,7},
            {9,20},
            {3}
        },
        {
            {5},
            {4},
            {3},
            {2},
            {1},
        }
    };

    int i = 0;
    for (auto test : tests)
    {
        auto soln = sol.levelOrderBottom(test);
        // printTreeBreadthFirst(test);
        std::cout << soln[0][0] << std::endl;
        assert(soln == expected[i]);
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}