#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <queue>
#include <cmath>

using namespace std;

#include "Trees.hpp"

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