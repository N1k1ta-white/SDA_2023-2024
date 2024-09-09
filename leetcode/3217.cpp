//
// Created by Nikita on 08.09.2024.
//
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {

    vector<int> *nums;

    void removeNode(ListNode* prev, ListNode* next) {
        prev->next = next;
    }

    bool isPresent(int num) {
        auto res = lower_bound(nums->begin(), nums->end(), num);
        return res != nums->end() && *res == num;
    }

public:

    ListNode* modifiedList(vector<int>& nums, ListNode* head) {
        sort(nums.begin(), nums.end());
        this->nums = &nums;

        while (head && isPresent(head->val)) {
            head = head->next;
        }

        if (head) {
            ListNode *prev = head;
            ListNode *curr = head->next;

            while (curr) {
                if (isPresent(curr->val)) {
                    removeNode(prev, curr->next);
                    ListNode* temp = curr->next;
                    delete curr;
                    curr = temp;
                    continue;
                }
                if (curr) {
                    prev = curr;
                    curr = curr->next;
                }
            }
        }
        return head;
    }
};

int main() {
    vector<int> nums = {1,7,6,2,4};
    ListNode* head = new ListNode(3, new ListNode(7, new ListNode(1, new ListNode(8, new ListNode(1)))));
    Solution solution;

    head = solution.modifiedList(nums, head);


    while (head) {
        ListNode* temp = head->next;
        delete head;
        head = temp;
    }
}