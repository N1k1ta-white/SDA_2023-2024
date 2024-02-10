#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Node {
    int val;
    Node* next;
    Node* prev;
    Node(int val, Node* prev) : val(val), next(nullptr), prev(prev) {}
    Node(int val, Node* prev, Node* next) : val(val), next(next), prev(prev) {}
};

class Mitya {
    int count;
    int centerPos;
    Node* head;
    Node* center;
    Node* end;

    void checkCenter() {
        if (count == 0) {
            center = nullptr;
            return;
        }
        int mid = count / 2;
        if (mid - centerPos == 1 && count % 2) {
            if (center->prev)
                center = center->prev;
            centerPos = mid;
        }
        if (centerPos - mid == 1) {
            if (center->next)
                center = center->next;
            centerPos = mid;
        }
    }

public:
    Mitya() : count(0), head(nullptr), end(nullptr), centerPos(0) {}
    ~Mitya() {
        Node* temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
    void add(int val) {
        Node* crib = new Node(val, nullptr, head);
        if (count == 0) {
            end = crib;
            center = crib;
        }
        if (head)
            head->prev = crib;
        head = crib;
        count++;
        checkCenter();
    }

    void gun() {
        Node* newHead = head->next;
        delete head;
        if (!newHead) {
            count = 0;
            head = end = center = nullptr;
            return;
        }
        head = newHead;
        head->prev = nullptr;
        count--;
        checkCenter();
    }

    void milen() {
        if (count == 1)
            return;
        if (count % 2)
            center = center->next;
        Node* midl = center;
        end->next = head;
        head->prev = end;
        end = midl->prev;
        midl->prev = nullptr;
        end->next = nullptr;
        center = head;
        head = midl;
    }

    void print() {
        cout << count << endl;
        if (count == 0)
            return;
        Node* iter = end;
        while (iter) {
            cout << iter->val << " ";
            iter = iter->prev;
        }
    }
};

int main() {
    int n, x;
    Mitya mitya;
    cin >> n;
    string request;
    for (int i = 0; i < n; ++i) {
        cin >> request;
        if (request == "add") {
            cin >> x;
            mitya.add(x);
        }
        else if (request == "gun")
            mitya.gun();
        else
            mitya.milen();
    }
    mitya.print();
}