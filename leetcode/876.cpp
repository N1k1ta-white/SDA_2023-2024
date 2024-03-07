#include <iostream>

using namespace std;

struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
};

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