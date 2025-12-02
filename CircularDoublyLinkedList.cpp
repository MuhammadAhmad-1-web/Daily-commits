#include<iostream>
using namespace std;

class DNode {
public:
    int data;
    DNode* next;
    DNode* prev;
    
    DNode(int val) {
        data = val;
        next = nullptr;
        prev = nullptr;
    }
};

class CDLinkedList {
private:
    DNode* head;

public:
    // Default constructor
    CDLinkedList() {
        head = nullptr;
    }
    
    // Destructor
    ~CDLinkedList() {
        if (head == nullptr) return;
        
        DNode* current = head;
        DNode* nextNode;
        
        // Break the circular link
        head->prev->next = nullptr;
        
        while (current != nullptr) {
            nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
    }
    
    // Insertion functions
    void insertAtHead(int val) {
        DNode* newNode = new DNode(val);
        
        if (head == nullptr) {
            // Empty list - node points to itself
            head = newNode;
            newNode->next = newNode;
            newNode->prev = newNode;
        } else {
            DNode* tail = head->prev;
            
            newNode->next = head;
            newNode->prev = tail;
            tail->next = newNode;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void insertAtTail(int val) {
        DNode* newNode = new DNode(val);
        
        if (head == nullptr) {
            // Empty list - node points to itself
            head = newNode;
            newNode->next = newNode;
            newNode->prev = newNode;
        } else {
            DNode* tail = head->prev;
            
            newNode->next = head;
            newNode->prev = tail;
            tail->next = newNode;
            head->prev = newNode;
        }
    }
    
    // Deletion functions
    void removeAtHead() {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }
        
        if (head->next == head) {
            // Only one node
            delete head;
            head = nullptr;
        } else {
            DNode* tail = head->prev;
            DNode* temp = head;
            
            head = head->next;
            head->prev = tail;
            tail->next = head;
            
            delete temp;
        }
    }
    
    void removeAtTail() {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }
        
        if (head->next == head) {
            // Only one node
            delete head;
            head = nullptr;
        } else {
            DNode* tail = head->prev;
            DNode* newTail = tail->prev;
            
            newTail->next = head;
            head->prev = newTail;
            
            delete tail;
        }
    }
    
    void remove(int val) {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }
        
        DNode* current = head;
        
        do {
            if (current->data == val) {
                if (current == head && current->next == head) {
                    // Only one node
                    delete current;
                    head = nullptr;
                    return;
                } else if (current == head) {
                    // Removing head
                    removeAtHead();
                    return;
                } else {
                    // Remove middle or tail node
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                    delete current;
                    return;
                }
            }
            current = current->next;
        } while (current != head);
        
        cout << "Value " << val << " not found!" << endl;
    }
    
    // Utility functions
    bool search(int key) {
        if (head == nullptr) {
            return false;
        }
        
        DNode* current = head;
        do {
            if (current->data == key) {
                return true;
            }
            current = current->next;
        } while (current != head);
        
        return false;
    }
    
    void update(int key, int val) {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }
        
        DNode* current = head;
        do {
            if (current->data == key) {
                current->data = val;
                cout << "Updated " << key << " to " << val << endl;
                return;
            }
            current = current->next;
        } while (current != head);
        
        cout << "Key " << key << " not found!" << endl;
    }
    
    int countNodes() {
        if (head == nullptr) {
            return 0;
        }
        
        int count = 0;
        DNode* current = head;
        do {
            count++;
            current = current->next;
        } while (current != head);
        
        return count;
    }
    
    // Display function for testing
    void display() {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }
        
        DNode* current = head;
        do {
            cout << current->data << " ";
            current = current->next;
        } while (current != head);
        cout << endl;
    }
    void merge(CDLinkedList& list1, CDLinkedList& list2) {
    if (list1.head == nullptr && list2.head == nullptr) {
        return;
    }
    
    if (list1.head == nullptr) {
        head = list2.head;
        list2.head = nullptr;
        return;
    }
    
    if (list2.head == nullptr) {
        head = list1.head;
        list1.head = nullptr;
        return;
    }
    
    DNode* ptr1 = list1.head;
    DNode* ptr2 = list2.head;
    DNode* tail = nullptr;
    
    // Choose the first node
    if (ptr1->data <= ptr2->data) {
        head = ptr1;
        tail = ptr1;
        ptr1 = ptr1->next;
        if (ptr1 == list1.head) ptr1 = nullptr;
    } else {
        head = ptr2;
        tail = ptr2;
        ptr2 = ptr2->next;
        if (ptr2 == list2.head) ptr2 = nullptr;
    }
    
    // Merge remaining nodes
    
    while (ptr1 != head) {
        tail->next = ptr1;
        ptr1->prev = tail;
        tail = ptr1;
        ptr1 = ptr1->next;
        if (ptr1 == list1.head) ptr1 = nullptr;
    }
    
    // Attach remaining nodes from list2
    while (ptr2 != head) {
        tail->next = ptr2;
        ptr2->prev = tail;
        tail = ptr2;
        ptr2 = ptr2->next;
        if (ptr2 == list2.head) ptr2 = nullptr;
    }
    while (ptr1 != head && ptr2 != head) {
        if (ptr1->data <= ptr2->data) {
            tail->next = ptr1;
            ptr1->prev = tail;
            tail = ptr1;
            ptr1 = ptr1->next;
            if (ptr1 == list1.head) ptr1 = nullptr;
        } else {
            tail->next = ptr2;
            ptr2->prev = tail;
            tail = ptr2;
            ptr2 = ptr2->next;
            if (ptr2 == list2.head) ptr2 = nullptr;
        }
    }
    
    // Attach remainin
    // Make it circular
    tail->next = head;
    head->prev = tail;
    
    // Empty the original lists
    list1.head = nullptr;
    list2.head = nullptr;
}
    
    
    



     
};


int main() {
    CDLinkedList list1;
    CDLinkedList list2;
    // Testing insertion
   list1.insertAtHead(12);
   list1.insertAtHead(10);
   list1.insertAtHead(7);
   list1.insertAtHead(3);
    list2.insertAtHead(1);
   list2.insertAtHead(3);
   list2.insertAtHead(6);
   list2.insertAtHead(8);

   
    CDLinkedList list3;
    list3.merge(list1, list2);
    list3.display();
    return 0;
}
