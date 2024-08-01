#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    string getString(int &pos, string& s, bool rev) {
        string word = "", first, last;
        for (int i = pos; i < s.size(); ++i) {
            if (i == '(') {
                first = s.substr(pos, i - pos - 1);
                word += getString(++pos, s, !rev);
                last = s.substr()
            }
        }
        if (rev) {
            reverse(first.begin(), first.end());
            reverse(last.begin(), last.end());
            reverse(center.begin(), center.end());
            return last + center + first;
        }
        return first + center + last;
    }
public:
    string reverseParentheses(string s) {
        string word = "";
        int pos = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                word += s.substr(pos, i - 1) + getString(i, s, true);
                pos = i + 1;
            }
        }
        return word;
    }
};

int main() {
    Solution sol;
    cout << sol.reverseParentheses("ta()usw((((a))))");
}