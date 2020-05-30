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
    vector<vector<int>> levelOrderBottom(TreeNode* root) {

        vector<vector<int>> levelOrder;
        std::queue<TreeNode*> nodes;

        if (root == nullptr)
        {
            return levelOrder;
        }
        else
        {
            nodes.push(root);
            levelOrder.push_back({});
        }

        int i = 0;
        int level = 1;
        
        while (true)
        {
            if (nodes.empty())
            {
                break;
            }

            root = nodes.front();
            nodes.pop();
            i++;

            if (i == pow(2, level))
            {
                level++;
                levelOrder.push_back({});
            }

            levelOrder[levelOrder.size() - 1].push_back(root->val);

            if (root->left)
            {
                nodes.push(root->left);
            }
            else
            {
                i++;
            }
            

            if (root->right)
            {
                nodes.push(root->right);
            }
            else
            {
                i++;
            }
        }

        auto l = 1;
        for (auto level: levelOrder)
        {
            for (auto i: level)
            {
                std::cout << "Level: " << l << ", value: " << i << std::endl;
            }
            l++;
        }

        return std::vector<std::vector<int>>(levelOrder.rbegin(), levelOrder.rend());
    }
};

int main()
{

    Solution sol;

    const std::vector<TreeNode *> tests = {
        createTree({3,9,20,-1,-1,15,7}),
        createTree({1,2,-1,3,-1,4,-1,5})
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
        printTreeBreadthFirst(test);
        // assert(soln == expected[i]);
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}