#include <bits/stdc++.h>
using namespace std;
class Solution
{
private:
    /*
     * PROBLEM UNDERSTANDING:
     * - Given two strings s1 and s2
     * - Can delete characters from either string
     * - Goal: Make strings equal with minimum ASCII sum of deleted characters
     *
     * KEY INSIGHT - Maximize What We Keep (LCS with ASCII Values):
     *
     * Instead of minimizing deletions, we MAXIMIZE what we keep!
     *
     * Observation:
     * - Total ASCII sum = sum(s1) + sum(s2)
     * - Characters we keep appear in BOTH strings (common subsequence)
     * - Deletion cost = Total - 2 × (ASCII sum of common subsequence)
     *
     * Therefore: Minimize deletions ≡ Maximize common subsequence value
     *
     * This transforms the problem into:
     * "Find the common subsequence with MAXIMUM ASCII sum"
     *
     * APPROACH - Modified Longest Common Subsequence (LCS):
     *
     * Classic LCS finds longest subsequence, we find HIGHEST VALUE subsequence.
     *
     * DP State: dp[i][j] = max ASCII sum of common subsequence using:
     *   - First i characters of s1 (s1[0..i-1])
     *   - First j characters of s2 (s2[0..j-1])
     *
     * Transitions:
     * 1. If s1[i] == s2[j]: Include this character
     *    dp[i][j] = ASCII(s1[i]) + dp[i-1][j-1]
     *
     * 2. If s1[i] ≠ s2[j]: Skip one character from either string
     *    dp[i][j] = max(dp[i-1][j], dp[i][j-1])
     *
     * EXAMPLE: s1 = "sea", s2 = "eat"
     *
     * Common subsequence "ea" has ASCII sum: 101 + 97 = 198
     * sum(s1) = 115+101+97 = 313
     * sum(s2) = 101+97+116 = 314
     * Deletion cost = 313 + 314 - 2×198 = 627 - 396 = 231 ✓
     *
     * TIME: O(m × n) where m = s1.length, n = s2.length
     * SPACE: O(m × n) for DP table
     */

    // DP table: memoization for maximum ASCII sum of common subsequence
    int dp[1001][1001];

    /**
     * Computes the maximum ASCII sum of common subsequence
     * Uses top-down DP (memoization)
     *
     * @param i - current index in s1 (0-indexed, processing from end)
     * @param j - current index in s2 (0-indexed, processing from end)
     * @param s1 - first string
     * @param s2 - second string
     * @return maximum ASCII sum of common subsequence for s1[0..i] and s2[0..j]
     */
    int findMaxCommonSubsequenceValue(int i, int j, const string &s1, const string &s2)
    {
        // Base case: If either string is exhausted, no more characters to match
        if (i < 0 || j < 0)
        {
            return 0;
        }

        // Return memoized result if already computed
        if (dp[i][j] != -1)
        {
            return dp[i][j];
        }

        // Case 1: Characters match - include in common subsequence
        if (s1[i] == s2[j])
        {
            // Add ASCII value of matched character + best solution for remaining substrings
            int charValue = static_cast<int>(s1[i]);
            return dp[i][j] = charValue + findMaxCommonSubsequenceValue(i - 1, j - 1, s1, s2);
        }

        // Case 2: Characters don't match - try skipping from either string
        // Take the maximum of:
        //   - Skip current character from s1 (move i back)
        //   - Skip current character from s2 (move j back)
        int skipFromS1 = findMaxCommonSubsequenceValue(i - 1, j, s1, s2);
        int skipFromS2 = findMaxCommonSubsequenceValue(i, j - 1, s1, s2);

        return dp[i][j] = max(skipFromS1, skipFromS2);
    }

    /**
     * Calculates total ASCII sum of all characters in a string
     *
     * @param s - input string
     * @return sum of ASCII values of all characters
     */
    int calculateAsciiSum(const string &s)
    {
        return accumulate(s.begin(), s.end(), 0,
                          [](int sum, char c)
                          { return sum + static_cast<int>(c); });
    }

public:
    int minimumDeleteSum(string s1, string s2)
    {
        // Calculate total ASCII sums
        int totalS1 = calculateAsciiSum(s1);
        int totalS2 = calculateAsciiSum(s2);

        // Initialize DP table with -1 (uncomputed)
        memset(dp, -1, sizeof(dp));

        // Find maximum ASCII sum of common subsequence
        int maxCommonValue = findMaxCommonSubsequenceValue(s1.length() - 1,
                                                           s2.length() - 1,
                                                           s1, s2);

        // Minimum deletion sum = Total sum - 2 × (sum we keep)
        // We subtract twice because common characters appear in BOTH strings
        return totalS1 + totalS2 - 2 * maxCommonValue;
    }
};

/*
 * DETAILED WALKTHROUGH - Example 1: s1 = "sea", s2 = "eat"
 *
 * ===== STEP 1: Calculate Total Sums =====
 * s1 = "sea": 115('s') + 101('e') + 97('a') = 313
 * s2 = "eat": 101('e') + 97('a') + 116('t') = 314
 *
 * ===== STEP 2: Find Max Common Subsequence Value =====
 *
 * DP Table Construction (showing key states):
 *
 * Call: findMaxCommonSubsequenceValue(2, 2, "sea", "eat")
 * Compare s1[2]='a' vs s2[2]='t' → Not equal
 *
 * Branch 1: Skip 'a' from s1
 *   Call: findMaxCommonSubsequenceValue(1, 2, "sea", "eat")
 *   Compare s1[1]='e' vs s2[2]='t' → Not equal
 *
 *   Branch 1.1: Skip 'e' from s1
 *     Call: findMaxCommonSubsequenceValue(0, 2, "sea", "eat")
 *     Compare s1[0]='s' vs s2[2]='t' → Not equal
 *     Returns: max(0, 0) = 0
 *
 *   Branch 1.2: Skip 't' from s2
 *     Call: findMaxCommonSubsequenceValue(1, 1, "sea", "eat")
 *     Compare s1[1]='e' vs s2[1]='a' → Not equal
 *
 *     Branch 1.2.1: Skip 'e'
 *       Call: findMaxCommonSubsequenceValue(0, 1, "sea", "eat")
 *       Compare s1[0]='s' vs s2[1]='a' → Not equal
 *       Returns: 0
 *
 *     Branch 1.2.2: Skip 'a'
 *       Call: findMaxCommonSubsequenceValue(1, 0, "sea", "eat")
 *       Compare s1[1]='e' vs s2[0]='e' → MATCH! ✓
 *       Return: 101 + findMaxCommonSubsequenceValue(0, -1) = 101 + 0 = 101
 *
 *     Returns: max(0, 101) = 101
 *
 *   Returns: max(0, 101) = 101
 *
 * Branch 2: Skip 't' from s2
 *   Call: findMaxCommonSubsequenceValue(2, 1, "sea", "eat")
 *   Compare s1[2]='a' vs s2[1]='a' → MATCH! ✓
 *
 *   Call: findMaxCommonSubsequenceValue(1, 0, "sea", "eat")
 *   Compare s1[1]='e' vs s2[0]='e' → MATCH! ✓
 *
 *   Return: 101 + findMaxCommonSubsequenceValue(0, -1) = 101 + 0 = 101
 *
 *   Return: 97 + 101 = 198
 *
 * Final: max(101, 198) = 198
 *
 * Common subsequence found: "ea" with ASCII sum 198
 *
 * ===== STEP 3: Calculate Minimum Deletion Sum =====
 * totalS1 + totalS2 - 2 × maxCommonValue
 * = 313 + 314 - 2 × 198
 * = 627 - 396
 * = 231 ✓
 *
 * Verification:
 * - Delete 's' from "sea": 115
 * - Delete 't' from "eat": 116
 * - Total: 231 ✓
 * - Both strings become "ea"
 *
 * ===================================================================
 *
 * DETAILED WALKTHROUGH - Example 2: s1 = "delete", s2 = "leet"
 *
 * ===== Character ASCII Values =====
 * d=100, e=101, l=108, t=116
 *
 * ===== Total Sums =====
 * s1 = "delete": 100+101+108+101+116+101 = 627
 * s2 = "leet": 108+101+101+116 = 426
 *
 * ===== Finding Max Common Subsequence =====
 * Possible common subsequences:
 * - "let": 108+101+116 = 325
 * - "eet": 101+101+116 = 318
 * - "lee": 108+101+101 = 310
 * - "et": 101+116 = 217
 *
 * Maximum: "let" with sum 325
 *
 * ===== Deletion Sum =====
 * 627 + 426 - 2×325 = 1053 - 650 = 403 ✓
 *
 * Verification:
 * From "delete" to "let": delete 'd'(100) + 'e'(101) + 'e'(101) = 302
 * From "leet" to "let": delete 'e'(101) = 101
 * Total: 302 + 101 = 403 ✓
 *
 * ===================================================================
 *
 * WHY THIS WORKS - Algorithm Correctness:
 *
 * 1. PROBLEM TRANSFORMATION:
 *    - Original: Minimize deletion cost
 *    - Transformed: Maximize value of what we keep
 *    - Equivalence: deletion_cost = total - 2×kept
 *
 * 2. COMMON SUBSEQUENCE PROPERTY:
 *    - Characters we keep must appear in BOTH strings
 *    - They contribute to BOTH sums before deletion
 *    - That's why we subtract 2× (counted twice)
 *
 * 3. DP OPTIMALITY:
 *    - At each position, we try all possibilities:
 *      a) Include current character (if matched)
 *      b) Skip from s1
 *      c) Skip from s2
 *    - Take maximum value → ensures global optimum
 *
 * 4. MEMOIZATION:
 *    - Same subproblem (i, j) always gives same answer
 *    - Prevents redundant calculations
 *    - Converts O(2^n) to O(m×n)
 *
 * 5. BASE CASE:
 *    - When either string is exhausted (i<0 or j<0)
 *    - No more characters to match → return 0
 *
 * COMPLEXITY ANALYSIS:
 * - Time: O(m × n) - fill DP table of size m×n
 * - Space: O(m × n) - DP table storage
 *   + O(m + n) - recursion stack depth
 *
 * OPTIMIZATION OPPORTUNITY:
 * - Could use bottom-up DP with O(min(m,n)) space
 * - Current solution is clear and efficient enough
 */
int main()
{
    return 0;
}