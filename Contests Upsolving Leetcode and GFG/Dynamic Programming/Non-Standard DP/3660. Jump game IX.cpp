#include <bits/stdc++.h>
using namespace std;
class Solution {
private:
    /*
     * PROBLEM UNDERSTANDING:
     * - From index i, can jump to j where:
     *   - If j > i: allowed only if nums[j] < nums[i] (jump right to smaller)
     *   - If j < i: allowed only if nums[j] > nums[i] (jump left to greater)
     * - Goal: For each index, find maximum value reachable through any jump sequence
     * 
     * KEY INSIGHT - Greedy Path Following:
     * 
     * OBSERVATION 1: Jumping Right (to smaller values)
     * - From position i, if we jump right to j (nums[j] < nums[i])
     * - From j, we can potentially jump left to find larger values
     * - The key: smallest value to the right opens door to largest value to its left
     * 
     * OBSERVATION 2: Pattern Recognition
     * - If max(nums[0..i]) ≤ min(nums[i+1..n-1]):
     *   Cannot jump from left partition to right partition
     *   Answer is just max in left partition
     * - Otherwise:
     *   Can jump right, then potentially jump left to find max
     *   Answer propagates from the right
     * 
     * OBSERVATION 3: Right-to-Left Processing
     * - Process from right to left
     * - For each position, check if we can "escape" to the right
     * - If we can escape right, we inherit the answer from position i+1
     * - If we can't escape, answer is local maximum to the left
     * 
     * APPROACH:
     * 1. Precompute prefix max: maxToLeft[i] = max(nums[0..i])
     * 2. Precompute suffix min: minToRight[i] = min(nums[i..n-1])
     * 3. Process right-to-left:
     *    - If maxToLeft[i] > minToRight[i+1]: can jump right, inherit ans[i+1]
     *    - Otherwise: stuck in left partition, answer is maxToLeft[i]
     * 
     * EXAMPLE: nums = [2,3,1]
     * 
     * maxToLeft:   [2, 3, 3]
     * minToRight:  [1, 1, 1]
     * 
     * At i=2: ans[2] = 3 (base case, rightmost position)
     * At i=1: maxToLeft[1]=3, minToRight[2]=1
     *         3 > 1 → can jump right → ans[1] = ans[2] = 3
     * At i=0: maxToLeft[0]=2, minToRight[1]=1
     *         2 > 1 → can jump right → ans[0] = ans[1] = 3
     * 
     * Result: [3, 3, 3] ✓
     * 
     * TIME: O(n)
     * SPACE: O(n)
     */

public:
    vector<int> maxValue(vector<int>& nums) {
        int n = nums.size();
        
        // Prefix maximum: maxToLeft[i] = max value in nums[0..i]
        vector<int> maxToLeft(n);
        
        // Suffix minimum: minToRight[i] = min value in nums[i..n-1]
        vector<int> minToRight(n);
        
        // Build prefix maximum array
        maxToLeft[0] = nums[0];
        for (int i = 1; i < n; i++) {
            maxToLeft[i] = max(nums[i], maxToLeft[i - 1]);
        }
        
        // Build suffix minimum array
        minToRight[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            minToRight[i] = min(nums[i], minToRight[i + 1]);
        }
        
        // Build answer array from right to left
        vector<int> result(n);
        
        // Base case: rightmost position
        // Can only look at elements to its left (which includes itself)
        result[n - 1] = maxToLeft[n - 1];
        
        // Process from right to left
        for (int i = n - 2; i >= 0; i--) {
            // Check if we can "escape" to the right partition
            // Can escape if: max element to our left > min element to our right
            if (maxToLeft[i] > minToRight[i + 1]) {
                // Can jump right to smaller values, then potentially left to larger
                // Inherit the answer from position i+1
                result[i] = result[i + 1];
            } else {
                // Cannot jump right (max left ≤ min right)
                // Stuck in left partition, best we can do is local max
                result[i] = maxToLeft[i];
            }
        }
        
        return result;
    }
};

/*
 * DETAILED WALKTHROUGH - Example 1: nums = [2,1,3]
 * 
 * ===== STEP 1: Build Prefix Maximum =====
 * maxToLeft[0] = 2
 * maxToLeft[1] = max(1, 2) = 2
 * maxToLeft[2] = max(3, 2) = 3
 * 
 * maxToLeft = [2, 2, 3]
 * 
 * ===== STEP 2: Build Suffix Minimum =====
 * minToRight[2] = 3
 * minToRight[1] = min(1, 3) = 1
 * minToRight[0] = min(2, 1) = 1
 * 
 * minToRight = [1, 1, 3]
 * 
 * ===== STEP 3: Build Result (Right to Left) =====
 * 
 * i=2 (base case):
 *   result[2] = maxToLeft[2] = 3
 * 
 * i=1:
 *   maxToLeft[1] = 2
 *   minToRight[2] = 3
 *   2 > 3? NO
 *   Cannot escape right
 *   result[1] = maxToLeft[1] = 2
 * 
 * i=0:
 *   maxToLeft[0] = 2
 *   minToRight[1] = 1
 *   2 > 1? YES
 *   Can escape right
 *   result[0] = result[1] = 2
 * 
 * Final: [2, 2, 3] ✓
 * 
 * Verification:
 * - From i=0: Can jump to i=2 (1 < 2), but stuck at 1. Best = 2 ✓
 * - From i=1: Can jump to i=0 (2 > 1). Best = 2 ✓
 * - From i=2: Already at 3, no better. Best = 3 ✓
 * 
 * ===================================================================
 * 
 * DETAILED WALKTHROUGH - Example 2: nums = [2,3,1]
 * 
 * ===== Arrays =====
 * maxToLeft = [2, 3, 3]
 * minToRight = [1, 1, 1]
 * 
 * ===== Build Result =====
 * i=2: result[2] = 3
 * 
 * i=1:
 *   maxToLeft[1] = 3, minToRight[2] = 1
 *   3 > 1? YES → result[1] = result[2] = 3
 * 
 * i=0:
 *   maxToLeft[0] = 2, minToRight[1] = 1
 *   2 > 1? YES → result[0] = result[1] = 3
 * 
 * Final: [3, 3, 3] ✓
 * 
 * Verification:
 * - From i=0: Jump to i=2 (1<2), then to i=1 (3>1). Best = 3 ✓
 * - From i=1: Already at 3. Best = 3 ✓
 * - From i=2: Jump to i=1 (3>1). Best = 3 ✓
 * 
 * ===================================================================
 * 
 * WHY THIS WORKS - Algorithm Correctness:
 * 
 * 1. PARTITION CONCEPT:
 *    - At each position i, divide array into left [0..i] and right [i+1..n-1]
 *    - If max(left) > min(right): can bridge from left to right
 *    - This enables jumping right to small value, then left to large value
 * 
 * 2. ANSWER PROPAGATION:
 *    - If we can bridge to right, answer propagates from right
 *    - Why? Because position i+1 has already computed best reachable from there
 *    - By inheriting ans[i+1], we get transitivity of reachability
 * 
 * 3. LOCAL MAXIMUM FALLBACK:
 *    - If cannot bridge right (max left ≤ min right)
 *    - Best we can do is jump around in left partition
 *    - Maximum reachable is maxToLeft[i]
 * 
 * 4. RIGHT-TO-LEFT PROCESSING:
 *    - Ensures ans[i+1] is computed before ans[i]
 *    - Enables answer propagation
 *    - Base case: rightmost element uses local maximum
 * 
 * 5. GREEDY CORRECTNESS:
 *    - Don't need to explore all paths
 *    - If bridging is possible, optimal path goes through it
 *    - Greedy choice of inheriting from right is optimal
 * 
 * COMPLEXITY ANALYSIS:
 * - Time: O(n) for building arrays + O(n) for result = O(n)
 * - Space: O(n) for auxiliary arrays
 * 
 * EDGE CASES:
 * - Single element: result = [nums[0]]
 * - Sorted ascending: each position's max is rightmost (global max)
 * - Sorted descending: each position's max is itself (can't jump productively)
 * - All same: result = array of same value
 */

int main()
{
    return 0;
}