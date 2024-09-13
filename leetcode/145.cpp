#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include "structures/TreeNode.h"

using namespace std;

class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> stack;
        stack.push(root);
        TreeNode* curr;
        while (!stack.empty()) {
            curr = stack.top();
            stack.pop();
            if (curr) {
                stack.push(curr->left);
                stack.push(curr->right);
                res.push_back(curr->val);
            }
        }
        reverse(res.begin(), res.end());
        return res;
    }
};

int main() {

}