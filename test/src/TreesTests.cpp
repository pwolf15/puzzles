#include "CppUTest/TestHarness.h"

#include <vector>
#include <iostream>
#include <string>

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

TEST(Trees, AverageOfLevels)
{
    TreeNode* node = new TreeNode(3);
    node->left = new TreeNode(9);
    node->right = new TreeNode(20);
    node->right->left = new TreeNode(15);
    node->right->right = new TreeNode(7);

    std::vector<double> expected = { 3, 14.5, 11 };
    auto result = averageOfLevels(node);
    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    deleteTree(node);

    node = new TreeNode(2147483647);
    node->left = new TreeNode(2147483647);
    node->right = new TreeNode(2147483647);

    expected = { 2147483647, 2147483647 };
    result = averageOfLevels(node);
    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    deleteTree(node);
};

TEST(Trees, BinaryTreePaths)
{
    TreeNode* node = new TreeNode(1);
    node->left = new TreeNode(2);
    node->right = new TreeNode(3);
    node->left->right = new TreeNode(5);

    std::vector<std::string> expected = { "1->2->5", "1->3" };
    auto result = binaryTreePaths(node);
    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    deleteTree(node);
};

TEST(Trees, Tree2Str)
{
    TreeNode* node = new TreeNode(1);
    node->left = new TreeNode(2);
    node->right = new TreeNode(3);
    node->left->left = new TreeNode(4);
    CHECK_EQUAL("1(2(4))(3)", tree2str(node));
    deleteTree(node);

    node = new TreeNode(1);
    node->left = new TreeNode(2);
    node->right = new TreeNode(3);
    node->left->right = new TreeNode(4);
    CHECK_EQUAL("1(2()(4))(3)", tree2str(node));

    deleteTree(node);
}

TEST(Trees, FindTilt)
{
    TreeNode* node = new TreeNode(1);
    node->left = new TreeNode(2);
    node->right = new TreeNode(3);

    CHECK_EQUAL(1, findTilt(node));

    deleteTree(node);
    
    node = new TreeNode(4);
    node->left = new TreeNode(2);
    node->right = new TreeNode(9);
    node->left->left = new TreeNode(3);
    node->left->right = new TreeNode(5);
    node->right->right = new TreeNode(7);

    CHECK_EQUAL(15, findTilt(node));

    deleteTree(node);
}

TEST(Trees, IsCousins)
{
    TreeNode* node = new TreeNode(1);
    node->left = new TreeNode(2);
    node->right = new TreeNode(3);
    node->left->right = new TreeNode(4);
    node->right->right = new TreeNode(5);

    CHECK(isCousins(node, 5, 4));

    deleteTree(node);

    node = new TreeNode(1);
    node->left = new TreeNode(2);
    node->right = new TreeNode(3);
    node->left->left = new TreeNode(4);

    CHECK(!isCousins(node, 4, 3));

    deleteTree(node);

    node = new TreeNode(1);
    node->left = new TreeNode(2);
    node->right = new TreeNode(3);
    node->left->right = new TreeNode(4);

    CHECK(!isCousins(node, 2, 3));

    deleteTree(node);
}

TEST(Trees, DiameterOfBinaryTree)
{
    TreeNode* node = new TreeNode(1);
    node->right = new TreeNode(3);
    node->left = new TreeNode(2);
    node->left->left = new TreeNode(4);
    node->left->right = new TreeNode(5);

    CHECK_EQUAL(3, diameterOfBinaryTree(node));

    deleteTree(node);

    node = new TreeNode(1);
    node->left = new TreeNode(2);

    CHECK_EQUAL(1, diameterOfBinaryTree(node));

    deleteTree(node);
}

TEST(Trees, FindMode)
{
    TreeNode* node = new TreeNode(1);
    node->right = new TreeNode(2);
    node->right->left = new TreeNode(2);

    std::vector<int> expected = { 2 };
    std::vector<int> result = findMode(node);
    CHECK_EQUAL(result.size(), expected.size());
    for (size_t i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    deleteTree(node);

    node = new TreeNode(0);

    expected = { 0 };
    result = findMode(node);
    CHECK_EQUAL(result.size(), expected.size());
    for (size_t i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    deleteTree(node);
}

TEST(Trees, RangeSumBST)
{
    TreeNode* node = new TreeNode(10);
    node->left = new TreeNode(5);
    node->left->left = new TreeNode(3);
    node->left->right = new TreeNode(7);
    node->right = new TreeNode(15);
    node->right->right = new TreeNode(18);

    CHECK_EQUAL(32, rangeSumBST(node, 7, 15));

    deleteTree(node);

    node = new TreeNode(10);
    node->left = new TreeNode(5);
    node->left->left = new TreeNode(3);
    node->left->left->left = new TreeNode(1);
    node->left->right = new TreeNode(7);
    node->left->right->left = new TreeNode(6);
    node->right = new TreeNode(15);
    node->right->left = new TreeNode(13);
    node->right->right = new TreeNode(18);

    CHECK_EQUAL(23, rangeSumBST(node, 6, 10));

    deleteTree(node);
}

TEST(Trees, IncreasingBST)
{
    TreeNode* node = new TreeNode(5);
    node->left = new TreeNode(3);
    node->left->left = new TreeNode(2);
    node->left->left->left = new TreeNode(1);
    node->left->right = new TreeNode(4);
    node->right = new TreeNode(6);
    node->right->right = new TreeNode(8);
    node->right->right->left = new TreeNode(7);
    node->right->right->right = new TreeNode(9);

    TreeNode* root = increasingBST(node);
    
    auto temp = root;
    std::vector<int> expected = { 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int i = 0;
    while (temp)
    {
        CHECK_EQUAL(expected[i], temp->val);
        temp = temp->right;
        i++;
    }

    deleteTree(root);
}