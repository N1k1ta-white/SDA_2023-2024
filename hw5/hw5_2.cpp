#include <iostream>
#include <deque>
#include <vector>

using namespace std;

class Solution {
    private:
    static inline int max(int n1, int n2) {
        return n1 > n2 ? n1 : n2;
    }
public:
    int largestRectangleArea(vector<int>& heights) {
        deque<pair<int, int>> deq;
        pair<int, int> get;
        int maxArea = 0, start, n = heights.size();
        for (int i = 0; i < n; i++) {
            start = i;
            while (!deq.empty() && deq.back().first > heights[i]) {
                get = deq.back();
                maxArea = max(maxArea, (i - get.second) * get.first);
                deq.pop_back();
                start = get.second;
            }
            deq.push_back(make_pair(heights[i], start));
        }
        while (!deq.empty()) {
            get = deq.front();
            maxArea = max(maxArea, (n - get.second) * get.first);
            deq.pop_front();
        }
        return maxArea;
    }
};

int main() {
}