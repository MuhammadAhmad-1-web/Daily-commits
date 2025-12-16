#include <iostream>
#include <vector>
#include <algorithm> // For std::swap

class Heap {
private:
    std::vector<int> heap;
    bool isMinHeap; // true for MinHeap, false for MaxHeap

    // Helper to get indices
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return (2 * i) + 1; }
    int rightChild(int i) { return (2 * i) + 2; }

    // The core Heapify function (sifts a node down)
    void heapifyDown(int index) {
        int left = leftChild(index);
        int right = rightChild(index);
        int extremum = index; // This will hold either smallest (MinHeap) or largest (MaxHeap)

        // Compare with left child
        if (left < heap.size()) {
            if (isMinHeap) {
                if (heap[left] < heap[extremum]) extremum = left;
            } else {
                if (heap[left] > heap[extremum]) extremum = left;
            }
        }

        // Compare with right child
        if (right < heap.size()) {
            if (isMinHeap) {
                if (heap[right] < heap[extremum]) extremum = right;
            } else {
                if (heap[right] > heap[extremum]) extremum = right;
            }
        }

        // If the extremum is not the current node, swap and continue heapifying down
        if (extremum != index) {
            std::swap(heap[index], heap[extremum]);
            heapifyDown(extremum);
        }
    }

    // Helper to sift a node up (used during insertion)
    void heapifyUp(int index) {
        if (index == 0) return; // Root has no parent

        int p = parent(index);

        bool swapNeeded = false;
        if (isMinHeap) {
            if (heap[index] < heap[p]) swapNeeded = true;
        } else {
            if (heap[index] > heap[p]) swapNeeded = true;
        }

        if (swapNeeded) {
            std::swap(heap[index], heap[p]);
            heapifyUp(p);
        }
    }

public:
    // Constructor: Default is MinHeap, pass false for MaxHeap
    Heap(bool minHeap = true) : isMinHeap(minHeap) {}

    // Constructor: Build heap from an existing array
    Heap(const std::vector<int>& input, bool minHeap = true) : heap(input), isMinHeap(minHeap) {
        // Build the heap: Call heapifyDown starting from the last non-leaf node
        for (int i = (heap.size() / 2) - 1; i >= 0; i--) {
            heapifyDown(i);
        }
    }

    // Insert a new element
    void insert(int key) {
        heap.push_back(key);
        heapifyUp(heap.size() - 1);
    }

    // Extract the root element (Min for MinHeap, Max for MaxHeap)
    int extractTop() {
        if (heap.empty()) {
            throw std::runtime_error("Heap is empty");
        }

        int root = heap[0];
        // Move the last element to root and remove last element
        heap[0] = heap.back();
        heap.pop_back();

        // Fix the heap property
        if (!heap.empty()) {
            heapifyDown(0);
        }

        return root;
    }

    // Peek at the root element without removing it
    int peek() const {
        if (heap.empty()) {
            throw std::runtime_error("Heap is empty");
        }
        return heap[0];
    }

    // Utility to print the heap
    void printHeap() const {
        for (int i : heap) {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
};

int main() {
    // 1. Example using MinHeap (Default)
    std::cout << "--- Min Heap Example ---\n";
    std::vector<int> data = {10, 20, 15, 30, 40, 5, 25}; // Unordered data
    
    // Create heap from vector
    Heap minH(data, true); 
    
    std::cout << "Heapified Array: ";
    minH.printHeap(); // Expected root: 5

    std::cout << "Extracted Top: " << minH.extractTop() << "\n"; // Should be 5
    std::cout << "New Top: " << minH.peek() << "\n"; // Should be 10

    // 2. Example using MaxHeap
    std::cout << "\n--- Max Heap Example ---\n";
    Heap maxH(data, false); // false = MaxHeap

    std::cout << "Heapified Array: ";
    maxH.printHeap(); // Expected root: 40

    maxH.insert(50);
    std::cout << "After inserting 50: ";
    maxH.printHeap(); // Expected root: 50

    return 0;
}
