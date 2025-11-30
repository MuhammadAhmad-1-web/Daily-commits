#include <iostream>
#include <string>
using namespace std;


struct StudentNode {
    int rollNo;
    string name;
    double cgpa;
    StudentNode* left;
    StudentNode* right;

    StudentNode(int r, string n, double c) {
        rollNo = r;
        name = n;
        cgpa = c;
        left = NULL;
        right = NULL;
    }
};

class StudentBST {
private:
    StudentNode* root;

    // Helper: Insert 
    bool insertHelper(StudentNode*& node, int r, string n, double c) {
        if (node == NULL) {
            node = new StudentNode(r, n, c);
            return true;
        }
        if (r == node->rollNo) return false; //already
        
        if (r < node->rollNo)
            return insertHelper(node->left, r, n, c);
        else
            return insertHelper(node->right, r, n, c);
    }

    // Helper: InOrder Traversal 
    void inOrderHelper(StudentNode* node) {
        if (node == NULL) return;
        inOrderHelper(node->left);
        cout << "Roll: " << node->rollNo << ", Name: " << node->name << ", CGPA: " << node->cgpa << endl;
        inOrderHelper(node->right);
    }

    // Helper: Find Minimum Node (for remove)
    StudentNode* findMin(StudentNode* node) {
        while (node->left != NULL) node = node->left;
        return node;
    }

    // Helper: Remove 
    StudentNode* removeHelper(StudentNode* node, int r, bool &success) {
        if (node == NULL) {
            success = false;
            return NULL;
        }
        if (r < node->rollNo) {
            node->left = removeHelper(node->left, r, success);
        } else if (r > node->rollNo) {
            node->right = removeHelper(node->right, r, success);
        } else {
            // Node found
            success = true;
            // Case 1: No child
            if (node->left == NULL && node->right == NULL) {
                delete node;
                return NULL;
            }
            // Case 2: One child
            else if (node->left == NULL) {
                StudentNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == NULL) {
                StudentNode* temp = node->left;
                delete node;
                return temp;
            }
            // Case 3: Two children
            else {
                StudentNode* temp = findMin(node->right);
                node->rollNo = temp->rollNo;
                node->name = temp->name;
                node->cgpa = temp->cgpa;
                node->right = removeHelper(node->right, temp->rollNo, success);
            }
        }
        return node;
    }

    // Helper: Display In Range 
    void displayInRangeHelper(StudentNode* node, double start, double end) {
        if (node == NULL) return;
        
        displayInRangeHelper(node->left, start, end);
        
        if (node->cgpa >= start && node->cgpa <= end) {
            cout << "Roll: " << node->rollNo << " (" << node->cgpa << ")" << endl;
        }
        
        displayInRangeHelper(node->right, start, end);
    }

    // Helper: Destroy 
    void destroy(StudentNode* node) {
        if (node) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }

public:
    StudentBST() { root = NULL; }
    
    // Destructor 
    ~StudentBST() { destroy(root); }

    // Task 1.1: Insert 
    bool insert(int r, string n, double c) {
        return insertHelper(root, r, n, c);
    }

    // Task 1.1: Search 
    bool search(int r) {
        StudentNode* curr = root;
        while (curr != NULL) {
            if (r == curr->rollNo) {
                cout << "Found: " << curr->name << ", CGPA: " << curr->cgpa << endl;
                return true;
            }
            else if (r < curr->rollNo) curr = curr->left;
            else curr = curr->right;
        }
        cout << "Student not found." << endl;
        return false;
    }

    // Task 1.1: 
    void InOrder() {
        inOrderHelper(root);
    }

    // Task 1.2: Remove 
    bool remove(int rn) {
        bool success = false;
        root = removeHelper(root, rn, success);
        if(!success) cout << "Student not found for removal." << endl;
        return success;
    }

    // Task 1.3: Display Range 
    void displayInRange(double start, double end) {
        cout << "Students with CGPA between " << start << " and " << end << ":" << endl;
        displayInRangeHelper(root, start, end);
    }
};

int main() {
    StudentBST stree;
    
    
    int choice;
    do {
        cout << "\n1. Insert\n2. Search\n3. List All\n4. Remove\n5. Range Search\n6. Quit\nChoice: ";
        cin >> choice;
        if (choice == 1) {
            int r; string n; double c;
            cout << "Enter Roll, Name, CGPA: ";
            cin >> r >> n >> c;
            if(stree.insert(r, n, c)) cout << "Inserted.\n";
            else cout << "Duplicate Roll No.\n";
        }
        else if (choice == 2) {
            int r; cout << "Enter Roll: ";
             cin >> r;
            stree.search(r);
        }
        else if (choice == 3) stree.InOrder();
        else if (choice == 4) {
            int r; cout << "Enter Roll to remove: "; 
            cin >> r;
            if(stree.remove(r)) cout << "Removed.\n";
        }
        else if (choice == 5) {
            double s, e; cout << "Enter min and max CGPA: ";
             cin >> s >> e;
            stree.displayInRange(s, e);
        }
    } while (choice != 6);

    return 0;
}
