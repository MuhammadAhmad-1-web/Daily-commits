#include <iostream>
#include <vector> 

using namespace std;


int findFirstNonRepeating(const vector<int>& input) {
    int counts[2001] = {0}; 
    int offset = 1000;
    for (int i = 0; i < input.size(); i++) {
        int originalNum = input[i];
        if (originalNum < -1000 || originalNum > 1000) {
            continue; 
        }
        int shiftedIndex = originalNum + offset; 
        counts[shiftedIndex]++;
    }
    for (int i = 0; i < input.size(); i++) {
        int originalNum = input[i];
        if (originalNum < -1000 || originalNum > 1000) {
            continue;}
        int shiftedIndex = originalNum + offset;

        if (counts[shiftedIndex] == 1) {
            return originalNum;
        }
    }
    return -1;
}

int main(){
    cout << "--- TASK 2: ---" << endl;
    vector<int> v1 = { 4, 5, 6, 7, 4, 6, 5, 6, 4, 5, 5, 6 };
    cout << "Sample 1: " << findFirstNonRepeating(v1) << endl; 

    vector<int> v2 = { 1, 5, 2, 5, 4, 1, 2, 3, 4, 3, 5 };
    cout << "Sample 2: " << findFirstNonRepeating(v2) << endl; 
    
    
    return 0;
}
