#include <iostream>

struct Node {
    int value;
    Node* next;
    Node(int v) : value(v), next(nullptr) {}
};

class LinkedList {
    Node* head;
    Node* tail;
    size_t sz;
public:
    LinkedList() : head(nullptr), tail(nullptr), sz(0) {}
    ~LinkedList() { clear(); }

    // disable copying for simplicity
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    void push_back(int v) {
        Node* n = new Node(v);
        if (!head) head = tail = n;
        else {
            tail->next = n;
            tail = n;
        }
        ++sz;
    }

    bool empty() const { return head == nullptr; }
    size_t size() const { return sz; }

    void clear() {
        Node* cur = head;
        while (cur) {
            Node* tmp = cur;
            cur = cur->next;
            delete tmp;
        }
        head = tail = nullptr;
        sz = 0;
    }

    void print() const {
        for (Node* cur = head; cur; cur = cur->next) {
            std::cout << cur->value << (cur->next ? " -> " : "");
        }
        std::cout << '\n';
    }

    friend void combine(LinkedList& list1, LinkedList& list2);
};

void combine(LinkedList& list1, LinkedList& list2) {
    if (&list1 == &list2) return; // no-op if same list
    if (list2.empty()) return;
    if (list1.empty()) {
        list1.head = list2.head;
        list1.tail = list2.tail;
        list1.sz = list2.sz;
    } else {
        list1.tail->next = list2.head;
        list1.tail = list2.tail;
        list1.sz += list2.sz;
    }
    // empty list2 without deleting nodes (ownership moved)
    list2.head = list2.tail = nullptr;
    list2.sz = 0;
}

// Example usage
int main() {
    LinkedList a, b;
    a.push_back(1);
    a.push_back(2);
    b.push_back(3);
    b.push_back(4);
    b.push_back(5);

    std::cout << "A before: "; a.print();
    std::cout << "B before: "; b.print();

    combine(a, b);

    std::cout << "A after:  "; a.print();
    std::cout << "B after:  "; b.print(); // should be empty

    return 0;
}
