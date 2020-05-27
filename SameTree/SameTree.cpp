#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

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
    bool isSameTree(TreeNode *p, TreeNode *q)
    {
        if (p == nullptr && q == nullptr)
        {
            return true;
        }
        else if (p == nullptr)
        {
            return false;
        }
        else if (q == nullptr)
        {
            return false;
        }
        else
        {
            if (p->val == q->val)
            {
                return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
            }
            else
            {
                return false;
            }     
        }
    }
};

TreeNode *createTree(std::vector<int> tree)
{
    // assume -1 means null child
    TreeNode *node = nullptr;
    int i = 0;
    while (true)
    {
        if (i >= tree.size())
        {
            break;
        }

        node = new TreeNode(tree[i]);
        if (tree[i + 1] != -1)
        {
            node->left = new TreeNode(tree[i + 1]);
        }
        else if (tree[i + 1] != -1)
        {
            node->right = new TreeNode(tree[i + 1]);
        }

        i += 3;
    }

    return node;
}

int main()
{

    Solution sol;

    const std::vector<std::vector<TreeNode *>> tests = {
        {createTree({1, 2, 3}), createTree({1, 2, 3})},
        {createTree({1, 2}), createTree({1, -1, 2})},
        {createTree({1, 2, 1}), createTree({1, 1, 2})},
    };

    const std::vector<bool> expected = {
        true,
        false,
        false,
    };

    int i = 0;
    for (auto test : tests)
    {
        auto soln = sol.isSameTree(test[0], test[1]);
        assert(soln == expected[i]);
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}