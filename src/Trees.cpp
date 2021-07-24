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

// time complexity: O(log n + n)
// space complexity: O(1)
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

void getValues(TreeNode* root, std::vector<int>& values)
{
    if (root == nullptr)
    {
        return;
    }
    else
    {
        getValues(root->left, values);
        values.push_back(root->val);
        getValues(root->right, values);
    }
}

void bstToGstHelper(TreeNode* root, const std::vector<int>& values)
{
    if (root == nullptr)
    {
        return;
    }
    else
    {
        int newVal = root->val;
        for (size_t i = 0; i < values.size(); ++i)
        {
            if (values[i] > root->val)
            {
                newVal += values[i];
            }
        }

        root->val = newVal;

        bstToGstHelper(root->left, values);
        bstToGstHelper(root->right, values);
    }
}

// time complexity: O(n^2)
// space complexity: O(n)
TreeNode* bstToGst(TreeNode* root)
{
    std::vector<int> values;
    getValues(root, values);
    bstToGstHelper(root, values);
    return root;
}

TreeNode* fromArray(std::vector<int> arr)
{
    if (arr.empty())
    {
        return nullptr;
    }

    TreeNode* root = new TreeNode(arr[0]);
    std::queue<TreeNode*> nodes;
    nodes.push(root);

    int i = 1;
    while (true)
    {
        auto node = nodes.front();
        nodes.pop();
        
        if (arr[i] != -1)
        {
            node->left = new TreeNode(arr[i]);
            nodes.push(node->left);
        }

        i++;
        if (arr[i] != -1)
        {
            node->right = new TreeNode(arr[i]);
            nodes.push(node->right);
        }
        i++;

        if (nodes.empty() || i >= arr.size())
        {
            break;
        }
    }

    return root;
}

std::unique_ptr<BinaryTreeNode<int>> fromArrayBT(std::vector<int> arr)
{
    if (arr.empty())
    {
        return nullptr;
    }

    std::unique_ptr<BinaryTreeNode<int>> root = std::make_unique<BinaryTreeNode<int>>();
    root->data = (arr[0]);
    std::queue<BinaryTreeNode<int>*> nodes;
    nodes.push(root.get());

    int i = 1;
    while (true)
    {
        BinaryTreeNode<int>* node = nodes.front();
        nodes.pop();
        
        if (arr[i] != -1)
        {
            node->left = std::make_unique<BinaryTreeNode<int>>();
            node->left->data = arr[i];
            nodes.push(node->left.get());
        }

        i++;
        if (arr[i] != -1)
        {
            node->right = std::make_unique<BinaryTreeNode<int>>();
            node->right->data = (arr[i]);
            nodes.push(node->right.get());
        }
        i++;

        if (nodes.empty())
        {
            break;
        }
    }

    return std::move(root);
}

// time complexity: O(n)
// space complexity: O(h), where h max depth of stack
//  log n <= h <= n
void preorder(const std::unique_ptr<BinaryTreeNode<int>>& root)
{
    if (root == nullptr)
    {
        return;
    }

    std::cout << root->data << std::endl;
    preorder(root->left);
    preorder(root->right);
}


// time complexity: O(n)
// space complexity: O(h), where h max depth of stack
void inorder(const std::unique_ptr<BinaryTreeNode<int>>& root)
{
    if (root == nullptr)
    {
        return;
    }

    inorder(root->left);
    std::cout << root->data << std::endl;
    inorder(root->right);
}

// time complexity: O(n)
// space complexity: O(h), where h max depth of stack
void postorder(const std::unique_ptr<BinaryTreeNode<int>>& root)
{
    if (root == nullptr)
    {
        return;
    }

    postorder(root->left);
    postorder(root->right);
    std::cout << root->data << std::endl;
}

int height(const std::unique_ptr<BinaryTreeNode<int>>& t)
{
    if (t == nullptr)
    {
        return 0;
    }
    else 
    {
        return 1 + std::max(height(t->left), height(t->right));
    }
}

// time complexity: O(n)
// space complexity: O(h)
bool IsBalanced_PW1(const std::unique_ptr<BinaryTreeNode<int>>& tree)
{
    if (tree == nullptr)
    {
        return true;
    }
    else
    {
        int h1 = height(tree->left);
        int h2 = height(tree->right);
        return std::abs(h1 - h2) <= 1 && IsBalanced(tree->left) && IsBalanced(tree->right);
    }
}

struct NodeHeight 
{
    int height;
    bool balanced;
};

// time complexity: O(n)
// space complexity: O(n)
NodeHeight getHeight(const std::unique_ptr<BinaryTreeNode<int>>& tree)
{
    if (tree == nullptr)
    {
        NodeHeight nh;
        nh.balanced = true;
        nh.height = 0;
        return nh;
    }
    else
    {
        NodeHeight nh;
        NodeHeight left, right;
        left = getHeight(tree->left);
        right = getHeight(tree->right);
        nh.height = 1 + std::max(left.height, right.height);
        nh.balanced = left.balanced && right.balanced && std::abs(right.height - left.height) <= 1;
        return nh;
    }
}

bool IsBalanced_PW2(const std::unique_ptr<BinaryTreeNode<int>>& tree)
{
    if (tree == nullptr)
    {
        return true;
    }
    else
    {
        NodeHeight nh = getHeight(tree);
        return nh.balanced;
    }
}

struct BalancedStatusWithHeight
{
    bool balanced;
    int height;
};

// First value of the return value indicates if tree is balanced, and if
// balanced the second value of the return value is the height of the tree.
BalancedStatusWithHeight CheckBalanced(const std::unique_ptr<BinaryTreeNode<int>>& tree)
{
    if (tree == nullptr)
    {
        return { true, -1 };
    }
    auto left_result = CheckBalanced(tree->left);
    if (!left_result.balanced)
    {
        return { false, 0 };
    }
    auto right_result = CheckBalanced(tree->right);
    if (!right_result.balanced)
    {
        return { false, 0 };
    }

    bool is_balanced = std::abs(left_result.height - right_result.height) <= 1;
    int height = std::max(left_result.height, right_result.height) + 1;
    return { is_balanced, height };
}

bool IsBalanced_EPI(const std::unique_ptr<BinaryTreeNode<int>>& tree)
{
    return CheckBalanced(tree).balanced;
}

bool IsBalanced(const std::unique_ptr<BinaryTreeNode<int>>& tree)
{
    return IsBalanced_EPI(tree);
}

std::unique_ptr<BinaryTreeNodeP<int>> fromArrayBTP(std::vector<int> arr)
{
    if (arr.empty())
    {
        return nullptr;
    }

    std::unique_ptr<BinaryTreeNodeP<int>> root = std::make_unique<BinaryTreeNodeP<int>>();
    root->data = (arr[0]);
    std::queue<BinaryTreeNodeP<int>*> nodes;
    nodes.push(root.get());

    std::cout << "Nodes size: " << nodes.size() << std::endl;

    int i = 1;
    while (true)
    {
        BinaryTreeNodeP<int>* node = nodes.front();
        nodes.pop();
        std::cout << "Nodes size: " << nodes.size() << std::endl;
        
        if (arr[i] != -1)
        {
            node->left = std::make_unique<BinaryTreeNodeP<int>>();
            node->left->data = arr[i];
            // node->left->parent = node;
            nodes.push(node->left.get());
        }

        i++;
        if (arr[i] != -1)
        {
            node->right = std::make_unique<BinaryTreeNodeP<int>>();
            node->right->data = (arr[i]);
            // node->right->parent = node;
            nodes.push(node->right.get());
        }
        i++;

        if (nodes.empty())
        {
            break;
        }
        else
        {
            std::cout << "nodes.front(): " << nodes.front()->data << std::endl;
            std::cout << "nodes.size(): " << nodes.size() << std::endl;
        }

        break;
    }

    return std::move(root);
}

int depth(BinaryTreeNodeP<int>* node)
{
    if (!node)
    {
        return 0;
    }
    else
    {
        return 1 + depth(node->parent);
    }
}

// time complexity: O(n)
// space complexity: O(1)
BinaryTreeNodeP<int>* Lca_PW(const std::unique_ptr<BinaryTreeNodeP<int>>& node0,
    const std::unique_ptr<BinaryTreeNodeP<int>>& node1
)
{
    int depth0 = depth(node0.get());
    int depth1 = depth(node1.get());

    BinaryTreeNodeP<int>* cur0 = node0.get();
    BinaryTreeNodeP<int>* cur1 = node1.get();

    if (depth0 < depth1)
    {
        int diff = depth1 - depth0;
        while (diff)
        {
            std::cout << cur1->data << std::endl;
            cur1 = cur1->parent;
            --diff;
        }
    }
    else if (depth1 < depth0)
    {
        int diff = depth0 - depth1;
        while (diff)
        {
            cur0 = cur0->parent;
            --diff;
        }
    }

    while (cur0 != cur1)
    {
        cur0 = cur0->parent;
        cur1 = cur1->parent;
    }

    return cur0;
}

// time complexity: O(n)
// space complexity: O(1)
BinaryTreeNodeP<int>* Lca_epi(const std::unique_ptr<BinaryTreeNodeP<int>>& node0,
    const std::unique_ptr<BinaryTreeNodeP<int>>& node1
)
{
    return nullptr;
}

BinaryTreeNodeP<int>* Lca(const std::unique_ptr<BinaryTreeNodeP<int>>& node0,
    const std::unique_ptr<BinaryTreeNodeP<int>>& node1
)
{
    return Lca_PW(node0, node1);
}