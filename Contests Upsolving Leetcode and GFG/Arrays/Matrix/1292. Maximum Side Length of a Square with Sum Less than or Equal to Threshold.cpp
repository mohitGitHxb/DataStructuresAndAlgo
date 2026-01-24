#include <bits/stdc++.h>
using namespace std;

class Solution
{
private:
    /*
     * PROBLEM UNDERSTANDING:
     * - Given m×n matrix and threshold
     * - Find maximum side length of square submatrix with sum ≤ threshold
     * - Return 0 if no such square exists
     *
     * KEY INSIGHT - 2D Prefix Sum with Pruning:
     *
     * 2D PREFIX SUM TECHNIQUE:
     * - Build prefix sum array where prefixSum[i][j] = sum of rectangle from (0,0) to (i-1,j-1)
     * - Query any rectangle sum in O(1) using inclusion-exclusion principle
     *
     * FORMULA for rectangle sum from (r1,c1) to (r2,c2):
     *   sum = prefixSum[r2+1][c2+1]
     *       - prefixSum[r1][c2+1]     // subtract top rectangle
     *       - prefixSum[r2+1][c1]     // subtract left rectangle
     *       + prefixSum[r1][c1]       // add back top-left (subtracted twice)
     *
     * OPTIMIZATION - Monotonic Property:
     * - If a k×k square at position (i,j) exceeds threshold,
     *   all larger squares (k+1)×(k+1), (k+2)×(k+2), ... will also exceed it
     * - Therefore: break inner loop early when first invalid size found
     * - Also: start checking from maxSide+1 (no need to recheck smaller sizes)
     *
     * EXAMPLE: mat = [[1,1,3,2,4,3,2],[1,1,3,2,4,3,2],[1,1,3,2,4,3,2]], threshold = 4
     *
     * Position (0,0), size 2×2:
     *   Elements: [[1,1],[1,1]]
     *   Sum: 1+1+1+1 = 4 ≤ 4 ✓
     *
     * Position (0,0), size 3×3:
     *   Elements: [[1,1,3],[1,1,3],[1,1,3]]
     *   Sum: 1+1+3+1+1+3+1+1+3 = 15 > 4 ✗
     *   Break! (all larger squares will also exceed)
     *
     * TIME: O(m × n × min(m,n)) average case with pruning
     *       O(m × n × min(m,n)²) worst case without pruning
     * SPACE: O(m × n) for prefix sum array
     */

    /**
     * Builds 2D prefix sum array
     * prefixSum[i][j] = sum of all elements in rectangle from (0,0) to (i-1,j-1)
     *
     * @param mat - input matrix
     * @return 2D prefix sum array (size: (m+1)×(n+1))
     */
    vector<vector<int>> build2DPrefixSum(const vector<vector<int>> &mat)
    {
        int rows = mat.size();
        int cols = mat[0].size();

        // Use 1-based indexing: prefixSum[i][j] covers mat[0..i-1][0..j-1]
        vector<vector<int>> prefixSum(rows + 1, vector<int>(cols + 1, 0));

        for (int i = 1; i <= rows; i++)
        {
            for (int j = 1; j <= cols; j++)
            {
                // Inclusion-exclusion principle
                prefixSum[i][j] = mat[i - 1][j - 1]          // current element
                                  + prefixSum[i - 1][j]      // sum from above
                                  + prefixSum[i][j - 1]      // sum from left
                                  - prefixSum[i - 1][j - 1]; // remove overlap
            }
        }

        return prefixSum;
    }

    /**
     * Computes sum of square submatrix using prefix sums
     *
     * @param prefixSum - precomputed 2D prefix sum array
     * @param topRow - top-left corner row (0-indexed)
     * @param topCol - top-left corner column (0-indexed)
     * @param sideLength - side length of the square
     * @return sum of all elements in the square
     */
    int getSquareSum(const vector<vector<int>> &prefixSum,
                     int topRow, int topCol, int sideLength)
    {
        // Convert to bottom-right corner (inclusive, 0-indexed)
        int bottomRow = topRow + sideLength - 1;
        int bottomCol = topCol + sideLength - 1;

        // Apply 2D prefix sum formula (convert to 1-indexed for prefixSum array)
        int sum = prefixSum[bottomRow + 1][bottomCol + 1] // total rectangle
                  - prefixSum[topRow][bottomCol + 1]      // subtract top
                  - prefixSum[bottomRow + 1][topCol]      // subtract left
                  + prefixSum[topRow][topCol];            // add back overlap

        return sum;
    }

public:
    int maxSideLength(vector<vector<int>> &mat, int threshold)
    {
        int numRows = mat.size();
        int numCols = mat[0].size();

        // Build 2D prefix sum array for O(1) range queries
        vector<vector<int>> prefixSum = build2DPrefixSum(mat);

        int maxSideFound = 0;

        // Try all possible top-left corners
        for (int row = 0; row < numRows; row++)
        {
            for (int col = 0; col < numCols; col++)
            {
                // Maximum possible square size from this position
                int maxPossibleSize = min(numRows - row, numCols - col);

                // Try sizes starting from maxSideFound+1 (optimization)
                // No need to check sizes ≤ maxSideFound (already found)
                for (int size = maxSideFound + 1; size <= maxPossibleSize; size++)
                {
                    int squareSum = getSquareSum(prefixSum, row, col, size);

                    if (squareSum <= threshold)
                    {
                        // Valid square found, update maximum
                        maxSideFound = size;
                    }
                    else
                    {
                        // Exceeded threshold - all larger squares will too
                        // Break early (monotonic property)
                        break;
                    }
                }
            }
        }

        return maxSideFound;
    }
};

/*
 * DETAILED WALKTHROUGH - Example 1:
 * mat = [[1,1,3,2,4,3,2],
 *        [1,1,3,2,4,3,2],
 *        [1,1,3,2,4,3,2]], threshold = 4
 *
 * ===== STEP 1: Build 2D Prefix Sum =====
 *
 * prefixSum[i][j] = sum of rectangle (0,0) to (i-1,j-1)
 *
 *     0   1   2   3   4   5   6   7   8
 *   ┌────────────────────────────────────┐
 * 0 │ 0   0   0   0   0   0   0   0   0  │
 * 1 │ 0   1   2   5   7  11  14  16  │
 * 2 │ 0   2   4  10  14  22  28  32  │
 * 3 │ 0   3   6  15  21  33  42  48  │
 *   └────────────────────────────────────┘
 *
 * Example calculation for prefixSum[2][2]:
 *   = mat[1][1] + prefixSum[1][2] + prefixSum[2][1] - prefixSum[1][1]
 *   = 1 + 2 + 2 - 1
 *   = 4
 *   Represents sum of [[1,1],[1,1]] = 4 ✓
 *
 * ===== STEP 2: Try All Positions and Sizes =====
 *
 * --- Position (0,0) ---
 *
 * Size 1: Square [[1]]
 *   sum = prefixSum[1][1] - prefixSum[0][1] - prefixSum[1][0] + prefixSum[0][0]
 *       = 1 - 0 - 0 + 0 = 1
 *   1 ≤ 4 ✓ → maxSideFound = 1
 *
 * Size 2: Square [[1,1],[1,1]]
 *   sum = prefixSum[2][2] - prefixSum[0][2] - prefixSum[2][0] + prefixSum[0][0]
 *       = 4 - 0 - 0 + 0 = 4
 *   4 ≤ 4 ✓ → maxSideFound = 2
 *
 * Size 3: Square [[1,1,3],[1,1,3],[1,1,3]]
 *   sum = prefixSum[3][3] - prefixSum[0][3] - prefixSum[3][0] + prefixSum[0][0]
 *       = 15 - 0 - 0 + 0 = 15
 *   15 > 4 ✗ → Break! (larger squares will exceed too)
 *
 * --- Position (0,1) ---
 * Start from size 3 (maxSideFound + 1 = 2 + 1)
 *
 * Size 3: Square [[1,3,2],[1,3,2],[1,3,2]]
 *   sum = prefixSum[3][4] - prefixSum[0][4] - prefixSum[3][1] + prefixSum[0][1]
 *       = 21 - 0 - 3 + 0 = 18
 *   18 > 4 ✗ → Break!
 *
 * ... Continue for all positions ...
 *
 * No position yields size > 2 within threshold
 *
 * Final answer: 2 ✓
 *
 * ===================================================================
 *
 * DETAILED WALKTHROUGH - Example 2:
 * mat = [[2,2,2,2,2],
 *        [2,2,2,2,2],
 *        [2,2,2,2,2],
 *        [2,2,2,2,2],
 *        [2,2,2,2,2]], threshold = 1
 *
 * Every 1×1 square has sum = 2 > 1
 * No valid square exists
 *
 * Answer: 0 ✓
 *
 * ===================================================================
 *
 * 2D PREFIX SUM FORMULA VISUALIZATION:
 *
 * To find sum of rectangle from (r1,c1) to (r2,c2):
 *
 *   (0,0) ────────── (0,c2+1)
 *     │  A  │    B   │
 *   (r1,0) ────────── (r1,c2+1)
 *     │  C  │    D   │
 *   (r2+1,0) ──────── (r2+1,c2+1)
 *     │     │         │
 *   (0,c1) (r1,c1) (r2+1,c1)
 *
 * We want: D (the target rectangle)
 *
 * We have:
 *   prefixSum[r2+1][c2+1] = A + B + C + D
 *   prefixSum[r1][c2+1]   = A + B
 *   prefixSum[r2+1][c1]   = A + C
 *   prefixSum[r1][c1]     = A
 *
 * Formula:
 *   D = (A+B+C+D) - (A+B) - (A+C) + A
 *     = A+B+C+D - A-B - A-C + A
 *     = D ✓
 *
 * ===================================================================
 *
 * WHY THIS WORKS - Algorithm Correctness:
 *
 * 1. 2D PREFIX SUM CORRECTNESS:
 *    - Standard technique for range sum queries in 2D
 *    - Inclusion-exclusion principle ensures correct computation
 *    - O(1) query time after O(m×n) preprocessing
 *
 * 2. MONOTONIC PROPERTY OPTIMIZATION:
 *    - If k×k square exceeds threshold, (k+1)×(k+1) will too
 *    - Reason: (k+1)×(k+1) contains all of k×k plus extra elements
 *    - All matrix elements are non-negative → larger squares have larger sums
 *    - Early break saves unnecessary checks
 *
 * 3. STARTING FROM maxSideFound+1:
 *    - No need to check sizes we've already found valid
 *    - If we found valid size k, we know sizes 1..k work somewhere
 *    - Only need to find if larger sizes exist
 *
 * 4. EXHAUSTIVE SEARCH:
 *    - Check all positions ensures we don't miss any valid square
 *    - Guaranteed to find maximum size if it exists
 *
 * 5. EDGE CASES:
 *    - All elements > threshold → return 0
 *    - Single element ≤ threshold → return 1
 *    - Empty matrix → not possible per constraints
 *
 * COMPLEXITY ANALYSIS:
 * - Preprocessing: O(m×n) to build prefix sum
 * - Main loop:
 *   - Positions: O(m×n)
 *   - Sizes per position: O(min(m,n)) worst case
 *   - With early break: often much better (amortized O(1) per position)
 * - Total: O(m×n×min(m,n)) average case with pruning
 * - Space: O(m×n) for prefix sum array
 *
 * OPTIMIZATION OPPORTUNITIES:
 * - Could use binary search on size for each position: O(m×n×log(min(m,n)))
 * - Current approach with pruning is simpler and often faster in practice
 */

int main()
{
    return 0;
}