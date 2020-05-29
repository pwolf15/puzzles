#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <queue>
#include <cmath>

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
    bool isSymmetric(TreeNode *root)
    {

        if (root == nullptr)
        {
            return true;
        }
        else
        {
            return isSymmetricRecursive(root->left, root->right);
        }
    }

private:
    bool isSymmetricRecursive(TreeNode *left, TreeNode *right)
    {
        if (left == nullptr && right == nullptr)
        {
            return true;
        }
        else if (left == nullptr || right == nullptr)
        {
            return false;
        }
        else if (left->val == right->val)
        {
            return isSymmetricRecursive(left->right, right->left) && isSymmetricRecursive(left->left, right->right);
        }
        else
        {
            return false;
        }
    }
};

TreeNode *createTree(std::vector<int> tree)
{
    // assume -1 means null child
    TreeNode *node = nullptr;
    TreeNode *head = nullptr;
    std::queue<TreeNode *> nodes;
    int i = 0;

    if (i >= tree.size())
    {
        return nullptr;
    }

    node = new TreeNode(tree[i++]);
    head = node;
    nodes.push(node);

    while (true)
    {
        if (i >= tree.size())
        {
            break;
        }

        if (nodes.empty())
        {
            break;
        }

        node = nodes.front();
        nodes.pop();

        if (tree[i] != -1)
        {
            node->left = new TreeNode(tree[i++]);
            nodes.push(node->left);
        }
        else
        {
            i++;
        }

        if (tree[i] != -1)
        {
            node->right = new TreeNode(tree[i++]);
            nodes.push(node->right);
        }
        else
        {
            i++;
        }
    }

    return head;
}

void printTreeBreadthFirst(TreeNode *node)
{
    // can't recurse on subtrees, because it will only print a branch at a time
    std::queue<TreeNode*> nodes;
    int level = 1;
    int i = 0;
    if (node == nullptr)
    {
        return;
    }

    nodes.push(node);
    while (true)
    {
        if (nodes.empty())
        {
            break;
        }

        node = nodes.front();
        nodes.pop();
        i++;

        if (i == pow(2, level))
        {
            level++;
        }

        std::cout << "Level: " << level << ", Value: " <<  node->val << std::endl;

        if (nodes.empty())
        {
            level++;
        }

        if (node->left)
        {
            nodes.push(node->left);
        }

        if (node->right)
        {
            nodes.push(node->right);
        }
    }
}

int main()
{

    Solution sol;

    const std::vector<TreeNode *> tests = {
        createTree({1, 2, 2, 3, 4, 4, 3}),
        createTree({1, 2, 2, -1, 3, -1, 3}),
        createTree({1,2,2}),
        createTree({1,2,2,-1,3,-1,3}),
    };

    const std::vector<bool> expected = {
        true,
        false,
        true,
        false,
    };

    int i = 0;
    for (auto test : tests)
    {
        auto soln = sol.isSymmetric(test);
        printTreeBreadthFirst(test);
        assert(soln == expected[i]);
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}