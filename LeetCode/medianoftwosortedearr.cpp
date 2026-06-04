class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // Step 1: Merge the two arrays
        vector<int> merged;
        
        // Add all elements from nums1
        for (int num : nums1) {
            merged.push_back(num);
        }
        
        // Add all elements from nums2
        for (int num : nums2) {
            merged.push_back(num);
        }
        
        // Step 2: Sort the merged array
        sort(merged.begin(), merged.end());
        
        // Step 3: Find the median
        int n = merged.size();
        if (n % 2 == 1) {
            // Odd length - return middle element
            return merged[n / 2];
        } else {
            // Even length - return average of two middle elements
            return (merged[n / 2 - 1] + merged[n / 2]) / 2.0;
        }
    }
};