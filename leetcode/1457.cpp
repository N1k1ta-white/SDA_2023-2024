#include <iostream>
#include <vector>
#include <unordered_map>

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

    class Palindrom {
        int set;
        int countOdd;
    public:

        Palindrom() {
            set = 0;
            countOdd = 0;
        }

        void addNumber(int num) {
            num--;
            int mask = 1;
            mask = mask << num;
            if (set & mask) {
                set ^= mask;
                countOdd--;
            } else {
                set |= mask;
                countOdd++;
            }
        }

        bool isPalindrom() {
            return countOdd == 1 || countOdd == 0;
        }
    };

    int recursiveSearch(TreeNode* root, Palindrom pal) {
        if (!root) {
            return 0;
        }
        pal.addNumber(root->val);
        if (!root->left && !root->right) {
            return pal.isPalindrom() ? 1 : 0;
        }
        return recursiveSearch(root->left, pal) + recursiveSearch(root->right, pal);
    }

    int pseudoPalindromicPaths (TreeNode* root) {
        Palindrom pal;
        return recursiveSearch(root, pal);
    }
};

int main() {
    Solution sol;
    TreeNode* root32 = new TreeNode(3);
    TreeNode* root13 = new TreeNode(1);
    TreeNode* root31 = new TreeNode(3, root32, root13);
    TreeNode* root12 = new TreeNode(1);
    TreeNode* root11 = new TreeNode(1, root12, nullptr);
    TreeNode *root = new TreeNode(2, root31, root11);
    cout << sol.pseudoPalindromicPaths(root);

}