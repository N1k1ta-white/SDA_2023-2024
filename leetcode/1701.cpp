#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    double averageWaitingTime(vector<vector<int>>& customers) {
        double totalWaitingTime = 0;
        int currentTime = 0;

        for (const auto& customer : customers) {
            int arrivalTime = customer[0];
            int cookingTime = customer[1];

            if (currentTime < arrivalTime) {
                currentTime = arrivalTime;
            }

            currentTime += cookingTime;
            totalWaitingTime += (currentTime - arrivalTime);
        }

        return totalWaitingTime / customers.size();
    }
};

int main() {
    Solution solution;
    vector<vector<int>> customers = {{1, 2}, {2, 5}, {4, 3}};
    double result = solution.averageWaitingTime(customers);
    std::cout << "Average Waiting Time: " << result << std::endl;
    return 0;
}
