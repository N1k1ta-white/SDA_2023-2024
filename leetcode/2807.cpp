//
// Created by Nikita on 10.09.2024.
//
#include <iostream>
#include "structures/ListNode.h"

using namespace std;

class Solution {
    static int findGreatestCommonDivisorBetween(int a, int b) {
        if (a < b) {
            swap(a, b);
        }
        while (b) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    static void insertNodeBetween(ListNode* first, ListNode* second, ListNode* mid) {
        first->next = mid;
        mid->next = second;
    }

public:

    ListNode* insertGreatestCommonDivisors(ListNode* head) {
        ListNode* curr = head;
        ListNode* next = head->next;
        while (next) {
            int gcd = findGreatestCommonDivisorBetween(curr->val, next->val);
            ListNode* node = new ListNode(gcd);
            insertNodeBetween(curr, next, node);
            curr = next;
            next = next->next;
        }
        return head;
    }
};

int main() {
    Solution solution;
}