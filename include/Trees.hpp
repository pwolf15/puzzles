#include <vector>
#include <string>

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