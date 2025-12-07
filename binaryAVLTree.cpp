#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <climits>
#include <string>
using namespace std;

class Node {
public:
    int data;
    int height;
    Node* left;
    Node* right;
    
    Node(int value) {
        data = value;
        height = 1;
        left = NULL;
        right = NULL;
    }
};

class BinarySearchTree {
private:
    Node* root;

    Node* buildTreeHelper(vector<int>& in, vector<int>& pre, int inStart, int inEnd, int& preIndex) {
        if (inStart > inEnd) return NULL;
        Node* node = new Node(pre[preIndex++]);
        if (inStart == inEnd) return node;
        int inIndex;
        for (int i = inStart; i <= inEnd; i++) {
            if (in[i] == node->data) {
                inIndex = i;
                break;
            }
        }
        node->left = buildTreeHelper(in, pre, inStart, inIndex - 1, preIndex);
        node->right = buildTreeHelper(in, pre, inIndex + 1, inEnd, preIndex);
        return node;
    }

    Node* sortedArrayToBSTHelper(int arr[], int start, int end) {
        if (start > end) return NULL;
        int mid = start + (end - start) / 2;
        Node* node = new Node(arr[mid]);
        node->left = sortedArrayToBSTHelper(arr, start, mid - 1);
        node->right = sortedArrayToBSTHelper(arr, mid + 1, end);
        return node;
    }
    
    void rightRotateDSW(Node*& grandParent, Node* parent, Node* child) {
        if (grandParent != NULL) grandParent->right = child;
        else root = child;
        parent->left = child->right;
        child->right = parent;
    }

    void leftRotateDSW(Node*& grandParent, Node* parent, Node* child) {
        if (grandParent != NULL) grandParent->right = child;
        else root = child;
        parent->right = child->left;
        child->left = parent;
    }

    void convertToBackbone() {
        Node* grandParent = NULL;
        Node* temp = root;
        while (temp != NULL) {
            if (temp->left != NULL) {
                Node* child = temp->left;
                rightRotateDSW(grandParent, temp, child);
                temp = child;
            } else {
                grandParent = temp;
                temp = temp->right;
            }
        }
    }

    void compress(Node* grandParent, int count) {
        Node* temp = (grandParent == NULL) ? root : grandParent->right;
        for (int i = 0; i < count; i++) {
            Node* child = temp->right;
            if (child) {
                leftRotateDSW(grandParent, temp, child);
                grandParent = child;
                temp = child->right;
            }
        }
    }

    void inorderHelper(Node* node) {
        if (!node) return;
        inorderHelper(node->left);
        cout << node->data << " ";
        inorderHelper(node->right);
    }
    void preorderHelper(Node* node) {
        if (!node) return;
        cout << node->data << " ";
        preorderHelper(node->left);
        preorderHelper(node->right);
    }
    void postorderHelper(Node* node) {
        if (!node) return;
        postorderHelper(node->left);
        postorderHelper(node->right);
        cout << node->data << " ";
    }
    void deleteSubtree(Node* node) {
        if (!node) return;
        deleteSubtree(node->left);
        deleteSubtree(node->right);
        delete node;
    }
    int getHeightHelper(Node* node) {
        if (!node) return 0;
        return 1 + max(getHeightHelper(node->left), getHeightHelper(node->right));
    }
    int countAllNodesHelper(Node* node) {
        if (!node) return 0;
        return 1 + countAllNodesHelper(node->left) + countAllNodesHelper(node->right);
    }

    Node* insertHelper(int value, Node* node) {
        if (node == NULL) return new Node(value);
        if (value < node->data) node->left = insertHelper(value, node->left);
        else if (value > node->data) node->right = insertHelper(value, node->right);
        return node;
    }

public:
    BinarySearchTree() { root = NULL; }
    ~BinarySearchTree() { deleteSubtree(root); }

    void insert(int value) { root = insertHelper(value, root); }
    void destroy() { deleteSubtree(root); root = NULL; }
    int getHeight() { return getHeightHelper(root); }
    int countAllNodes() { return countAllNodesHelper(root); }

    void display_in_order() { inorderHelper(root); cout << endl; }
    void display_pre_order() { preorderHelper(root); cout << endl; }
    void display_post_order() { postorderHelper(root); cout << endl; }

    void construct_from_traversals(vector<int> in_order, vector<int> pre_order) {
        destroy();
        int preIndex = 0;
        root = buildTreeHelper(in_order, pre_order, 0, in_order.size() - 1, preIndex);
    }

    void createBalancedTree(int* arr, int start, int end) {
        if (root != NULL) destroy();
        root = sortedArrayToBSTHelper(arr, start, end);
    }

    void createPerfectBST() {
        convertToBackbone();
        int n = countAllNodes();
        int m = pow(2, floor(log2(n + 1))) - 1;
        compress(NULL, n - m);
        while (m > 1) {
            m = m / 2;
            compress(NULL, m);
        }
    }
};

int main() {
    cout << "=== Task 1: Construct from Traversals ===" << endl;
    BinarySearchTree bst1;
    vector<int> in1 = {1, 2, 3, 4, 5, 6};
    vector<int> pre1 = {3, 1, 2, 5, 4, 6};
    bst1.construct_from_traversals(in1, pre1);
    
    cout << "In-order (Example 1): "; bst1.display_in_order();
    cout << "Post-order (Example 1): "; bst1.display_post_order();

    cout << "\n=== Task 2: Create Balanced Tree from Array ===" << endl;
    BinarySearchTree bst2;
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    bst2.createBalancedTree(arr, 0, n - 1);
    
    cout << "Pre-order: "; bst2.display_pre_order();
    cout << "In-order: "; bst2.display_in_order();
    cout << "Post-order: "; bst2.display_post_order();

    cout << "\n=== Task 3: DSW Algorithm (Perfect BST) ===" << endl;
    BinarySearchTree bst3;
    int inputs[] = {1, 5, 10, 20, 25, 30, 35, 40, 45};
    for(int val : inputs) bst3.insert(val);

    cout << "Original Height: " << bst3.getHeight() << endl;
    cout << "Original In-order: "; bst3.display_in_order();

    bst3.createPerfectBST();

    cout << "Height After DSW: " << bst3.getHeight() << endl;
    cout << "Balanced (In-order): "; bst3.display_in_order();
    cout << "Balanced (Pre-order): "; bst3.display_pre_order();
    cout << "Balanced (Post-order): "; bst3.display_post_order();

    return 0;
}
