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

bool equal(TreeNode* l, TreeNode* r)
{
    if (!l || !r)
    {
        return l == r;
    }
    else
    {
        bool result = l->val == r->val;

        if (!result)
        {
            std::cout << l->val << " != " << r->val << std::endl;
        }
        
        return result && equal(l->left, r->left) && 
            equal(l->right, r->right);
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

TEST(Trees, PreorderTraversal)
{
    TreeNode* node = new TreeNode(1);
    node->right = new TreeNode(2);
    node->right->left = new TreeNode(3);

    std::vector<int> result = preorderTraversal(node);
    std::vector<int> expected = { 3, 2, 1};
    CHECK_EQUAL(expected.size(), result.size());
    for (int i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    deleteTree(node);

    node = nullptr;

    result = preorderTraversal(node);
    expected = { };
    CHECK_EQUAL(expected.size(), result.size());

    node = new TreeNode(1);
    result = preorderTraversal(node);
    expected = { 1 };
    CHECK_EQUAL(expected.size(), result.size());
    for (int i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    deleteTree(node);

    // node = new TreeNode(1);
    // node->left = new TreeNode(2);
    // result = preorderTraversal(node);
    // expected = { 1, 2 };
    // CHECK_EQUAL(expected.size(), result.size());
    // for (int i = 0; i < result.size(); ++i)
    // {
    //     CHECK_EQUAL(expected[i], result[i]);
    // }

    // deleteTree(node);
}

TEST(Trees, PrintTree)
{
    TreeNode* node = new TreeNode(1);
    node->left = new TreeNode(2);

    std::vector<std::vector<std::string>> expected = 
    {
        {"","1",""},
        {"2","",""}
    };
    auto result = printTree(node);
    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i].size(), result[i].size());
        for (size_t j = 0; j < expected[i].size(); ++j)
        {
            CHECK_EQUAL(expected[i][j], result[i][j]);
        }
    }

    deleteTree(node);

    node = new TreeNode(1);
    node->left = new TreeNode(2);
    node->left->right = new TreeNode(4);
    node->right = new TreeNode(3);

    expected = 
    {
        {"","","","1","","",""},
        {"","2","","","","3",""},
        {"","","4","","","",""}
    };

    result = printTree(node);
    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i].size(), result[i].size());
        for (size_t j = 0; j < expected[i].size(); ++j)
        {
            CHECK_EQUAL(expected[i][j], result[i][j]);
        }
    }

    deleteTree(node);
}

TEST(Trees, FromArray)
{
    TreeNode* expected = new TreeNode(3);
    expected->left = new TreeNode(3);
    expected->right = new TreeNode(2);

    std::vector<int> testArr = { 3, 3, 2};
    TreeNode* node = fromArray(testArr);

    CHECK(equal(expected, node));

    deleteTree(expected);
    deleteTree(node);

    expected = new TreeNode(4);
    expected->left = new TreeNode(1);
    expected->right = new TreeNode(6);
    expected->left->left = new TreeNode(0);
    expected->left->right = new TreeNode(2);
    expected->left->right->right= new TreeNode(3);
    expected->right->left = new TreeNode(5);
    expected->right->right = new TreeNode(7);
    expected->right->right->right = new TreeNode(8);

    testArr = { 4, 1, 6, 0, 2, 5, 7, -1, -1, -1, 3, -1, -1, -1, 8 };
    node = fromArray(testArr);

    CHECK(equal(expected, node));

    deleteTree(expected);
    deleteTree(node);
}

TEST(Trees, BstToGst)
{
    TreeNode* node = fromArray({ 1, 0, 2});
    TreeNode* root = bstToGst(node);

    TreeNode* expected = fromArray({3, 3, 2 });
    CHECK(equal(expected, root));

    deleteTree(root);
    deleteTree(expected);

    node = fromArray({4,1,6,0,2,5,7,-1,-1,-1,3,-1,-1,-1,8});
    root = bstToGst(node);
    expected = fromArray({30,36,21,36,35,26,15,-1,-1,-1,33,-1,-1,-1,8});

    CHECK(equal(expected, node));

    deleteTree(expected);
    deleteTree(node);
}

TEST(Trees, Traversal)
{
    std::unique_ptr<BinaryTreeNode<int>> node = fromArrayBT({ 314, 6, 6, 271, 561, 2, 271 });
    std::cout << "Preorder" << std::endl;
    preorder(node);
    std::cout << "Inorder" << std::endl;
    inorder(node);
    std::cout << "Postorder" << std::endl;
    postorder(node);
}

TEST(Trees, IsBalanced)
{
    auto n = fromArrayBT({});
    CHECK(IsBalanced(n));
    auto n1 = fromArrayBT({1,2,3});
    CHECK(IsBalanced(n1));
    auto n2 = fromArrayBT({1,1,-1});
    CHECK(IsBalanced(n2));
    auto n3 = fromArrayBT({1,1,-1,1,-1,-1,-1,1,-1,-1,-1,-1,-1,-1});
    CHECK(!IsBalanced(n3));
    auto n4 = fromArrayBT({ 1,2,2,3,-1,-1,3,4,-1,-1,4 });
    CHECK(!IsBalanced(n4));
}

BinaryTreeNodeP<int>* findNode(std::unique_ptr<BinaryTreeNodeP<int>>& node, int value)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    else if (node->data == value)
    {
        return node.get();
    }
    else
    {
        auto left = findNode(node->left, value);
        auto right = findNode(node->right, value);
        if (left)
        {
            return left;
        }
        if (right)
        {
            return right;
        }

        return nullptr;
    }
};

void printBTP(const std::unique_ptr<BinaryTreeNodeP<int>>& node)
{
    if (node == nullptr)
    {
        return;
    }
    else 
    {
        std::cout << node->data << std::endl;
        printBTP(node->left);
        printBTP(node->right);
    }
}

TEST(Trees, LCA)
{
    auto n = fromArrayBTP({});
    auto n1 = fromArrayBTP({2,1,3,-1,-1,-1,-1});

    CHECK(n1.get() == Lca(n1->left, n1->right));

    auto n2 = fromArrayBTP({314, 6, 6, 271, 561, 2, 271,-1,-1,-1,-1,-1,-1,-1,-1});
    CHECK(n2);
    CHECK(!n2->parent)
    CHECK(n2->left.get() == Lca(n2->left->left, n2->left->right));

    auto makeNode = [](int num) {
        auto newNode = std::make_unique<BinaryTreeNodeP<int>>();
        newNode->data = num;
        return std::move(newNode);
    };
    auto makeLeft = [](int num, BinaryTreeNodeP<int>* node) {
        node->left = std::make_unique<BinaryTreeNodeP<int>>();
        node->left->data = num;
        node->left->parent = node;
        return node->left.get();
    };
    auto makeRight = [](int num, BinaryTreeNodeP<int>* node) {
        node->right = std::make_unique<BinaryTreeNodeP<int>>();
        node->right->data = num;
        node->right->parent = node;
        return node->right.get();
    };

    auto A = makeNode(314);
    auto I = makeRight(6, A.get());
    auto B = makeLeft(6, A.get());
    auto C = makeLeft(271, B);
    auto F = makeRight(561, B);
    auto D = makeLeft(28, C);
    auto E = makeRight(0, C);
    auto G = makeRight(3, F);
    auto H = makeLeft(17, G);
    auto J = makeLeft(2, I);
    auto O = makeRight(271, I);
    auto K = makeRight(1, J);
    auto L = makeLeft(401, K);
    auto N = makeRight(257, K);
    auto M = makeRight(641, L);
    auto P = makeRight(28, O);

    // printBTP(A);

    CHECK(K == Lca(M, N));
    CHECK(A.get() == Lca(M, H));
    CHECK(I == Lca(J,O));
    CHECK(I == Lca(M,P));
}