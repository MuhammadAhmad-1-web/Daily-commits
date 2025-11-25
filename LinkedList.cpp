#include<iostream>
using namespace std ;

class Node{
    friend class LinkedList;
private:
    int data;
    Node* next;
public:
   Node(int val ){
    data = val ;
    next = nullptr;
   }
};

class LinkedList{
private:
    Node* head;
public:
    LinkedList(){
        head = nullptr;
    }

    void insertAtBeginning(int val ){
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }

    void display(){
        Node* temp = head;
        while(temp != 0){
            cout << temp->data << " ";
            temp = temp->next;
        }
    }

    void insertAtEnd(int val){
        Node* newNode = new Node(val);
        if(head == 0){
            head = newNode;
        }
        else{
            Node* temp = head;
            while(temp->next != 0){
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void deleteAtbeginning(){
        if(head == 0){
            return ;
        }
        else{
            Node* temp = head;
            head = head->next;
            delete temp ;
        }
    }

    void deleteFromEnd(){
        if(head == 0){
            return;
        }
        else if(head->next == 0){
            delete head;
            head = nullptr;
        }
        else{
            Node* temp = head;
            Node* pre = head;
            while(temp->next != 0){
                pre = temp;
                temp = temp->next;
            }
            pre->next = nullptr;
            delete temp;
        }
    }

    bool search(int val ){
        if(head == 0){
            return false;
        }
        Node * temp = head ;
        while(temp != 0){
            if(temp->data == val){
                return true;
            }
            temp = temp -> next;
        }
        return false;
    }

    int getLength(){
        int count = 0 ;
        Node* temp = head;
        while(temp != 0){
            count++;
            temp = temp->next;
        }
        return count;
    }

    void combine(LinkedList& list1, LinkedList& list2){
        if (head == nullptr) {
            if (list1.head == nullptr) {
                head = list2.head;
            } else {
                head = list1.head;
                Node* tail = head;
                while (tail->next != nullptr){ 
                    tail = tail->next;
                }
                tail->next = list2.head;
            }
        }
        list1.head = nullptr;
        list2.head = nullptr;
    }

    void reverseNodes() {
        if(head == nullptr || head->next == nullptr) {
            return;
        }
        
        Node* prev = nullptr;
        Node* current = head;
        Node* nextNode = nullptr;
        
        while(current != nullptr) {
            nextNode = current->next;
            current->next = prev;
            prev = current;
            current = nextNode;
        }
        
        head = prev;
    }

    ~LinkedList(){
        while(head != nullptr){
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main(){
    LinkedList list;
    LinkedList list2;

    list.insertAtBeginning(10);
    list.insertAtBeginning(20);
    list.insertAtBeginning(30);

    list2.insertAtBeginning(10);
    list2.insertAtBeginning(20);
    list2.insertAtBeginning(30);

    LinkedList list3;
    list3.combine(list, list2);
    list3.display();

    return 0;
}
