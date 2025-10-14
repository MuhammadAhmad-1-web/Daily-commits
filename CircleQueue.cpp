#include<iostream>
using namespace std;

template <typename T>
class Queue{
private:
    T* data;
    int noofelements;
    int capacity;
    int rearindex;
    int frontindex;
    
public:
    Queue(int size = 10) {
        capacity = size;
        data = new T[capacity];
        noofelements = 0;
        frontindex = 0;
        rearindex = 0;
    }
    
    ~Queue(){
        delete[] data;
    }
    
    bool isEmpty(){
        return noofelements == 0;
    }
    
    bool isFull(){
        return noofelements == capacity;
    }
    
    void enqueue(T value){
        if(isFull()){
            cout << "Can't enter more into the queue" << endl;
            return;
        }
        data[rearindex] = value;
        rearindex = (rearindex + 1) % capacity;   // circular increment
        noofelements++;
    }
    
    T dequeue(){
        if(isEmpty()){
            cout << "Queue is empty" << endl;
            return T();
        }
        T e = data[frontindex];
        frontindex = (frontindex + 1) % capacity; // circular increment
        noofelements--;
        return e;
    }
    
    Queue(const Queue<T>& other){
        capacity = other.capacity;
        noofelements = other.noofelements;
        frontindex = 0;
        rearindex = noofelements;
        data = new T[capacity];
        
        int src = other.frontindex;
        for(int i = 0; i < noofelements; i++){
            data[i] = other.data[src];
            src = (src + 1) % other.capacity;     // circular traversal
        }
    }
    
    void display(){
        int index = frontindex;
        for(int i = 0; i < noofelements; i++){
            cout << data[index] << endl;
            index = (index + 1) % capacity;       // circular traversal
        }
    }
    
    Queue<T>& operator=(const Queue<T>& other){
        if(this == &other){
            return *this;
        }
        
        delete[] data;
        capacity = other.capacity;
        noofelements = other.noofelements;
        frontindex = 0;
        rearindex = noofelements;
        data = new T[capacity];
        
        int src = other.frontindex;
        for(int i = 0; i < noofelements; i++){
            data[i] = other.data[src];
            src = (src + 1) % other.capacity;     // circular traversal
        }
        return *this;
    }
    
    void resize(){
        int newcapacity = capacity * 2;
        T* newdata = new T[newcapacity];
        
        int src = frontindex;
        for(int i = 0; i < noofelements; i++){
            newdata[i] = data[src];
            src = (src + 1) % capacity;           // circular traversal
        }
        
        delete[] data;
        data = newdata;
        capacity = newcapacity;
        frontindex = 0;
        rearindex = noofelements;
    }
};

/*int main(){
    Queue<int> q1;
    q1.enqueue(10);
    q1.enqueue(20);
    q1.enqueue(30);
    cout << "Integer Queue:" << endl;
    q1.display();
    cout << "Dequeued: " << q1.dequeue() << endl;
    
    Queue<double> q2;
    q2.enqueue(3.14);
    q2.enqueue(2.71);
    q2.enqueue(1.41);
    cout << "Double Queue:" << endl;
    q2.display();
    
    Queue<string> q3;
    q3.enqueue("Hello");
    q3.enqueue("World");
    q3.enqueue("Queue");
    cout << "String Queue:" << endl;
    q3.display();
    
    Queue<char> q4;
    q4.enqueue('A');
    q4.enqueue('B');
    q4.enqueue('C');
    cout << "Character Queue:" << endl;
    q4.display();
    
    return 0;
}*/
 
int main() 
{ 
 Queue<int> q(5); 
 
 q.enqueue(14); 
 q.enqueue(22); 
 q.enqueue(13); 
 q.enqueue(-6); 
 q.display(); 
 cout<<"Deleted Value = "<<q.dequeue()<<endl; 
 cout<<"Deleted Value = "<<q.dequeue()<<endl; 
 q.display(); 
  
 q.enqueue(9); 
 q.enqueue(20); 
 q.enqueue(5); 
 q.display(); 
 return 0; 
} 
