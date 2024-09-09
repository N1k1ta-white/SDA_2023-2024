//
// Created by Nikita on 07.09.2024.
//
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {

    bool checkSubsequence(ListNode* head, TreeNode* node) {
        queue<pair<TreeNode*, ListNode*>> queue;
        queue.emplace(node, head);
        while (!queue.empty()) {
            pair<TreeNode*, ListNode*> curr = queue.front();
            queue.pop();
            if (curr.first && curr.second) {
                if (curr.first->val == curr.second->val) {
                    queue.emplace(curr.first->left, curr.second->next);
                    queue.emplace(curr.first->right, curr.second->next);
                }
            } else if (!curr.second) {
                return true;
            }
        }
        return false;
    }

    bool dfs(ListNode* head, TreeNode* node) {
        if (!node) {
            return false;
        }
        return dfs(head, node->left) || dfs(head, node->right) || checkSubsequence(head, node);
    }

public:
    bool isSubPath(ListNode* head, TreeNode* root) {
        return dfs(head, root);
    }
};

int main() {
    ListNode *head = new ListNode(1, new ListNode(10));
    TreeNode* root = new TreeNode(1, nullptr, new TreeNode(1, new TreeNode(10, new TreeNode(9), nullptr), new TreeNode(1)));

    Solution solution;
    cout << solution.isSubPath(head, root);
}