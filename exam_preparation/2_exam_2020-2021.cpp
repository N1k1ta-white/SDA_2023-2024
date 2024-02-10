#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    int data;
    Node *next;
};

struct List {
    Node* head = nullptr;
    Node* tail = nullptr;

    void add(int value) {
        Node* temp = new Node;
        temp->data = value;
        temp->next = nullptr;

        if (head == nullptr and tail == nullptr){
            head = tail = temp;
        } else {
            tail->next = temp;
            tail = temp;
        }
    }


    void reverse(int from, int to) {
        Node* curr = head;
        Node* prev = nullptr;
        for (int i = 0; i < from - 1 && curr; ++i) {
            prev = curr;
            curr = curr->next;
        }
        if (!curr) {
            return;
        }
        List *list = new List;
        vector<int> vec;
        for (int i = 0; i < to - from && curr->next; ++i) {
            vec.push_back(curr->data);
            curr = curr->next;
        }
        vec.push_back(curr->data);
        std::reverse(vec.begin(), vec.end());

        for (int num : vec) {
            list->add(num);
        }

        if (prev) {
            prev->next = list->head;
        } else {
            head = list->head;
        }
        if (curr->next) {
            list->tail->next = curr->next;
        } else {
            tail = list->tail;
        }
    }

    void print() {
        Node* temp = head;

        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }

        cout << endl;
    }

    ~List() {
        Node* curr = head;

        while(curr) {
            Node* prev = new Node;
            prev = curr;
            curr = curr->next;
            delete prev;
        }

        delete curr;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    List testList;

    int queries;
    cin >> queries;

    for (int t = 0; t < queries; t++) {

        string op;
        cin >> op;

        if (op == "add") {
            int num;
            cin >> num;
            testList.add(num);
        }

        if (op == "print") {
            testList.print();
        }

        if (op == "reverse") {
            int from, to;
            cin >> from >> to;
            testList.reverse(from, to);
        }
    }

    return 0;
}