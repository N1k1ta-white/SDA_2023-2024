/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        if (!head || !head->next || !head->next->next) return {-1, -1};

        vector<int> criticalPoints;
        ListNode* prev = head;
        ListNode* curr = head->next;
        ListNode* next = head->next->next;
        int index = 1;
        int minDist = INT_MAX;

        while (next) {
            if ((curr->val > prev->val && curr->val > next->val) || (curr->val < prev->val && curr->val < next->val)) {
                if (!criticalPoints.empty()) {
                    minDist = min(minDist, index - criticalPoints.back());
                }
                criticalPoints.push_back(index);
                // std::cout << "Critical point value: " << curr->val << std::endl;
            }
            prev = curr;
            curr = next;
            next = next->next;
            index++;
        }

        if (criticalPoints.size() < 2) return {-1, -1};

        int maxDist = criticalPoints.back() - criticalPoints.front();

        return {minDist, maxDist};
    }
};