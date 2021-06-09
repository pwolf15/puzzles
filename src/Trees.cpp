#include "Trees.hpp"
#include <limits>
#include <iostream>
#include <queue>
#include <numeric>
#include <vector>
#include <string>
#include <stack>
#include <unordered_map>
#include <map>
#include <cmath>

TreeNode* sortedArrayToBST(std::vector<int>& nums)
{
    if (nums.empty())
    {
        return nullptr;
    }
    auto tree = new TreeNode(nums[nums.size() / 2]);
    std::vector<int> left;
    std::vector<int> right;
    std::copy(nums.begin(), nums.begin() + nums.size() / 2, std::back_inserter(left));
    std::copy(nums.begin() + nums.size() / 2 + 1, nums.end(), std::back_inserter(right));
    tree->left = sortedArrayToBST(left);
    tree->right = sortedArrayToBST(right);
    
    return tree;
}

bool isValidBSTUtil(TreeNode* root, long int min, long int max)
{
    if (root == nullptr)
    {
        return true;
    }

    if (root->left && (root->left->val >= root->val || root->left->val <= min)) return false;
    if (root->right && (root->right->val <= root->val || root->right->val >= max)) return false;

    return isValidBSTUtil(root->left, min, root->val) && isValidBSTUtil(root->right, root->val, max);
}

bool isValidBST(TreeNode *root)
{
    return isValidBSTUtil(root, std::numeric_limits<long int>::min(), std::numeric_limits<long int>::max());
}

// space complexity: O(n)
// time complexity: O(n)
std::vector<double> averageOfLevels_PW(TreeNode* root)
{
    std::queue<TreeNode*> nodes;
    std::vector<double> averages;

    nodes.push(root);
    while (!nodes.empty())
    {
        std::queue<TreeNode*> new_nodes;
        std::vector<long long> level;

        while (!nodes.empty())
        {
            auto top = nodes.front();
            nodes.pop();
            level.push_back(top->val);
            if (top->left)
            {
                new_nodes.push(top->left);
            }
            if (top->right)
            {
                new_nodes.push(top->right);
            }
        }

        if (!level.empty())
        {
            long long sum = std::accumulate(level.begin(), level.end(), 0.0);
            averages.push_back(sum / (double)level.size());
        }

        std::swap(new_nodes, nodes);
    }
    
    return averages;
}

// space complexity: O(n)
// time complexity: O(n)
std::vector<double> averageOfLevels_PW2(TreeNode* root)
{
    std::queue<TreeNode*> nodes;
    std::vector<double> averages;
    double sum = 0;
    int count = 0;

    nodes.push(root);
    while (!nodes.empty())
    {
        std::queue<TreeNode*> new_nodes;
        std::vector<long long> level;
        sum = 0;
        count = 0;

        while (!nodes.empty())
        {
            auto top = nodes.front();
            sum += top->val;
            count++;

            nodes.pop();
            if (top->left)
            {
                new_nodes.push(top->left);
            }
            if (top->right)
            {
                new_nodes.push(top->right);
            }
        }

        if (count)
        {
            averages.push_back(sum / (double)count);
        }

        std::swap(new_nodes, nodes);
    }
    
    return averages;
}

std::vector<double> averageOfLevels(TreeNode* root)
{
    return averageOfLevels_PW2(root);
}

// time complexity: O(n)
// space complexity: O(n * log n)
std::vector<std::string> binaryTreePaths(TreeNode* root)
{
    if (root == nullptr) 
    {
        return {};
    }
    else {
        std::vector<std::string> left = binaryTreePaths(root->left);
        std::vector<std::string> right = binaryTreePaths(root->right);
        std::vector<std::string> paths;
        if (!left.empty())
        {
            for (auto path: left)
            {
                path = std::to_string(root->val) + "->" + path;
                paths.emplace_back(path);
            }
        }
        if (!right.empty())
        {
            for (auto path: right)
            {
                path = std::to_string(root->val) + "->" + path;
                paths.emplace_back(path);
            }
        }

        if (right.empty() && left.empty())
        {
            paths.emplace_back(std::to_string(root->val));
        }

        return paths;
    }
}

// time complexity: O(n), visit each node only once
// space complexity: O(n^2), construct new string for each node visit
std::string tree2str(TreeNode* t)
{
    if (!t) return "";
    std::string result = "";

    result += std::to_string(t->val);
    std::string left = tree2str(t->left);
    std::string right = tree2str(t->right);

    if (!right.empty())
    {
        // if right non-empty, always append both.
        //  case 1: left non-empty, would append in any case
        //  case 2: left empty, need to append to disambiguate with right-empty case
        result += "(" + left + ")";
        result += "(" + right + ")";
    }
    else if (!left.empty())
    {
        // if left non-empty and right empty, always append only left
        result += "(" + left + ")";
    }
    return result;
}

int sumNodes(TreeNode* root)
{
    if (!root)
    {
        return 0;
    }
    else {
        return root->val + sumNodes(root->left) + sumNodes(root->right);
    }
}

void tilt(TreeNode* root, std::vector<int>& tiltValues)
{
    if (!root)
    {
        return;
    }
    else if (!root->left && !root->right)
    {
        tiltValues.push_back(0);
        return;
    }
    else
    {
        int val = abs(sumNodes(root->left) - sumNodes(root->right));
        tiltValues.push_back(val);
        tilt(root->left, tiltValues);
        tilt(root->right, tiltValues);
    }
}

// time complexity: O(n!)
// space complexity: O(n)
int findTilt(TreeNode* root)
{
    std::vector<int> tiltValues;
    tilt(root, tiltValues);

    return std::accumulate(tiltValues.begin(), tiltValues.end(), 0);
}

int nodeDepth(TreeNode* root, int val)
{
    if (!root)
    {
        return -1;
    }
    else if (root->val == val)
    {
        return 0;
    }
    else {
        int depthLeft = nodeDepth(root->left, val);
        int depthRight = nodeDepth(root->right, val);

        // depth == -1 => node not found in this tree
        if (depthLeft != -1)
        {
            return 1 + depthLeft;
        }
        else if (depthRight != -1)
        {
            return 1 + depthRight;
        }
        else
        {
            return -1;
        }
    }
}

TreeNode* getParent(TreeNode* root, int val)
{
    if (!root)
    {
        return root;
    }
    else {
        if ((root->right && root->right->val == val))
        {
            return root;
        }
        else if ((root->left && root->left->val == val))
        {
            return root;
        }
        else {
            TreeNode* left = getParent(root->left, val);
            TreeNode* right = getParent(root->right, val);
            if (left) return left;
            if (right) return right;
            return nullptr;
        }
    }
}

// time complexity: O(4*n), need to traverse tree to find depth of x, depth of y, parent of x, parent of y
// space complexity: O(1)
bool isCousins(TreeNode* root, int x, int y)
{
    TreeNode* parent1 = getParent(root, x);
    TreeNode* parent2 = getParent(root, y);
    return nodeDepth(root, x) == nodeDepth(root, y) && (parent1 != parent2);
}

int maxHeight(TreeNode* node)
{
    if (!node) return 0;
    else 
    {
        return std::max(1 + maxHeight(node->left), 1 + maxHeight(node->right));
    }
}

int diameterOfBinaryTree(TreeNode* root)
{
    return maxHeight(root->left) + maxHeight(root->right);
}

void findModeHelper(TreeNode* root, std::unordered_map<int, int>& m)
{
    if (!root)
    {
        return;
    }
    else
    {
        m[root->val]++;
        findModeHelper(root->left, m);
        findModeHelper(root->right, m);
    }
}

// time complexity: O(n), traverse entire tree, traverse map with node value to frequency
// space complexity: O(n), need map for value to frequency, map for frequency to values
std::vector<int> findMode(TreeNode* root)
{
    std::unordered_map<int, int> m;
    std::map<int, std::vector<int>> counts;
    findModeHelper(root, m);

    for (auto pair: m)
    {
        if (counts.find(pair.second) == counts.end())
        {
            std::vector<int> vals;
            counts[pair.second] = vals;
            counts[pair.second].push_back(pair.first);
        }
        else
        {
            counts[pair.second].push_back(pair.first);
        }
    }

    return counts.rbegin()->second;
}

// time complexity: O(n)
// space complexity: O(1)
int rangeSumBST_PW1(TreeNode* root, int low, int high)
{
    if (root == nullptr)
    {
        return 0;
    }
    
    int sum = rangeSumBST(root->left, low, high) + rangeSumBST(root->right, low, high);
    return root->val >= low && root->val <= high ? sum + root->val : sum;
}

// time complexity: O(n)
// space complexity: O(1)
int rangeSumBST_PW2(TreeNode* root, int low, int high)
{
    if (root == nullptr)
    {
        return 0;
    }
    
    int sum = 0;
    if (root->val < low)
    {
        return rangeSumBST(root->right, low, high);
    }
    else if (root->val == low)
    {
        return low + rangeSumBST(root->right, low, high);
    }
    else if (root->val > low && root->val < high)
    {
        return root->val + rangeSumBST(root->left, low, high) + rangeSumBST(root->right, low, high);
    }
    else if (root->val == high)
    {
        return root->val + rangeSumBST(root->left, low, high);
    }
    else
    {
        return rangeSumBST(root->left, low, high);
    }
}

int rangeSumBST(TreeNode* root, int low, int high)
{
    return rangeSumBST_PW2(root, low, high);
}

// time complexity: O(n)
// space complexity: O(n)
TreeNode* increasingBST(TreeNode* root)
{
    if (!root)
    {
        return root;
    }
    else
    {
        auto newRoot = increasingBST(root->left);
        if (!newRoot)
        {
            // it's already the lowest-valued noode
            newRoot = root;
            newRoot->right = increasingBST(root->right);
        }
        else 
        {
            auto temp = root;

            // re-assign root
            root = newRoot;
            newRoot->left = nullptr;

            // find largest node in LHS tree
            while (root->right)
            {
                root = root->right;
            }

            // assign previous root to right child of largest LHS tree node
            root->right = temp;
            temp->right = increasingBST(temp->right);

            // assign left child of previous root to null
            temp->left = nullptr;
        }
        
        return newRoot;
    }
}


int sumRootToLeaf(TreeNode* root)
{
    return 0;
}

void preorderTraversal(TreeNode* root, std::vector<int>& nodes)
{
    if (root == nullptr)
    {
        return;
    }
    else
    {
        preorderTraversal(root->left, nodes);
        preorderTraversal(root->right, nodes);
        nodes.push_back(root->val);
    }
}

std::vector<int> preorderTraversal(TreeNode* root)
{
    std::vector<int> nodes;
    
    preorderTraversal(root, nodes);

    return nodes;
}

void updateTree(std::vector<std::vector<std::string>>& mat, int r, int c, int height, TreeNode* root)
{
    if (!root)
    {
        return;
    }
    else
    {
        mat[r][c] = std::to_string(root->val);
        
        if (root->left)
        {
            updateTree(mat, r+1, c-pow(2, height-r-2), height, root->left);
        }
        if (root->right)
        {
            updateTree(mat, r+1, c+pow(2, height-r-2), height, root->right);
        }
    }
}

std::vector<std::vector<std::string>> printTree(TreeNode* root)
{
    const auto height = [](TreeNode* root) {
        auto height_impl=[](TreeNode* root,auto& height_ref) mutable {
            if (!root)
            {
                return 0;
            }
            else
            {
                return std::max(1 + height_ref(root->left, height_ref), 1 + height_ref(root->right, height_ref));
            }
        };
        return height_impl(root,height_impl);
    };

    int h = height(root);
    std::vector<std::vector<std::string>> mat(h);
    for (size_t i = 0; i < mat.size(); ++i)
    {
        mat[i].resize(round(pow(2, h) - 1));
    }

    updateTree(mat, 0, round(pow(2, h) - 1) / 2, h, root);

    return mat;
}