#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int start = 0;
        int end = int(nums.size()) - 1;

        while (start <= end) {
            int mid = start + (end - start) / 2;

            if (nums[mid] == target) {
                return mid;
            }
            else if (nums[mid] > target) {
                end = mid - 1;
            }
            else {
                start = mid + 1;
            }
        }

        return -1;
    }
};

int main() {
    Solution sol;

    // Example 1
    vector<int> nums1 = {-1, 0, 3, 5, 9, 12};
    int target1 = 9;
    int result1 = sol.search(nums1, target1);
    cout << "Target " << target1 << " found at index: " << result1 << endl;

    // Example 2
    vector<int> nums2 = {-1, 0, 3, 5, 9, 12};
    int target2 = 2;
    int result2 = sol.search(nums2, target2);
    cout << "Target " << target2 << " found at index: " << result2 << endl;

    return 0;
}
