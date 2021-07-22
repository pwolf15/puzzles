#ifndef TREES_H
#define TREES_H

#include <vector>
#include <string>
#include <memory>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode *sortedArrayToBST(std::vector<int> &nums);

bool isValidBST(TreeNode *root);

std::vector<double> averageOfLevels(TreeNode* root);

std::vector<std::string> binaryTreePaths(TreeNode* root);

std::string tree2str(TreeNode* t);

int findTilt(TreeNode* root);

bool isCousins(TreeNode* root, int x, int y);

int diameterOfBinaryTree(TreeNode* root);

std::vector<int> findMode(TreeNode* root);

int rangeSumBST(TreeNode* root, int low, int high);

TreeNode* increasingBST(TreeNode* root);

int sumRootToLeaf(TreeNode* root);

std::vector<int> preorderTraversal(TreeNode* root);

std::vector<std::vector<std::string>> printTree(TreeNode* root);

TreeNode* bstToGst(TreeNode* root);

TreeNode* fromArray(std::vector<int> arr);

template <typename T>
struct BinaryTreeNode {
    T data;
    std::unique_ptr<BinaryTreeNode<T>> left, right;
};

std::unique_ptr<BinaryTreeNode<int>> fromArrayBT(std::vector<int> arr);

void preorder(const std::unique_ptr<BinaryTreeNode<int>>& root);

void inorder(const std::unique_ptr<BinaryTreeNode<int>>& root);

void postorder(const std::unique_ptr<BinaryTreeNode<int>>& root);

bool IsBalanced(const std::unique_ptr<BinaryTreeNode<int>>& tree);

template <typename T>
struct BinaryTreeNodeP {
    T data;
    std::unique_ptr<BinaryTreeNodeP<T>> left, right; 
    BinaryTreeNodeP<T>* parent;
};

std::unique_ptr<BinaryTreeNodeP<int>> fromArrayBTP(std::vector<int> arr);

BinaryTreeNodeP<int>* Lca(const std::unique_ptr<BinaryTreeNodeP<int>>& node0,
    const std::unique_ptr<BinaryTreeNodeP<int>>& node1
);

#endif