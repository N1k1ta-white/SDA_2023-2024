#include <unordered_map>
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct TreeNode {
    TreeNode *left;
    TreeNode *right;
    int val;

    TreeNode(int val, TreeNode *left, TreeNode *right) : left(left), right(right), val(val) {}
};

struct TextNode {
    int val;
    int left;
    int right;
};

class Tree {
    TreeNode *root;
    int maxSum;

    TreeNode *addNode(int i, const vector<TextNode> &arr) {
        TreeNode *node = nullptr;
        if (i == -1)
            return node;
        node = new TreeNode(arr[i].val, addNode(arr[i].left, arr),
                            addNode(arr[i].right, arr));
        return node;
    }

    void deleteTreeNode(TreeNode* node) {
        if (node->right)
            deleteTreeNode(node->right);
        if (node->left)
            deleteTreeNode(node->left);
        delete node;
    }

    int getLongestPathInSubTree(TreeNode* sub) {
        if (!sub)
            return 0;
        if (sub->val > maxSum)
            maxSum = sub->val;
        int left = getLongestPathInSubTree(sub->left),
                right = getLongestPathInSubTree(sub->right);
        if (left < sub->val && left < 0)
            left = sub->val;
        else
            left += sub->val;
        if (right < sub->val && right < 0)
            right = sub->val;
        else
            right += sub->val;
        int maxSubPath = max(max(left, right), left + right - sub->val);
        if (maxSubPath > maxSum)
            maxSum = maxSubPath;
        return (left > right ? left : right);
    }

public:

    ~Tree() {
        deleteTreeNode(root);
    }

    Tree(const vector<TextNode> &arr) : maxSum(INT_MIN) {
        root = addNode(0, arr);
    }

    Tree(const Tree& tr) = delete;
    Tree operator=(const Tree& tr) = delete;

    int findLongestPath() {
        int path = getLongestPathInSubTree(root);
        return path > maxSum ? path : maxSum;
    }

};


int main() {
    int n;
    cin >> n;
    vector<TextNode> arr(n);

    for (int i = 0; i < n; ++i)
        cin >> arr[i].val >> arr[i].left >> arr[i].right;

    Tree tree(arr);
    cout << tree.findLongestPath();
}