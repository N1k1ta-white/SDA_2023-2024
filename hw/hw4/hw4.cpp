#include <iostream>
using namespace std;

struct Node {
    Node* next;
    int value;
    explicit Node(int val) : value(val), next(nullptr) {}
    Node(int val, Node* next) : value(val), next(next) {}
};

void delList(Node* list1) {
    Node* temp;
    while (list1->next) {
        temp = list1->next;
        delete list1;
        list1 = temp;
    }
    delete list1;
}

class LinkedList {
    Node* start;
    Node* end;
    int length;

    void delList() {
        Node* temp;
        while (start->next) {
            temp = start->next;
            delete start;
            start = temp;
        }
        delete start;
    }

    void swapVal(Node* nd1, Node* nd2) {
        int temp = nd1->value;
        nd1->value = nd2->value;
        nd2->value = temp;
    }

public:
    LinkedList() {
        start = end = nullptr;
        length = 0;
    }

    ~LinkedList() {
        delList();
    }

    void pushBack(Node* node) {
        if (length == 0) {
            pushFront(node);
            end = start;
            return;
        }
        end->next = node;
        end = node;
        length++;
    }

    void popBack() {
        if (length == 0)
            throw logic_error("List is Empty!");
        Node* temp = start;
        while (temp->next != end)
            temp = temp->next;
        delete end;
        end = temp;
        length--;
    }

    void pushFront(Node* node) {
        node->next = start;
        start = node;
        if (length == 0)
            end = start;
        length++;
    }

    void popFront() {
        if (length == 0)
            throw logic_error("List is Empty!");
        Node* temp = start->next;
        delete start;
        start = temp;
        length--;
    }

    void insert(Node *node, int pos) {
        if (pos == 0) {
            pushFront(node);
            return;
        }
        if (pos == length - 1) {
            pushBack(node);
            return;
        }
        Node* temp = start;
        int iter = 0;
        while (iter + 1 != pos && temp->next) {
            temp = temp->next;
            iter++;
        }
        if (iter + 1 != pos)
            throw logic_error("Out of bounds!");
        Node* next = temp->next;
        temp->next = node;
        temp->next->next = next;
    }

    void sort() {
        Node* temp;
        for (int i = 0; i < length-1; i++) {
            temp = start;
            for (int j = 0; j < length - i - 1; j++) {
                if (temp->value > temp->next->value)
                    swapVal(temp, temp->next);
                temp = temp->next;
            }
        }
    }

    void print() const {
        Node* reader = start;
        while (reader->next) {
            cout << reader->value << " ";
            reader = reader->next;
        }
        cout << reader->value;
    }
};

int main() {
    int t, n, m, temp;
    cin >> t;
    cin >> n;
    LinkedList *list1 = new LinkedList;
    for (int i = 0; i < n; ++i) {
        cin >> temp;
        list1->pushBack(new Node(temp));
    }
//    cin >> m;
//    for (int i = 0; i < m; ++i) {
//        cin >> temp;
//        list1->pushBack(new Node(temp));
//    }
    list1->sort();
    list1->print();
    delete list1;
}