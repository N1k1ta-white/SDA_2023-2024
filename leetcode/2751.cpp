#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

class Solution {
    struct Robot {
        int position;
        int health;
        char direction;
        int posArr;
    };
    
    class Comparator {
    public:
        bool operator()(const Robot& rob1, const Robot& rob2) {
            return rob1.position < rob2.position;
        }
    };
public:
    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        priority_queue<Robot, vector<Robot>, Comparator> robots;
        stack<Robot> robotsStack;
        for (int i = 0; i < positions.size(); i++) {
            robots.push({positions[i], healths[i], directions[i], i});
        }
        while (!robots.empty()) {
            Robot rob = robots.top();
            robots.pop();
            bool lost = false;
            // Robot neighbour = robotsStack.top();
            while (!robotsStack.empty() && rob.direction != robotsStack.top().direction && !lost) {
                    if (rob.direction == 'L' && robotsStack.top().direction == 'R') {
                        break;
                    } else if (rob.health < robotsStack.top().health) {
                        robotsStack.top().health -= 1;
                        lost = true;
                    } else if (rob.health > robotsStack.top().health) {
                        rob.health -= 1;
                        robotsStack.pop();
                    } else {
                        lost = true;
                        robotsStack.pop();
                    }
                }
            if (!lost) {
                robotsStack.push(rob);
            }
        }
        
        vector<int> result(robotsStack.size());
        vector<Robot> temp(robotsStack.size());
        int i = 0;
        while (!robotsStack.empty()) {
            temp[i++] = robotsStack.top();
            robotsStack.pop();
        }
        sort(temp.begin(), temp.end(), [](const Robot& a, const Robot& b) {
            return a.posArr < b.posArr;
        });
        i = 0;
        for (const Robot& rob : temp) {
            result[i] = rob.health;
        }
        return result;
    }
};

int main() {
    Solution solution;
    vector<int> pos = {3,5,2,6};
    vector<int> hp = {10,10,15,12};
    string dr = "RLRL";
    for (int res : solution.survivedRobotsHealths(pos, hp, dr)) {
        cout << res << " ";
    }
    return 0;
}


