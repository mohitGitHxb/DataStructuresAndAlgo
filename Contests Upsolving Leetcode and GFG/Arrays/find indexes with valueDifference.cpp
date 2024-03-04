#include <bits/stdc++.h>
using namespace std;

/* 
The provided code addresses the problem of finding two indices, `i` and `j`, in an array `nums` such that they satisfy two conditions: 

1. `abs(i - j) >= indexDifference`.
2. `abs(nums[i] - nums[j]) >= valueDifference`.

Here's an explanation of the code along with the time and space complexities:

**Code Explanation**:

1. Initialize a vector `prefixMin` to store the minimum values encountered in the `nums` array up to the current index. Similarly, initialize `prefixMax` to store the maximum values encountered.

2. Initialize two variables `mn` (to keep track of the minimum value) and `mx` (to keep track of the maximum value) to positive and negative infinity, respectively.

3. Iterate through the `nums` array to fill `prefixMin` and `prefixMax` arrays and update `mn` and `mx` as follows:
   - Update `mn` as the minimum of `mn` and the current element.
   - Update `mx` as the maximum of `mx` and the current element.
   - Fill `prefixMin` and `prefixMax` with `mn` and `mx`, respectively, up to the current index.

4. Iterate through the `nums` array starting from `indexDifference`. For each iteration, do the following:
   - Calculate `diff` as the current element minus `valueDifference`.
   - Calculate `leftIdx` as the current index minus `indexDifference`.
   - Check if `prefixMin` at index `leftIdx` is less than or equal to `diff`. If true, it means there exists an element within the required index and value difference.
   - If the above condition is satisfied, loop through the elements from index 0 to the current index to find the index of the element in `nums` that matches the `prefixMin` at `leftIdx`. Return the indices `{j, i}` (found element at index `j` and the current element at index `i`).

5. Repeat a similar process for the second condition. Calculate `diff` as the current element plus `valueDifference` and check if `prefixMax` at `leftIdx` is greater than or equal to `diff`. If true, loop through the elements to find the index of the element in `nums` that matches the `prefixMax` at `leftIdx`. Return the indices `{j, i}`.

6. If no valid `i` and `j` are found during the iterations, return `{-1, -1}` as there are no valid indices that satisfy the conditions.

**Time Complexity**:

The code iterates through the `nums` array twice, and within each iteration, there are nested loops to search for matching values. The time complexity is O(N^2), where N is the size of the `nums` array.

**Space Complexity**:

The code uses two additional vectors `prefixMin` and `prefixMax` to store minimum and maximum values up to each index. The space complexity is O(N) for these vectors.

**Hint**:

- The code efficiently tracks the minimum and maximum values in the array while searching for valid indices.
- The use of nested loops for searching may lead to a less optimized solution. You could explore other approaches to achieve the same goal with better time complexity.

 */


class Solution {
public:
    vector<int> findIndices(vector<int>& nums, int indexDifference, int valueDifference) {
        vector<int> prefixMin(nums.size()),prefixMax(nums.size());
        vector<int> ans{-1,-1};
        int n = nums.size();
        int mn = INT_MAX,mx = INT_MIN;
        for(int i = 0; i < n; i++){
            
            mn = min(mn,nums[i]);
            mx = max(mx,nums[i]);
            prefixMax.at(i) = mx;
            prefixMin.at(i) = mn;
        }

        for(int i = indexDifference; i < n; i++){
            int diff = nums.at(i) - valueDifference;
            int leftIdx = i - indexDifference;
            if(prefixMin.at(leftIdx) <= diff){
                for(int j = 0; j <= i; j++){
                    if(nums[j] == prefixMin[leftIdx]){
                        return {j,i};
                    }
                }
            }

            diff = nums.at(i) + valueDifference;
            if(prefixMax.at(leftIdx) >= diff){
                for(int j = 0; j <= i; j++){
                    if(nums.at(j) == prefixMax.at(leftIdx)){
                        return {j,i};
                    }
                }
            }
        }
        return ans;
    }
};
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        //write code here
    }
    return 0;
}