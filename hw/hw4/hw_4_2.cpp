#include <unordered_map>
#include <iostream>
using namespace std;

struct Node {
    int key;
    int value;
    Node* next;
    Node* prev;
    Node() : key(-1), value(-1), next(nullptr), prev(nullptr) {}
    Node(int key, int val) : key(key), value(val), next(nullptr), prev(nullptr) {}
    Node(int key, int val, Node* prev) : key(key), value(val), next(nullptr), prev(prev) {}
    Node(int key, int val, Node* prev, Node* next) : key(key), value(val), next(next), prev(prev) {}
};

class LRUCache {
    int capacity;
    int heat;
    std::unordered_map<int, Node*> map;
    Node* head;
    Node* end;
    int counter;
    int heatCounter;

    void eraseLast() {
        Node* preEnd = end->prev;
        map.erase(end->key);
        delete end;
        end = preEnd;
        end->next = nullptr;
        counter--;
    }

    void transport(Node* node) {
        if (node == head)
            return;
        if (node == end) {
            end = node->prev;
        }
        if (node->prev)
            node->prev->next = node->next;
        if (node->next)
            node->next->prev = node->prev;
        node->next = head;
        head->prev = node;
        head = node;
        head->prev = nullptr;
    }

    void heatCheck() {
        if (heatCounter + 1 == heat) {
            eraseLast();
            heatCounter = 0;
        }
        else
            heatCounter++;
    }

public:
    LRUCache(int capacity, int heat) : capacity(capacity), heat(heat), head(nullptr), heatCounter(0),
                                        end(nullptr), counter(0) {}
     ~LRUCache() {
         Node* temp;
         while(head) {
             temp = head;
             head = head->next;
             delete temp;
         }
     }

    int get(int key) {
        int res;
        if (map.find(key) != map.end()) {
            Node* curr = map[key];
            transport(curr);
            res = curr->value;
        }
        else
            res = -1;
        heatCheck();
        return res;
    }

    void put(int key, int value) {
        if (map.find(key) == map.end()) {
            Node* newNode = new Node(key, value, nullptr, head);
            map[key] = newNode;
            if (head)
                head->prev = newNode;
            head = newNode;
            if (!end) {
                end = newNode;
            }
            counter++;
            if (counter > capacity)
                eraseLast();
        }
        else {
            Node* curr = map[key];
            curr->value = value;
            transport(curr);
        }
        heatCheck();
    }
};

int main() {
    int n, q, k, key, value;
    cin >> n >> q >> k;
    LRUCache cache(n, k);
    string request;
    for (int i = 0; i < q; ++i) {
        cin >> request;
        if (request == "get") {
            cin >> key;
            cout << cache.get(key) << endl;
        } else {
            cin >> key >> value;
            cache.put(key, value);
        }
    }
}