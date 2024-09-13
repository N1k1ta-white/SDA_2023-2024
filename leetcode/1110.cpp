#include <unordered_map>
#include <vector>
#include "structures/TreeNode.h"

using namespace std;

class Solution {
    // unordered_map<TreeNode*, vector<vector<TreeNode*>>> subTree;
    unordered_map<TreeNode*, int> distance;
    unordered_map<int, TreeNode*> nodes;

    // vector<TreeNode*> subTreeCounter(TreeNode* sub) {
    //     if (sub->right)
    //         subTree[sub].push_back(subTreeCounter(sub->right));
    //     if (sub->left)
    //         subTree[sub].push_back(subTreeCounter(sub->left));
    //     vector<TreeNode*> ans(subrTree[sub]);
    //     ans.push_back(sub);
    //     return ans;
    // }

    void bfsDistance(TreeNode* root) {
        if (!root) return;
        queue<TreeNode*> q;
        q.push(root);

        int dist = 0;
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            if (node) {
                distance[node->val] = dist;
                nodes[node->val] = node;
                q.push(node->left);
                q.push(node->right);
            }
        }
    }

public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, [](pair<int, int> a, pair<int, int> b) {
            return a.second < b.second;
        }> pq;
        for (int val : to_delete) {
            pq.push({val, distance[val]});
        }
        while (!pq.empty()) {
            int val = pq.top().first;
            pq.pop();
            if (nodes[val]) {
                nodes[val]->left = nullptr;
                nodes[val]->right = nullptr;
            }
        }
        
    }
};

int main() {
    // Example usage of the Solution class
    Solution solution;
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);

    vector<int> to_delete = {3, 5};
    vector<TreeNode*> result = solution.delNodes(root, to_delete);

    // Print the roots of the remaining trees
    for (TreeNode* tree : result) {
        cout << tree->val << " ";
    }
    cout << endl;

    // Clean up memory
    delete root->left->left;
    delete root->left;
    delete root->right->left;
    delete root->right->right;
    delete root->right;
    delete root;

    return 0;
}
