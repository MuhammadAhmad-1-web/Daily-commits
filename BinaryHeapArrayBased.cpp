#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;



class Student {
public:
    double cgpa;
    int rollNo;

    Student() {
        cgpa = 0.0;
        rollNo = 0;
    }

    Student(int r, double c) {
        rollNo = r;
        cgpa = c;
    }
};

class StudentMaxHeap {
private:
    Student* st;    // Array of students
    int currSize;   // Current number of students
    int maxSize;    // Maximum capacity

  
    bool isGreater(const Student& a, const Student& b) {
        if (a.cgpa > b.cgpa){
             return true;}
        if (a.cgpa == b.cgpa && a.rollNo < b.rollNo) {
            return true;}
        return false;
    }

    void heapifyUp(int index) {
        int parent = (index - 1) / 2;
        while (index > 0 && isGreater(st[index], st[parent])) {
            swap(st[index], st[parent]);
            index = parent;
            parent = (index - 1) / 2;
        }
    }

    void heapifyDown(int index) {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < currSize && isGreater(st[left], st[largest]))
            largest = left;

        if (right < currSize && isGreater(st[right], st[largest]))
            largest = right;

        if (largest != index) {
            swap(st[index], st[largest]);
            heapifyDown(largest);
        }
    }

public:
    // Constructor
    StudentMaxHeap(int size) {
        maxSize = size;
        currSize = 0;
        st = new Student[maxSize];
    }

    // Destructor
    ~StudentMaxHeap() {
        delete[] st;
    }

   
    bool isEmpty() { return currSize == 0; }
    bool isFull() { return currSize == maxSize; }

    // Task 1.1: 
    bool insert(int rollNo, double cgpa) {
        if (isFull()){

        return false;}

        Student newStudent(rollNo, cgpa);
        st[currSize] = newStudent;
        heapifyUp(currSize);
        currSize++;
        return true;
    }

    // Task 1.2: 
    bool removeBestStudent(int& rollNo, double& cgpa) {
        if (isEmpty()) return false;

       
        rollNo = st[0].rollNo;
        cgpa = st[0].cgpa;

        
        st[0] = st[currSize - 1];
        currSize--;

        
        if (currSize > 0) {
            heapifyDown(0);
        }
        return true;
    }

    // Task 1.3
    void levelOrder() {
        for (int i = 0; i < currSize; i++) {
            cout << "Roll#: " << st[i].rollNo << ", CGPA: " << st[i].cgpa << endl;
        }
    }

    int height() {
        if (isEmpty()){ 
            return -1;}
        return (int)log2(currSize);
    }
};

int main() {
    // --- Test Task 1 ---
    cout << "--- TASK 1: Student Heap ---" << endl;
    StudentMaxHeap heap(20);
    
    // Add multiple sample students
    heap.insert(10, 3.2);
    heap.insert(5, 3.9);
    heap.insert(12, 3.5);
    heap.insert(3, 3.9); // Same CGPA as roll 5 (tie-break: smaller roll first)
    heap.insert(7, 2.8);
    heap.insert(18, 3.7);
    heap.insert(1, 4.0); // Highest CGPA
    heap.insert(20, 3.4);
    heap.insert(11, 3.7); // Same CGPA as roll 18 (tie-break)
    heap.insert(4, 3.8);

    cout << "===== Level Order After Insertions =====\n";
    heap.levelOrder();
    cout << "\nHeight of the heap: " << heap.height() << endl;

    // Remove top student twice
    int roll;
    double cg;

    if (heap.removeBestStudent(roll, cg)) {
        cout << "Removed Student Roll No: " << roll << ", CGPA: " << cg << endl;
    }
    if (heap.removeBestStudent(roll, cg)) {
        cout << "Removed Student Roll No: " << roll << ", CGPA: " << cg << endl;
    }

    cout << "\n===== Level Order After Two Removals =====\n";
    heap.levelOrder();
    cout << "\nHeight of the heap: " << heap.height() << endl;

    cout << endl << "-----------------------------------" << endl;
    return 0;}








