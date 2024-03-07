#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int bagOfTokensScore(vector<int>& tokens, int power) {
        int max = 0;
        sort(tokens.begin(), tokens.end());
        int start = 0, end = tokens.size() - 1, score = 0;
        for (int i = 0; i < tokens.size(); i++) {
            if (power < tokens[start]) {
                if (start < end && score > 0) {
                    score--;
                    power += tokens[end--];
                } else {
                    break;
                }
            } else {
                power -= tokens[start++];
                score++;
            }
            if (max < score) {
                max = score;
            }
        }
        return max;
    }
};

int main() {
    vector<int> vec = {100,200,300,400};
    Solution sol;
    cout << sol.bagOfTokensScore(vec, 200);
}