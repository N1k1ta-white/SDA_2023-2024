#include <iostream>
#include <vector>
#include <stack>
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