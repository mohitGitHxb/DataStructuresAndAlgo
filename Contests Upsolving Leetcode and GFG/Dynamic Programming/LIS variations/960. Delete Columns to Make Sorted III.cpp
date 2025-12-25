#include <bits/stdc++.h>
using namespace std;
class Solution
{
private:
    /*
     * PROBLEM UNDERSTANDING:
     * - Given n strings (rows), all same length
     * - Can delete columns (same index from all strings)
     * - Goal: After deletion, EACH ROW should be individually sorted
     *   (NOT comparing rows to each other, but each row's chars left-to-right)
     *
     * KEY INSIGHT - LIS (Longest Increasing Subsequence) Approach:
     *
     * Instead of thinking "which columns to delete", think:
     * "Which columns can we KEEP such that every row remains sorted?"
     *
     * Answer: Find the LONGEST subsequence of columns where:
     * - For EVERY row, the characters in those columns are non-decreasing
     * - This is the maximum columns we can keep
     * - Minimum deletions = Total columns - Maximum columns we can keep
     *
     * EXAMPLE: strs = ["babca", "bbazb"]
     *
     * Column indices:  0     1     2     3     4
     * Row 0:          'b'   'a'   'b'   'c'   'a'
     * Row 1:          'b'   'b'   'a'   'z'   'b'
     *
     * Can we keep columns {0, 2}?
     *   Row 0: 'b' <= 'b' ✓
     *   Row 1: 'b' <= 'a' ✗ (FAILS!)
     *
     * Can we keep columns {2, 3}?
     *   Row 0: 'b' <= 'c' ✓
     *   Row 1: 'a' <= 'z' ✓
     *   This works! Length = 2
     *
     * LIS approach finds longest valid subsequence = 2
     * Minimum deletions = 5 - 2 = 3
     *
     * DP STATE:
     * dp[col] = length of longest valid subsequence ending at column 'col'
     *
     * TRANSITION:
     * For each column i, check all previous columns j < i:
     *   If keeping columns j and i together is valid (all rows satisfy char[j] <= char[i])
     *   Then: dp[i] = max(dp[i], dp[j] + 1)
     *
     * TIME: O(cols² * rows) - for each pair of columns, check all rows
     * SPACE: O(cols)
     */

    /**
     * Checks if two columns can be kept together in sequence
     * Valid if for EVERY row: character at col1 <= character at col2
     *
     * @param strs - array of strings
     * @param col1 - earlier column index
     * @param col2 - later column index
     * @return true if all rows satisfy strs[row][col1] <= strs[row][col2]
     */
    bool canKeepColumnsTogether(const vector<string> &strs, int col1, int col2)
    {
        // Check every row to ensure non-decreasing order
        for (int row = 0; row < strs.size(); row++)
        {
            // If any row has char at col1 > char at col2, we can't keep both columns
            if (strs[row][col1] > strs[row][col2])
            {
                return false;
            }
        }
        return true; // All rows satisfy the condition
    }

public:
    int minDeletionSize(vector<string> &strs)
    {
        int numRows = strs.size();
        int numCols = strs[0].length();

        // dp[col] = length of longest increasing subsequence of columns ending at 'col'
        // where "increasing" means all rows remain sorted
        vector<int> dp(numCols, 1); // Each column alone forms a subsequence of length 1

        // Track the longest valid subsequence found
        int longestValidSubsequence = 1;

        // Classic LIS pattern: for each column, check all previous columns
        for (int currentCol = 0; currentCol < numCols; currentCol++)
        {

            // Try extending from each previous column
            for (int prevCol = 0; prevCol < currentCol; prevCol++)
            {

                // Check if we can keep both prevCol and currentCol together
                // This means: for ALL rows, char[prevCol] <= char[currentCol]
                if (canKeepColumnsTogether(strs, prevCol, currentCol))
                {
                    // We can extend the subsequence ending at prevCol
                    // New length = length ending at prevCol + 1 (adding currentCol)
                    dp[currentCol] = max(dp[currentCol], dp[prevCol] + 1);
                }
            }

            // Update the global maximum
            longestValidSubsequence = max(longestValidSubsequence, dp[currentCol]);
        }

        // Minimum deletions = Total columns - Maximum columns we can keep
        return numCols - longestValidSubsequence;
    }
};

/*
 * DETAILED WALKTHROUGH - Example 1: strs = ["babca", "bbazb"]
 *
 * Visual representation:
 * Column:     0     1     2     3     4
 * Row 0:     'b'   'a'   'b'   'c'   'a'
 * Row 1:     'b'   'b'   'a'   'z'   'b'
 *
 * ===== Building DP Table =====
 *
 * Initial: dp = [1, 1, 1, 1, 1] (each column alone is valid)
 *
 * --- Processing Column 0 ---
 * No previous columns, dp[0] = 1
 *
 * --- Processing Column 1 ---
 * Check extending from column 0:
 *   Row 0: 'b' > 'a' ✗ → Cannot keep columns {0, 1}
 * dp[1] = 1
 *
 * --- Processing Column 2 ---
 * Check extending from column 0:
 *   Row 0: 'b' <= 'b' ✓
 *   Row 1: 'b' > 'a' ✗ → Cannot keep columns {0, 2}
 * Check extending from column 1:
 *   Row 0: 'a' <= 'b' ✓
 *   Row 1: 'b' > 'a' ✗ → Cannot keep columns {1, 2}
 * dp[2] = 1
 *
 * --- Processing Column 3 ---
 * Check extending from column 0:
 *   Row 0: 'b' <= 'c' ✓
 *   Row 1: 'b' <= 'z' ✓ → CAN keep columns {0, 3}!
 *   dp[3] = max(1, dp[0] + 1) = 2
 * Check extending from column 1:
 *   Row 0: 'a' <= 'c' ✓
 *   Row 1: 'b' <= 'z' ✓ → CAN keep columns {1, 3}!
 *   dp[3] = max(2, dp[1] + 1) = 2
 * Check extending from column 2:
 *   Row 0: 'b' <= 'c' ✓
 *   Row 1: 'a' <= 'z' ✓ → CAN keep columns {2, 3}!
 *   dp[3] = max(2, dp[2] + 1) = 2
 * dp[3] = 2
 *
 * --- Processing Column 4 ---
 * Check extending from column 0:
 *   Row 0: 'b' > 'a' ✗
 * Check extending from column 1:
 *   Row 0: 'a' <= 'a' ✓
 *   Row 1: 'b' > 'b' ✗
 * Check extending from column 2:
 *   Row 0: 'b' > 'a' ✗
 * Check extending from column 3:
 *   Row 0: 'c' > 'a' ✗
 * dp[4] = 1
 *
 * Final DP: [1, 1, 1, 2, 1]
 * Longest valid subsequence = 2
 *
 * Minimum deletions = 5 - 2 = 3 ✓
 *
 * One valid solution: Keep columns {2, 3}, delete columns {0, 1, 4}
 * Result: ["bc", "az"] where each row is sorted ✓
 *
 * ===================================================================
 *
 * WHY THIS WORKS - The LIS Connection:
 *
 * 1. SUBSEQUENCE NOT SUBSTRING: We can keep any subset of columns in order,
 *    not just consecutive ones. This is exactly like LIS problem.
 *
 * 2. VALIDITY CONDITION: Instead of nums[i] <= nums[j] in classic LIS,
 *    here we need strs[row][i] <= strs[row][j] for ALL rows simultaneously.
 *
 * 3. OPTIMALITY: Greedy approach works because:
 *    - If we can extend a subsequence, we should (maximizes kept columns)
 *    - DP ensures we find the globally longest valid subsequence
 *
 * 4. DIFFERENCE FROM PROBLEM 955:
 *    - Problem 955: Rows must be sorted relative to EACH OTHER
 *    - This problem: Each row must be sorted WITHIN ITSELF
 *    - Completely different constraints, different approaches!
 */
int main()
{
    return 0;
}