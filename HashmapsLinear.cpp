#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class HashTable {
private:
    string* table;
    int S; // Table size
    int n; // Current number of elements

public:
    // Constructor
    HashTable(int size) {
        S = size;
        n = 0;
        table = new string[S];
        // Initialize table with empty strings
        for (int i = 0; i < S; i++) {
            table[i] = ""; 
        }
    }

    // Destructor
    ~HashTable() {
        delete[] table;
    }

    // Checks whether the hash table is empty
    bool isEmpty() {
        return n == 0;
    }

    // Checks whether the hash table is full
    bool isFull() {
        return n == S;
    }

    
    double loadFactor() {
        if (S == 0) return 0.0;           // Load Factor
        return (double)n / S;
    }

    // Helper function to get Sum of ASCII values 
    int getHashValue(string name) {
        int sum = 0;
        for (char c : name) {
            sum += int(c);
        }
        return sum % S; // Modulo by table size 
    }

    // Insert function with Linear Probing 
    bool insert(string name) {
        if (isFull()) {
            cout << "Table is Full!" << endl;
            return false;
        }

        int index = getHashValue(name);
        int originalIndex = index;
        int i = 0;

        cout << "Traversing indices: ";

        // Linear Probing: Look for empty slot
        while (table[index] != "") {
            cout << index << " -> ";
            
            // If duplicate name found, usually we stop or update. 
            
            
            i++;
            index = (originalIndex + i) % S; // Increment by 1 (wrapped) 
            
           
        }

        cout << index << endl; // Print final slot
        table[index] = name;
        n++;
        return true;
    }

    // Search function 
    bool search(string name) {
        if (isEmpty()) return false;

        int index = getHashValue(name);
        int originalIndex = index;
        int i = 0;

        cout << "Traversing indices: ";

        // Probe until we find name or hit an empty slot
        while (table[index] != "") {
            cout << index << " ";
            
            if (table[index] == name) {
                cout << endl;
                return true;
            }

            i++;
            index = (originalIndex + i) % S;
            cout << "-> ";

            // We searched the whole table and came back to start
            if (index == originalIndex) break; 
        }
        
        cout << "End" << endl;
        return false;
    }

    // Remove function 
    bool remove(string name) {
        if (isEmpty()) return false;

        int index = getHashValue(name);
        int originalIndex = index;
        int i = 0;

        while (table[index] != "") {
            if (table[index] == name) {
                table[index] = ""; // Clear the slot
                n--;
                return true;
            }

            i++;
            index = (originalIndex + i) % S;

            if (index == originalIndex) break;
        }
        return false;
    }

    // Display function 
    void display() {
        cout << "--- Hash Table Content ---" << endl;
        for (int i = 0; i < S; i++) {
            cout << "Index " << i << ": ";
            if (table[i] == "") {
                cout << "EMPTY" << endl; 
            } else {
                cout << table[i] << endl;
            }
        }
        cout << "--------------------------"<<endl;
    }
};

int main() {
    int size;
    cout << "Task 02" << endl; 
    cout << "Enter the size of Hash Table: ";
    cin >> size;

    HashTable ht(size);
    int choice;
    string name;

    do {
       
        cout << "1. Insert a name" << endl;
        cout << "2. Search for a name" << endl;
        cout << "3. Remove a name" << endl;
        cout << "4. Display the Hash Table" << endl;
        cout << "5. Display Load Factor of the table" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter nsme to insert: ";
            cin >> name;
            if (ht.insert(name)) {
                cout << "Inserted successfully." << endl;
            } else {
                cout << "Insertion failed." << endl;
            }
            break;
        case 2:
            cout << "Enter name to search: ";
            cin >> name;
            if (ht.search(name)) {
                cout << "Name found!" << endl;
            } else {
                cout << "Name not found." << endl;
            }
            break;
        case 3:
            cout << "Enter name to remove: ";
            cin >> name;
            if (ht.remove(name)) {
                cout << "Removed successfully." << endl;
            } else {
                cout << "Name not found." << endl;
            }
            break;
        case 4:
            ht.display();
            break;
        case 5:
            cout << "Load Factor: " << ht.loadFactor() << endl;
            break;
        case 6:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 6);

    return 0;
}
