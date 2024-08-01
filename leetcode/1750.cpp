#include <iostream>
#include <queue>

using namespace std;

class Solution {
public:
    int minimumLength(string s) {
        int st = 0, end = s.size() - 1;
        while (st <= end) {
            if (s[st] == s[end]) {
                while (s[st] == s[st + 1] && st <= end) {
                    st++;
                }
                while (s[end] == s[end - 1] && st <= end) {
                    end--;
                }
                if (st == end) {
                    return -1;
                }
                st++;
                end--;
            } else {
                break;
            }
        }
        return (end - st + 1 < 0 ? 0 : end - st + 1);
    }
};

int main() {
    Solution sol;
    cout << sol.minimumLength("bbbbbbbbbbbbbbbbbbbbbbbbbbbabbbbbbbbbbbbbbbccbcbcbccbbabbb");
}