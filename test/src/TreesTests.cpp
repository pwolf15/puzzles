#include "CppUTest/TestHarness.h"

#include "Trees.hpp"

TEST_GROUP(Trees)
{
 
};

static void deleteTree(TreeNode* node)
{
    if (node == nullptr)
    {
        return;
    }
    else
    {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

TEST(Trees, ConvertSortedArrayToBST)
{
    std::vector<int> sorted = { -10,-3,0,5,9 };
    auto node = sortedArrayToBST(sorted);
    CHECK_EQUAL(0, node->val);
    CHECK_EQUAL(-3, node->left->val);
    CHECK_EQUAL(9, node->right->val);
    CHECK_EQUAL(-10, node->left->left->val);
    CHECK_EQUAL(5, node->right->left->val);
    
    auto root = node;
    deleteTree(root);
};

TEST(Trees, IsValidBST)
{
    TreeNode* node  = new TreeNode(2);
    node->left      = new TreeNode(1);
    node->right     = new TreeNode(3);

    CHECK(isValidBST(node));

    deleteTree(node);

    node                = new TreeNode(5);
    node->left          = new TreeNode(1);
    node->right         = new TreeNode(4);
    node->right->left   = new TreeNode(3);
    node->right->right  = new TreeNode(6);

    CHECK(!isValidBST(node));

    deleteTree(node);
};