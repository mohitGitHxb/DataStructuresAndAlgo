#include <bits/stdc++.h>
using namespace std;
/*
You are given a positive integer n, indicating that we initially have an n x n 0-indexed integer matrix mat filled with zeroes.

You are also given a 2D integer array query. For each query[i] = [row1i, col1i, row2i, col2i], you should do the following operation:

    Add 1 to every element in the submatrix with the top left corner (row1i, col1i) and the bottom right corner (row2i, col2i). That is, add 1 to mat[x][y] for all row1i <= x <= row2i and col1i <= y <= col2i.

Return the matrix mat after performing every query.



Example 1:

Input: n = 3, queries = [[1,1,2,2],[0,0,1,1]]
Output: [[1,1,0],[1,2,1],[0,1,1]]
Explanation: The diagram above shows the initial matrix, the matrix after the first query, and the matrix after the second query.
- In the first query, we add 1 to every element in the submatrix with the top left corner (1, 1) and bottom right corner (2, 2).
- In the second query, we add 1 to every element in the submatrix with the top left corner (0, 0) and bottom right corner (1, 1).

Example 2:

Input: n = 2, queries = [[0,0,1,1]]
Output: [[1,1],[1,1]]
Explanation: The diagram above shows the initial matrix and the matrix after the first query.
- In the first query we add 1 to every element in the matrix.


*/
/*
========================================================================================
                        PROBLEM UNDERSTANDING & APPROACH
========================================================================================

PROBLEM BREAKDOWN:
- We have an n×n matrix initialized with zeros
- We need to perform multiple range update queries
- Each query adds 1 to all elements in a submatrix defined by (row1, col1) to (row2, col2)
- Naive approach: For each query, iterate through the entire submatrix → O(Q × n²) time

THE KEY INSIGHT - DIFFERENCE ARRAY TECHNIQUE:
Instead of updating each element individually, we can use a "difference array" approach
to mark only the boundaries of changes, then reconstruct the final matrix efficiently.

========================================================================================
                        WHY DIFFERENCE ARRAY WORKS
========================================================================================

INTUITION:
Think of it like a timeline of events:
- When you enter a range, mark "+1" at the start
- When you exit a range, mark "-1" right after the end
- Taking cumulative sum gives you the actual values

For 1D array [0,0,0,0,0], to add 1 to range [1,3]:
    diff[1] = +1, diff[4] = -1  →  [0, 1, 0, 0, -1]
    Prefix sum  →  [0, 1, 1, 1, 0]  ✓ Correct!

For 2D matrix, we apply this idea row-wise:
- For each row in the query range, mark column boundaries
- Then compute prefix sum across each row

========================================================================================
                        ALGORITHM WALKTHROUGH
========================================================================================

STEP 1: Process each query and mark boundaries (row-wise difference array)
    For query (row1, col1, row2, col2):
        - For each row from row1 to row2:
            • Increment diffArray[row][col1] by 1 (start of range)
            • Decrement diffArray[row][col2+1] by 1 (end of range marker)

    This marks where increments START and STOP in each affected row.

STEP 2: Compute prefix sum row-wise to get final values
    For each row:
        - Compute cumulative sum from left to right
        - This converts boundary markers into actual increment values

TIME COMPLEXITY: O(Q × n) for processing queries + O(n²) for prefix sum = O(Q × n + n²)
SPACE COMPLEXITY: O(n²) for the difference array

========================================================================================
*/

class Solution
{
public:
    vector<vector<int>> rangeAddQueries(int n, vector<vector<int>> &queries)
    {
        // Initialize difference array - stores boundary markers, not actual values yet
        vector<vector<int>> diffArray(n, vector<int>(n, 0));

        // ==================== STEP 1: Mark Query Boundaries ====================
        // For each query, we mark the START and END of the range in each affected row
        for (auto q : queries)
        {
            int row1 = q[0], col1 = q[1], row2 = q[2], col2 = q[3];

            // Process each row in the query range [row1, row2]
            for (int i = row1; i <= row2; i++)
            {
                // MARK START: Increment at col1 means "add 1 starting here"
                diffArray[i][col1]++;

                // MARK END: Decrement at col2+1 means "stop adding after col2"
                // Only if col2+1 is within bounds
                if (col2 + 1 < n)
                    diffArray[i][col2 + 1]--;
            }

            // Example: For query (1,1,2,2) in 3×3 matrix:
            // Row 1: diff[1][1]++, diff[1][3]-- (if exists)
            // Row 2: diff[2][1]++, diff[2][3]-- (if exists)
        }

        // ==================== STEP 2: Convert to Actual Values ====================
        // Apply prefix sum across each row to convert markers into actual increments
        for (int i = 0; i < n; i++)
        {
            for (int j = 1; j < n; j++)
            {
                // Cumulative sum: current value = current marker + previous cumulative
                diffArray[i][j] += diffArray[i][j - 1];

                // This "spreads" the increment from col1 to col2 in each row
                // The -1 at col2+1 cancels out the spreading beyond col2
            }
        }

        // The diffArray now contains the final incremented values
        return diffArray;
    }
};

/*
========================================================================================
                        EXAMPLE TRACE
========================================================================================

Example: n = 3, queries = [[1,1,2,2], [0,0,1,1]]

Initial diffArray:
    [0, 0, 0]
    [0, 0, 0]
    [0, 0, 0]

After Query 1 [1,1,2,2]:
    [0, 0, 0]
    [0, 1, 0]  ← row 1: diff[1][1]++
    [0, 1, 0]  ← row 2: diff[2][1]++

After Query 2 [0,0,1,1]:
    [1, 0, -1] ← row 0: diff[0][0]++, diff[0][2]--
    [1, 1, -1] ← row 1: diff[1][0]++, diff[1][2]--
    [0, 1, 0]

After Prefix Sum:
    [1, 1, 0]  ← 1, 1+0=1, 1+(-1)=0
    [1, 2, 1]  ← 1, 1+1=2, 2+(-1)=1
    [0, 1, 1]  ← 0, 0+1=1, 1+0=1

========================================================================================
                        KEY TAKEAWAYS FOR SIMILAR PROBLEMS
========================================================================================

1. When you need multiple RANGE UPDATES, think DIFFERENCE ARRAY
2. Mark boundaries (+1 at start, -1 after end) instead of updating each element
3. Use prefix sum to reconstruct actual values from boundary markers
4. Works in 1D (lines), 2D (rectangles), and can extend to higher dimensions
5. Trades update time for reconstruction time - beneficial when Q is large

Related Problems:
- Range update queries on arrays (1D difference array)
- 2D range updates (this problem)
- Coordinate compression with range updates
- Batch processing of interval additions
========================================================================================
*/
int main()
{
    return 0;
}