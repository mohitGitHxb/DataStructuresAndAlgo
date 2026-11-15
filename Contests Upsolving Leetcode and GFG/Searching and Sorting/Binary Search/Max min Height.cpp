#include <bits/stdc++.h>
using namespace std;
/*

Given a garden with n flowers planted in a row, that is represented by an array arr[], where arr[i] denotes the height of the ith flower.You will water them for k days. In one day you can water w continuous flowers. Whenever you water a flower its height increases by 1 unit. You have to maximize the minimum height of all flowers after  k days of watering.

Examples:

Input: arr[] = [2, 3, 4, 5, 1], k = 2, w = 2
Output: 2
Explanation: The minimum height after watering is 2.
Day 1: Water the last two flowers -> arr becomes [2, 3, 4, 6, 2]
Day 2: Water the last two flowers -> arr becomes [2, 3, 4, 7, 3]

Input: arr[] = [5, 8], k = 5, w = 1
Output: 9
Explanation: The minimum height after watering is 9.
Day 1 - Day 4: Water the first flower -> arr becomes [9, 8]
Day 5: Water the second flower -> arr becomes [9, 9]

Constraints:
1 ≤ arr.size() ≤ 105
1 ≤ w ≤ arr.size()
1 ≤ k ≤ 105
1 ≤ arr[i] ≤ 109
*/
class Solution
{
public:
    int maxMinHeight(vector<int> &arr, int k, int w)
    {
        int n = arr.size();
        int left = 1, right = *max_element(arr.begin(), arr.end()) + k;
        int result = 1;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (canAchieveMinHeight(arr, k, w, mid))
            {
                result = mid;
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }

        return result;
    }

private:
    bool canAchieveMinHeight(vector<int> &arr, int k, int w, int minHeight)
    {
        int n = arr.size();
        vector<int> heights = arr;  // Copy original heights
        vector<int> diff(n + 1, 0); // Difference array for range updates
        int daysUsed = 0;
        int currentAdd = 0; // Current cumulative addition from difference array

        for (int i = 0; i < n; i++)
        {
            // Apply the difference array effect up to position i
            currentAdd += diff[i];
            heights[i] += currentAdd;

            // If current flower height is less than required minimum
            if (heights[i] < minHeight)
            {
                int needed = minHeight - heights[i];
                daysUsed += needed;

                // Check if we exceed available days
                if (daysUsed > k)
                {
                    return false;
                }

                // Apply range update using difference array
                // Water from position i to min(i + w - 1, n - 1)
                int endPos = min(i + w - 1, n - 1);

                // Update difference array for range [i, endPos]
                diff[i] += needed;
                diff[endPos + 1] -= needed;

                // Update current cumulative addition
                currentAdd += needed;
                heights[i] += needed; // Update current position immediately
            }
        }

        return true;
    }
};

/*
How the Difference Array Technique Works:

1. Initialize diff[] array with all zeros
2. For range update [L, R] with value V:
   - diff[L] += V
   - diff[R + 1] -= V

3. To get actual values, compute prefix sum of diff[] array:
   - actualValue[i] = originalValue[i] + prefixSum(diff[0] to diff[i])

Example walkthrough for arr = [2, 3, 4, 5, 1], k = 2, w = 2, checking minHeight = 2:

Initial: heights = [2, 3, 4, 5, 1], diff = [0, 0, 0, 0, 0, 0]

i = 0: heights[0] = 2 >= 2 ✓
i = 1: heights[1] = 3 >= 2 ✓
i = 2: heights[2] = 4 >= 2 ✓
i = 3: heights[3] = 5 >= 2 ✓
i = 4: heights[4] = 1 < 2, need 1 more
       Water range [4, 4] (since min(4+2-1, 4) = 4)
       diff[4] += 1, diff[5] -= 1
       diff = [0, 0, 0, 0, 1, -1]
       daysUsed = 1

Result: Can achieve minHeight = 2 with 1 day (≤ k = 2) ✓

Time Complexity: O(n log(maxHeight + k))
Space Complexity: O(n)
*/