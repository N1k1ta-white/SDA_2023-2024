#include <iostream>
#include <queue>

using namespace std;

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {

    bool checkVal(int val, int level) {
        if (level == 0) {
            return val % 2;
        }
        return level % 2 != 0 == !(val % 2);
    }


    bool checkOrder(int level, int curr, int prev) {
        return (level & 1) ? curr > prev : curr < prev;
    }

public:
    bool isEvenOddTree(TreeNode* root) {
        queue<pair<TreeNode*, int>> queue;
        queue.push({root, 0});
        int currLev = -1;
        int prev;
        while (!queue.empty()) {
            pair<TreeNode*, int> curr = queue.front();
            queue.pop();
            if (curr.first) {
                if (currLev != curr.second) {
                    currLev = curr.second;
                } else if (!checkOrder(currLev, curr.first->val, prev)) {
                    return false;
                }
                prev = curr.first->val;
                if (checkVal(curr.first->val, curr.second)) {
                    queue.push({curr.first->right, curr.second + 1});
                    queue.push({curr.first->left, curr.second + 1});
                } else {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    Solution sol;
    TreeNode* treeNode = new TreeNode(1, new TreeNode(10), new TreeNode(4));
    cout << sol.isEvenOddTree(treeNode);
}