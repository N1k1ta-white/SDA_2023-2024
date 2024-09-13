//
// Created by Nikita on 08.09.2024.
//
#include <iostream>
#include <vector>
#include <queue>
#include "structures/ListNode.h"

using namespace std;

class Solution {

    static int getLengthOfLinkedList(ListNode* head) {
        int length = 0;
        while (head) {
            length++;
            head = head->next;
        }
        return length;
    }

public:
    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        int length = getLengthOfLinkedList(head);
        int remain = length % k;
        int lengthOfPart = length / k;
        vector<ListNode*> parts(k, nullptr);
        vector<ListNode*> endParts(k, nullptr);
        for (int i = 0; i < k; ++i) {
            if (lengthOfPart) {
                parts[i] = head;
                endParts[i] = head;
                head = head->next;
            }
            for (int j = 1; j < lengthOfPart; ++j) {
                endParts[i]->next = head;
                head = head->next;
                endParts[i] = endParts[i]->next;
            }
            if (remain) {
                remain--;
                if (!lengthOfPart) {
                    parts[i] = head;
                    endParts[i] = head;
                } else {
                    endParts[i]->next = head;
                    endParts[i] = endParts[i]->next;
                }
                head = head->next;
            }
            if (endParts[i]) {
                endParts[i]->next = nullptr;
            }
        }
        return parts;
    }
};

int main() {

}