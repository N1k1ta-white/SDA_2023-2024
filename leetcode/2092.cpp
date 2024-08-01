#include <iostream>
#include <queue>
#include <set>

using namespace std;

vector<int> disjoint;

int getRoot(int x) {
    if (disjoint[x] == -1) {
        disjoint[x] = x;
    }
    if (disjoint[x] != x) {
        disjoint[x] = getRoot(disjoint[x]);
    }
    return disjoint[x];
}

void Union(int x, int y) {
    int r_x = getRoot(x), r_y = getRoot(y);
    disjoint[r_y] = r_x;
}

class Meet {
public:
    int first;
    int second;
    int time;
};

class MeetComparator {
public:
    bool operator()(const Meet& m1, const Meet& m2) {
        return m1.time > m2.time;
    }
};

class Solution {
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        priority_queue<Meet, vector<Meet>, MeetComparator> pq;
        disjoint.resize(n, -1);
        for (vector<int> meeting : meetings) {
            pq.push({meeting[0], meeting[1], meeting[2]});
        }
        Union(0, firstPerson);
        int time = -1;
        vector<int> members;
        while (!pq.empty()) {
            Meet curr = pq.top();
            pq.pop();
            if (time != curr.time) {
                for (int member : members) {
                    if (getRoot(member) != getRoot(0)) {
                        disjoint[member] = -1;
                    }
                }
                members.clear();
                time = curr.time;
            }
            members.push_back(curr.first);
            members.push_back(curr.second);
            Union(curr.first, curr.second);
        }
        vector<int> res;
        for (int i = 0; i < n; ++i) {
            if (getRoot(i) == getRoot(0)) {
                res.push_back(i);
            }
        }
        disjoint.clear();
        return res;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> vec = {{3,1,3}, {1,2,2}, {0,3,3}};
    vector<int> res = sol.findAllPeople(4, vec, 3);
    for (int n : res) {
        cout << n << " ";
    }
};