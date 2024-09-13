#include <iostream>
#include "structures/ListNode.h"

using namespace std;

class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode* middle = head;
        while (head->next && head->next->next) {
            middle = middle->next;
            head = head->next->next;
        }
        if (head->next) {
            middle = middle->next;
        }
        return middle;
    }
};

int main() {

}