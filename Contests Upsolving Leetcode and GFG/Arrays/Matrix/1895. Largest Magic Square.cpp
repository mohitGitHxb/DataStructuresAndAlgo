#include <bits/stdc++.h>
using namespace std;
class Solution
{
private:
    /*
     * PROBLEM UNDERSTANDING:
     * - k×k magic square: all rows, columns, and both diagonals sum to same value
     * - Given m×n grid, find largest magic square subgrid
     * - Every 1×1 grid is trivially magic (minimum answer = 1)
     *
     * KEY INSIGHT - Greedy Search with Prefix Sums:
     *
     * STRATEGY:
     * 1. Search from largest possible size down to 2
     * 2. First valid magic square found is the answer (greedy works!)
     * 3. Use prefix sums for O(1) row/column sum queries
     * 4. Diagonals must be computed manually (no precomputation helps)
     *
     * PREFIX SUM OPTIMIZATION:
     * - Without prefix sums: O(k) to compute each row/column sum
     * - With prefix sums: O(1) to compute any row/column sum
     * - Critical for efficiency when checking many squares
     *
     * MAGIC SQUARE VALIDATION:
     * For a k×k square starting at (r, c):
     * 1. Compute reference sum (use first row)
     * 2. Check all k rows have this sum
     * 3. Check all k columns have this sum
     * 4. Check both diagonals have this sum
     * 5. All 2k+2 sums must match
     *
     * EXAMPLE: grid = [[7,1,4,5,6],[2,5,1,6,4],[1,5,4,3,2],[1,2,7,3,4]]
     *
     * Testing size=3 at position (1,1):
     *   [5, 1, 6]
     *   [5, 4, 3]    All sums = 12 ✓
     *   [2, 7, 3]
     *
     * TIME: O(min(m,n)³ × m × n) worst case
     *       - O(min(m,n)) sizes to try
     *       - O(m×n) positions per size
     *       - O(min(m,n)) validation per position
     * SPACE: O(m×n) for prefix sum arrays
     */

    /**
     * Validates if a k×k subgrid is a magic square
     * Uses precomputed prefix sums for rows and columns
     *
     * @param grid - original grid
     * @param rowPrefixSum - prefix sums for rows
     * @param colPrefixSum - prefix sums for columns
     * @param startRow - top-left corner row
     * @param startCol - top-left corner column
     * @param size - side length of square to check
     * @return true if this subgrid forms a magic square
     */
    bool isMagicSquare(const vector<vector<int>> &grid,
                       const vector<vector<int>> &rowPrefixSum,
                       const vector<vector<int>> &colPrefixSum,
                       int startRow, int startCol, int size)
    {
        // Compute reference sum using first row
        // All other sums must match this value
        int targetSum = rowPrefixSum[startRow][startCol + size] -
                        rowPrefixSum[startRow][startCol];

        // Check all rows (starting from row 1, since row 0 is the reference)
        for (int i = 1; i < size; i++)
        {
            int rowSum = rowPrefixSum[startRow + i][startCol + size] -
                         rowPrefixSum[startRow + i][startCol];
            if (rowSum != targetSum)
            {
                return false;
            }
        }

        // Check all columns
        for (int j = 0; j < size; j++)
        {
            int colSum = colPrefixSum[startRow + size][startCol + j] -
                         colPrefixSum[startRow][startCol + j];
            if (colSum != targetSum)
            {
                return false;
            }
        }

        // Check main diagonal (top-left to bottom-right)
        int mainDiagonalSum = 0;
        for (int k = 0; k < size; k++)
        {
            mainDiagonalSum += grid[startRow + k][startCol + k];
        }
        if (mainDiagonalSum != targetSum)
        {
            return false;
        }

        // Check anti-diagonal (top-right to bottom-left)
        int antiDiagonalSum = 0;
        for (int k = 0; k < size; k++)
        {
            antiDiagonalSum += grid[startRow + k][startCol + size - 1 - k];
        }
        if (antiDiagonalSum != targetSum)
        {
            return false;
        }

        return true; // All checks passed!
    }

    /**
     * Builds prefix sum array for rows
     * rowPrefixSum[i][j] = sum of grid[i][0..j-1]
     *
     * @param grid - input grid
     * @return 2D array of row prefix sums
     */
    vector<vector<int>> buildRowPrefixSums(const vector<vector<int>> &grid)
    {
        int rows = grid.size();
        int cols = grid[0].size();
        vector<vector<int>> rowPrefixSum(rows, vector<int>(cols + 1, 0));

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                rowPrefixSum[i][j + 1] = rowPrefixSum[i][j] + grid[i][j];
            }
        }

        return rowPrefixSum;
    }

    /**
     * Builds prefix sum array for columns
     * colPrefixSum[i][j] = sum of grid[0..i-1][j]
     *
     * @param grid - input grid
     * @return 2D array of column prefix sums
     */
    vector<vector<int>> buildColPrefixSums(const vector<vector<int>> &grid)
    {
        int rows = grid.size();
        int cols = grid[0].size();
        vector<vector<int>> colPrefixSum(rows + 1, vector<int>(cols, 0));

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                colPrefixSum[i + 1][j] = colPrefixSum[i][j] + grid[i][j];
            }
        }

        return colPrefixSum;
    }

public:
    int largestMagicSquare(vector<vector<int>> &grid)
    {
        int numRows = grid.size();
        int numCols = grid[0].size();

        // Precompute prefix sums for O(1) range queries
        vector<vector<int>> rowPrefixSum = buildRowPrefixSums(grid);
        vector<vector<int>> colPrefixSum = buildColPrefixSums(grid);

        // Try sizes from largest to smallest (greedy: first valid is answer)
        int maxPossibleSize = min(numRows, numCols);

        for (int size = maxPossibleSize; size >= 2; size--)
        {
            // Try all possible top-left positions for this size
            for (int row = 0; row + size <= numRows; row++)
            {
                for (int col = 0; col + size <= numCols; col++)
                {
                    // Check if this position forms a magic square
                    if (isMagicSquare(grid, rowPrefixSum, colPrefixSum,
                                      row, col, size))
                    {
                        return size; // Found largest magic square!
                    }
                }
            }
        }

        // No magic square of size ≥2 found, return 1 (always valid)
        return 1;
    }
};

/*
 * DETAILED WALKTHROUGH - Example 1:
 * grid = [[7,1,4,5,6],[2,5,1,6,4],[1,5,4,3,2],[1,2,7,3,4]]
 *
 * Grid visualization (4×5):
 *     0  1  2  3  4
 *   ┌──────────────┐
 * 0 │ 7  1  4  5  6│
 * 1 │ 2  5  1  6  4│
 * 2 │ 1  5  4  3  2│
 * 3 │ 1  2  7  3  4│
 *   └──────────────┘
 *
 * ===== STEP 1: Build Prefix Sums =====
 *
 * Row Prefix Sums (rowPrefixSum[i][j] = sum of grid[i][0..j-1]):
 *     0   1   2   3   4   5   6
 *   ┌────────────────────────────┐
 * 0 │ 0   7   8  12  17  23  │
 * 1 │ 0   2   7   8  14  18  │
 * 2 │ 0   1   6  10  13  15  │
 * 3 │ 0   1   3  10  13  17  │
 *   └────────────────────────────┘
 *
 * Column Prefix Sums (colPrefixSum[i][j] = sum of grid[0..i-1][j]):
 *     0   1   2   3   4
 *   ┌────────────────────┐
 * 0 │ 0   0   0   0   0  │
 * 1 │ 7   1   4   5   6  │
 * 2 │ 9   6   5  11  10  │
 * 3 │10  11   9  14  12  │
 * 4 │11  13  16  17  16  │
 *   └────────────────────┘
 *
 * ===== STEP 2: Try Size 4 =====
 * Max size = min(4, 5) = 4
 * Valid positions: (0,0), (0,1)
 * Check both... (assume they fail for brevity)
 *
 * ===== STEP 3: Try Size 3 =====
 * Valid positions: (0,0), (0,1), (0,2), (1,0), (1,1), (1,2)
 *
 * --- Check position (1, 1) ---
 * Subgrid:
 *   [5, 1, 6]
 *   [5, 4, 3]
 *   [2, 7, 3]
 *
 * Reference sum (first row):
 *   rowPrefixSum[1][4] - rowPrefixSum[1][1] = 14 - 2 = 12 ✓
 *
 * Check row 1 (index 2 in grid):
 *   rowPrefixSum[2][4] - rowPrefixSum[2][1] = 13 - 1 = 12 ✓
 *
 * Check row 2 (index 3 in grid):
 *   rowPrefixSum[3][4] - rowPrefixSum[3][1] = 13 - 1 = 12 ✓
 *
 * Check column 0 (index 1 in grid):
 *   colPrefixSum[4][1] - colPrefixSum[1][1] = 13 - 1 = 12 ✓
 *
 * Check column 1 (index 2 in grid):
 *   colPrefixSum[4][2] - colPrefixSum[1][2] = 16 - 4 = 12 ✓
 *
 * Check column 2 (index 3 in grid):
 *   colPrefixSum[4][3] - colPrefixSum[1][3] = 17 - 5 = 12 ✓
 *
 * Check main diagonal:
 *   grid[1][1] + grid[2][2] + grid[3][3] = 5 + 4 + 3 = 12 ✓
 *
 * Check anti-diagonal:
 *   grid[1][3] + grid[2][2] + grid[3][1] = 6 + 4 + 2 = 12 ✓
 *
 * All checks passed! Return 3 ✓
 *
 * ===================================================================
 *
 * PREFIX SUM FORMULA EXPLANATION:
 *
 * To get sum of grid[i][c..c+size-1]:
 *   rowPrefixSum[i][c+size] - rowPrefixSum[i][c]
 *
 * Example: sum of grid[1][1..3] = elements at columns 1,2,3
 *   rowPrefixSum[1][4] - rowPrefixSum[1][1]
 *   = (2+5+1+6) - (2)
 *   = 14 - 2 = 12
 *   = 5 + 1 + 6 ✓
 *
 * Similarly for columns:
 *   colPrefixSum[r+size][j] - colPrefixSum[r][j]
 *
 * ===================================================================
 *
 * WHY THIS WORKS - Algorithm Correctness:
 *
 * 1. GREEDY SEARCH ORDER:
 *    - Searching from largest to smallest ensures first match is maximum
 *    - No need to continue after finding valid magic square
 *
 * 2. PREFIX SUM CORRECTNESS:
 *    - Standard technique: prefixSum[i] = sum of elements [0..i-1]
 *    - Range [L, R] sum = prefixSum[R+1] - prefixSum[L]
 *    - Enables O(1) queries instead of O(k) iteration
 *
 * 3. MAGIC SQUARE VALIDATION:
 *    - Must check k rows + k columns + 2 diagonals = 2k+2 sums
 *    - All must equal the target sum (we use first row as reference)
 *    - Early termination on first mismatch for efficiency
 *
 * 4. DIAGONAL COMPUTATION:
 *    - Main diagonal: grid[r+i][c+i] for i in [0, k)
 *    - Anti-diagonal: grid[r+i][c+k-1-i] for i in [0, k)
 *    - Cannot use prefix sums (not axis-aligned)
 *
 * 5. BASE CASE:
 *    - Return 1 if no larger magic square found
 *    - Every 1×1 grid is trivially magic (single element sums to itself)
 *
 * COMPLEXITY ANALYSIS:
 * - Preprocessing: O(m×n) to build prefix sums
 * - Main loop:
 *   - Sizes: O(min(m,n))
 *   - Positions per size: O(m×n)
 *   - Validation per position: O(k) where k = size
 * - Total: O(min(m,n)² × m × n) average case
 *   (Often much better due to early termination)
 * - Space: O(m×n) for prefix sum arrays
 *
 * OPTIMIZATION NOTES:
 * - Prefix sums reduce validation from O(k²) to O(k)
 * - Early termination on mismatch saves unnecessary checks
 * - Could further optimize by checking diagonals first (most likely to fail)
 */
int main()
{
    return 0;
}