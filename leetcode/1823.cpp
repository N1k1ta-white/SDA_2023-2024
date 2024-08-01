#include <iostream>

using namespace std;

class Solution {
public:
    int findTheWinner(int n, int k) {
        if (n == 1)
            return 1;
        return (findTheWinner(n - 1, k) + k - 1) % n + 1;
    }
};

int main() {
    Solution sol;
    cout << sol.findTheWinner(6, 5) << endl;
}