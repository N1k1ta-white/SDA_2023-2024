#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>

using namespace std;

class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution {
    unordered_map<int, Node*> created;

    Node* deepCopy(Node* org) {
        if (!org) {
            return {};
        }

        stack<Node*> stack;
        stack.push(org);
        Node* curr;
        while (!stack.empty()) {
            curr = stack.top();
            stack.pop();
            if (!created.count(curr->val)) {
                created[curr->val] = new Node(curr->val);
                for (int i = 0; i < curr->neighbors.size(); ++i) {
                    if (created.count(curr->neighbors[i]->val)) {
                        created[curr->val]->neighbors.push_back(created[curr->neighbors[i]->val]);
                        created[curr->neighbors[i]->val]->neighbors.push_back(created[curr->val]);
                    } else {
                        stack.push(curr->neighbors[i]);
                    }
                }
            }
        }
        return created[org->val];
    }

public:
    Node* cloneGraph(Node* node) {
        if (!node) {
            return nullptr;
        }
        Node* root = deepCopy(node);
        return root;
    }
};

int main() {
    Solution sol;
    Node* a = new Node(1);
    Node* b = new Node(2);
    Node* c = new Node(3, {a, b});
    Node* d = new Node(4, {c, a});
    a->neighbors.push_back(d);
    Node* res = sol.cloneGraph(d);
}