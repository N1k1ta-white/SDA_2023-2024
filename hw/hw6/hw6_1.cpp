#include <unordered_map>
#include <iostream>
#include <vector>

using namespace std;

struct Node {
    Node *left;
    Node *right;
    int val;
    int x;

    Node(int val, int x, Node *left, Node *right) : left(left), right(right), val(val), x(x) {}
};

struct TextNode {
    int index;
    int left;
    int right;
};

class Tree {
    Node *root;
    unordered_map<long, long> sums;
    int minX, maxX;

    Node *addNode(int x, int i, const vector<TextNode> &arr) {
        Node *node = nullptr;
        if (i == -1)
            return node;
        if (x < minX)
            minX = x;
        if (x > maxX)
            maxX = x;
        node = new Node(arr[i].index, x, addNode(x - 1, arr[i].left, arr),
                        addNode(x + 1, arr[i].right, arr));
        return node;
    }

    void searchingOfSum(Node *node) {

        if (!sums.count(node->x))
            sums[node->x] = node->val;
        else
            sums[node->x] += node->val;

        if (node->right)
            searchingOfSum(node->right);
        if (node->left)
            searchingOfSum(node->left);
    }

public:
    Tree(const vector<TextNode> &arr) : minX(0), maxX(0) {
        root = addNode(0, 0, arr);
    }

    void findSums() {
        searchingOfSum(root);

        for (int i = minX; i <= maxX; ++i) {
            if (sums.count(i))
                cout << sums[i] << " ";
        }

    }
};


int main() {
    int n;
    cin >> n;
    vector<TextNode> arr(n);

    for (int i = 0; i < n; ++i)
        cin >> arr[i].index >> arr[i].left >> arr[i].right;

    Tree tree(arr);
    tree.findSums();
}