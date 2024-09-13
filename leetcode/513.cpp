#include <iostream>
#include <queue>
#include <set>
#include "structures/TreeNode.h"

using namespace std;

class Solution {

    TreeNode* bfs(TreeNode* root) {
        queue<pair<TreeNode*, int>> q;
        q.push({root, 0});
        int currLevel = -1;
        TreeNode* left;
        while (!q.empty()) {
            pair<TreeNode*, int> curr = q.front();
            q.pop();
            if (curr.first) {
                if (curr.second != currLevel) {
                    left = curr.first;
                    currLevel = curr.second;
                }
                q.push({curr.first->left, curr.second + 1});
                q.push({curr.first->right, curr.second + 1});
            }
        }
        return left;
    }

public:
    int findBottomLeftValue(TreeNode* root) {
        return bfs(root)->val;
    }
};

int main() {
    TreeNode* root = new TreeNode(2, new TreeNode(1), new TreeNode(3));
    Solution sol;
    cout << sol.findBottomLeftValue(root);
}