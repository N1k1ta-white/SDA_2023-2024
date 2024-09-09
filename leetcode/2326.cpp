//
// Created by Nikita on 09.09.2024.
//
#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {

    static const vector<vector<int>> directions;
    vector<vector<int>> matrix;
    int currDirection;

    static constexpr int DEFAULT_VALUE = -1;

    static const int X = 0;
    static const int Y = 1;

    static vector<vector<int>> initMatrix(int m, int n) {
        return vector<vector<int>>(m, vector<int>(n, DEFAULT_VALUE));
    }

    bool checkBounds(vector<int>& pos) const {
        return matrix[0].size() > pos[X] && pos[X] >= 0 && matrix.size() > pos[Y] && pos[Y] >= 0;
    }

    bool isUntouched(vector<int>& pos) const {
        return matrix[pos[Y]][pos[X]] == DEFAULT_VALUE;
    }

    void moveForward(vector<int>& pos, int currDirection) {
        pos[X] += directions[currDirection][X];
        pos[Y] += directions[currDirection][Y];
    }

    void moveBack(vector<int>& pos, int currDirection) {
        pos[X] -= directions[currDirection][X];
        pos[Y] -= directions[currDirection][Y];
    }

    int getNextDirection() {
        return (currDirection + 1) % directions.size();
    }

    void setValue(vector<int> pos, int value) {
        matrix[pos[Y]][pos[X]] = value;
    }

    void makeTurn(vector<int>& pos) {
        moveBack(pos, currDirection);
        currDirection = getNextDirection();
        moveForward(pos, currDirection);
    }

public:
    vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {
        matrix = initMatrix(m, n);

        vector<int> pos = {0, 0};
        currDirection = 0;

        while (head) {
            int value = head->val;

            if (!checkBounds(pos) || !isUntouched(pos)) {
                makeTurn(pos);
            }

            setValue(pos, value);
            moveForward(pos, currDirection);
            head = head->next;
        }

        return matrix;
    }
};

const vector<vector<int>> Solution::directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int main() {
    ListNode* head = new ListNode(3, new ListNode(7, new ListNode(1, new ListNode(8, new ListNode(1)))));
    Solution solution;

    vector<vector<int>> res = solution.spiralMatrix(3, 3, head);

    for (int y = 0; y < res.size(); y++) {
        for (int x = 0; x < res[0].size(); ++x) {
            cout << res[y][x] << " ";
        }
        cout << endl;
    }
}