#include <bits/stdc++.h>
using namespace std;

/*
You are given an array of n strings strs, all of the same length.

We may choose any deletion indices, and we delete all the characters in those indices for each string.

For example, if we have strs = ["abcdef","uvwxyz"] and deletion indices {0, 2, 3}, then the final array after deletions is ["bef", "vyz"].

Suppose we chose a set of deletion indices answer such that after deletions, the final array has its elements in lexicographic order (i.e., strs[0] <= strs[1] <= strs[2] <= ... <= strs[n - 1]). Return the minimum possible value of answer.length.

*/
class Solution
{
private:
    /*
     * PROBLEM UNDERSTANDING:
     * - Given array of n strings, all same length
     * - Can delete columns (same index from all strings)
     * - Goal: Minimum deletions so final strings are in lexicographic order
     *
     * KEY INSIGHT:
     * - Process columns left to right (most significant to least)
     * - Track which adjacent pairs are "already sorted" (determined by previous columns)
     * - For each column:
     *   1. If it violates order for any "unsorted" pair → DELETE it
     *   2. If it determines order for a pair (char1 < char2) → mark pair as "sorted"
     *
     * EXAMPLE: strs = ["ca", "bb", "ac"]
     *
     * Column 0: ['c', 'b', 'a']
     * - Pair (0,1): 'c' > 'b' → VIOLATION → delete column 0
     * - deletions = 1
     *
     * Column 1: ['a', 'b', 'c']
     * - Pair (0,1): 'a' < 'b' → determines order, mark sorted
     * - Pair (1,2): 'b' < 'c' → determines order, mark sorted
     * - No violations, keep column
     *
     * Result: ["a", "b", "c"] ✓ (lexicographically sorted)
     */

    /**
     * Checks if keeping current column would violate lexicographic ordering
     * Only checks pairs that haven't been determined sorted by previous columns
     *
     * @param strs - array of strings
     * @param columnIndex - current column being examined
     * @param pairAlreadySorted - tracks which adjacent pairs are already in order
     * @return true if column should be deleted (has violation), false otherwise
     */
    bool columnHasViolation(const vector<string> &strs,
                            int columnIndex,
                            const vector<bool> &pairAlreadySorted)
    {
        int numStrings = strs.size();

        for (int i = 0; i < numStrings - 1; i++)
        {
            // Skip pairs already determined to be sorted by earlier columns
            if (pairAlreadySorted[i])
            {
                continue;
            }

            char currentChar = strs[i][columnIndex];
            char nextChar = strs[i + 1][columnIndex];

            // If current string has larger char than next string → violation!
            // Example: if we have "ba" and "bb", and column shows 'a' > 'b'
            if (currentChar > nextChar)
            {
                return true; // Must delete this column
            }
        }

        return false; // No violations, safe to keep
    }

    /**
     * Updates which adjacent pairs are now definitively sorted
     * A pair is "sorted" when we find a column where str[i][col] < str[i+1][col]
     * Once sorted, we don't need to check that pair for future columns
     *
     * @param strs - array of strings
     * @param columnIndex - current column being examined
     * @param pairAlreadySorted - tracks which adjacent pairs are already in order (updated in-place)
     */
    void updateSortedPairs(const vector<string> &strs,
                           int columnIndex,
                           vector<bool> &pairAlreadySorted)
    {
        int numStrings = strs.size();

        for (int i = 0; i < numStrings - 1; i++)
        {
            char currentChar = strs[i][columnIndex];
            char nextChar = strs[i + 1][columnIndex];

            // If current char is strictly less than next char,
            // this pair is now definitively in correct order
            // Future columns can't change this relationship
            //
            // Example: "abc" vs "bcd"
            // - Column 0: 'a' < 'b' → pair is sorted forever!
            // - Doesn't matter what columns 1,2 contain
            if (currentChar < nextChar)
            {
                pairAlreadySorted[i] = true;
            }

            // Note: if currentChar == nextChar, we still need to check future columns
            // Example: "ab" vs "ac" at column 0 both have 'a', so column 1 matters
        }
    }

public:
    int minDeletionSize(vector<string> &strs)
    {
        // Edge case: single string is always sorted
        if (strs.size() <= 1)
        {
            return 0;
        }

        int numStrings = strs.size();
        int stringLength = strs[0].size();
        int deletionCount = 0;

        // Track which adjacent pairs (i, i+1) are already determined to be sorted
        // pairAlreadySorted[i] = true means strs[i] < strs[i+1] is guaranteed
        vector<bool> pairAlreadySorted(numStrings - 1, false);

        // Process each column from left to right (most significant to least)
        for (int col = 0; col < stringLength; col++)
        {
            // Check if this column creates any violations
            if (columnHasViolation(strs, col, pairAlreadySorted))
            {
                // This column breaks lexicographic order → delete it
                deletionCount++;
                // Don't update sorted pairs since we're deleting this column
                continue;
            }

            // Column is safe to keep, update which pairs are now definitively sorted
            updateSortedPairs(strs, col, pairAlreadySorted);
        }

        return deletionCount;
    }
};

/*
 * DETAILED WALKTHROUGH - Example 1: strs = ["ca", "bb", "ac"]
 *
 * Initial state:
 * - Pairs to check: (0,1) and (1,2)
 * - pairAlreadySorted = [false, false]
 *
 * ===== COLUMN 0: ['c', 'b', 'a'] =====
 * Check violations:
 *   - Pair (0,1): pairAlreadySorted[0]=false, check needed
 *     'c' > 'b' → VIOLATION! ❌
 * Action: Delete column 0
 * Result: deletionCount = 1
 *
 * ===== COLUMN 1: ['a', 'b', 'c'] =====
 * Check violations:
 *   - Pair (0,1): pairAlreadySorted[0]=false, check needed
 *     'a' < 'b' → OK ✓
 *   - Pair (1,2): pairAlreadySorted[1]=false, check needed
 *     'b' < 'c' → OK ✓
 * Action: Keep column 1
 *
 * Update sorted pairs:
 *   - Pair (0,1): 'a' < 'b' → pairAlreadySorted[0] = true
 *   - Pair (1,2): 'b' < 'c' → pairAlreadySorted[1] = true
 *
 * Final result: deletionCount = 1
 * Final strings: ["a", "b", "c"] ✓
 *
 * ===================================================================
 *
 * WHY THIS WORKS - The Greedy Strategy:
 *
 * 1. We process columns left-to-right because leftmost columns are most
 *    significant in lexicographic comparison ("abc" < "b..." regardless of rest)
 *
 * 2. Once a pair is "sorted" by a column (str[i][col] < str[i+1][col]),
 *    it stays sorted forever - later columns don't matter for that pair
 *    Example: "a..." will always be < "b..." no matter what comes after
 *
 * 3. We only delete when necessary - if a column would break ordering for
 *    any undetermined pair, we must remove it
 *
 * 4. Greedy choice is optimal: keeping columns when possible minimizes deletions
 */
int main()
{
    return 0;
}