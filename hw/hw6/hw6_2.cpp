#include <iostream>
using namespace std;

struct TreeNode {
    int ind;
    long size = 1;
    TreeNode* left;
    TreeNode* right;
};
TreeNode nodes[10000000];

long searcherOfSizes(TreeNode* root) {
    if (root == nullptr)
        return 0;
    if (root->left == nullptr && root->right == nullptr)
        return 1;
    root->size += searcherOfSizes(root->left) + searcherOfSizes(root->right);
    return root->size;
}

long findMaxRes(TreeNode* root, long n) {
    long res = -1;
    for (long i = 0; i < n; i++) {
        long temp = (i == 0 ? 1 : n - nodes[i].size) *
                (nodes[i].left == nullptr ? 1 : nodes[i].left->size) *
                (nodes[i].right == nullptr ? 1 : nodes[i].right->size);
        if (temp > res)
            res = temp;
    }
    return res;
}

int main() {
    long n, l, r, maxResult;
    cin >> n;

    for (long i = 0; i < n; i++) {
        cin >> l >> r;
        nodes[i].ind = i;
        nodes[i].left = (l == -1 ? nullptr : &nodes[l]);
        nodes[i].right = (r == -1 ? nullptr : &nodes[r]);
    }

    TreeNode* root = &nodes[0];
    searcherOfSizes(root);
    maxResult = findMaxRes(root, n);
    cout << maxResult;
}