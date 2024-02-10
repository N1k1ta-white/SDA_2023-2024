#include <queue>
#include <iostream>
#include <string>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : val(val), left(nullptr), right(nullptr) {}

    TreeNode(int val, TreeNode* left, TreeNode* right) : val(val), left(left), right(right) {}
};

class BinarySearchTree {
    TreeNode* root;

    void recursuveAddNum(TreeNode*& node, int num) {
        if (node == nullptr) {
            node = new TreeNode(num);
        } else if (node->val > num) {
            recursuveAddNum(node->left, num);
        } else if (node->val < num) {
            recursuveAddNum(node->right, num);
        }
    }

    void recursiveDelete(TreeNode* node) {
        if (node) {
            recursiveDelete(node->left);
            recursiveDelete(node->right);
            delete node;
        }
    }

    void recursivePrint(const TreeNode* node) const {
        if (node) {
            recursivePrint(node->left);
            cout << node->val << " ";
            recursivePrint(node->right);
        }
    }

    TreeNode*& recursiveFind(TreeNode*& curr, int num) {
        if (!curr) {
            throw "Tree hasn't this number";
        }
        if (num > curr->val) {
            return recursiveFind(curr->right, num);
        } else if (num < curr->val) {
            return recursiveFind(curr->left, num);
        } else {
            return curr;
        }
    }

    void recursiveFindNextBiggerNumber(TreeNode*& curr, int num, TreeNode*& res) {
        if (curr) {
            if (num - curr->val < num - res->val && num - curr->val > 0) {
                res = curr;
            }
            recursiveFindNextBiggerNumber(curr->right, num, res);
            recursiveFindNextBiggerNumber(curr->left, num, res);
        }
    }

public:

    BinarySearchTree() : root(nullptr) {}
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree) = delete;

    void addNum(int num) {
        recursuveAddNum(root, num);
    }

    void inorder() const {
        recursivePrint(root);
        cout << endl;
    }

    void levelorder() const {
        queue<TreeNode*> queue;
        queue.push(root);
        TreeNode* curr;
        while (!queue.empty()) {
            curr = queue.front();
            queue.pop();
            if (curr) {
                cout << curr->val << " ";
                queue.push(curr->left);
                queue.push(curr->right);
            }
        }
        cout << endl;
    }

    void deleteNum(int num) {
        TreeNode*& nodeDel = recursiveFind(root, num);
        if (nodeDel->right && nodeDel->left) {
            TreeNode* closer = nodeDel->right;
            closer->left = nodeDel->left;
            delete nodeDel;
            nodeDel = closer;
        } else if (nodeDel->left || nodeDel->right) {
            TreeNode* child = (nodeDel->right ? nodeDel->right : nodeDel->left);
            delete nodeDel;
            nodeDel = child;
        } else {
            delete nodeDel;
            nodeDel = nullptr;
        }
    }

    ~BinarySearchTree() {
        recursiveDelete(root);
    }
};


int main() {
    int N, num;
    cin >> N;
    string ans;
    BinarySearchTree tree;
    for (int i = 0; i < N; ++i) {
        cin >> ans;
        if (ans == "add") {
            cin >> num;
            tree.addNum(num);
        } else if (ans == "inorder") {
            tree.inorder();
        } else if (ans == "levelorder") {
            tree.levelorder();
        } else if (ans == "del") {
            cin >> num;
            tree.deleteNum(num);
        }
    }
}