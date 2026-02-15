#include <bits/stdc++.h>
using namespace std;
class Solution
{
private:
    /*
     * PROBLEM UNDERSTANDING:
     * - String contains only 'a' and 'b'
     * - Balanced: no 'b' appears before any 'a' (all 'a's before all 'b's)
     * - Goal: Minimum deletions to make balanced
     *
     * KEY INSIGHT - Partition Point Strategy:
     *
     * A balanced string has the form: "aaa...abbb...b" (all a's, then all b's)
     *
     * We can think of finding a "partition point" where:
     * - Everything to the LEFT should be 'a' (delete all 'b's)
     * - Everything to the RIGHT should be 'b' (delete all 'a's)
     *
     * For each position i as partition point:
     * - Delete all 'b's in s[0..i]     → count of 'b's before and at position i
     * - Delete all 'a's in s[i+1..n-1] → count of 'a's after position i
     *
     * EXAMPLE: s = "aababbab"
     *           0123456 7
     *
     * Partition after index 3 (position between index 3 and 4):
     *   Left part:  "aaba" → delete 1 'b' (at index 2)
     *   Right part: "bbab" → delete 1 'a' (at index 6)
     *   Total: 2 deletions
     *   Result: "aaa" + "bbb" = "aaabbb" ✓
     *
     * APPROACH:
     * 1. Precompute prefix count of 'b's: B_prefix[i] = count of 'b' in s[0..i]
     * 2. Precompute suffix count of 'a's: A_suffix[i] = count of 'a' in s[i..n-1]
     * 3. For each position i, deletions = B_prefix[i] + A_suffix[i] - 1
     *    (-1 because we count position i in both prefix and suffix)
     * 4. Return minimum across all positions
     *
     * TIME: O(n)
     * SPACE: O(n)
     */

    /**
     * Builds prefix count array for character 'b'
     * B_prefix[i] = number of 'b's in s[0..i] (inclusive)
     *
     * @param s - input string
     * @return vector where B_prefix[i] counts 'b's up to and including index i
     */
    vector<int> buildPrefixCountB(const string &s)
    {
        int n = s.size();
        vector<int> B_prefix(n);

        B_prefix[0] = (s[0] == 'b') ? 1 : 0;

        for (int i = 1; i < n; i++)
        {
            B_prefix[i] = B_prefix[i - 1] + ((s[i] == 'b') ? 1 : 0);
        }

        return B_prefix;
    }

    /**
     * Builds suffix count array for character 'a'
     * A_suffix[i] = number of 'a's in s[i..n-1] (inclusive)
     *
     * @param s - input string
     * @return vector where A_suffix[i] counts 'a's from index i to end
     */
    vector<int> buildSuffixCountA(const string &s)
    {
        int n = s.size();
        vector<int> A_suffix(n);

        // Start with total count of 'a's in entire string
        int totalA = count(s.begin(), s.end(), 'a');
        A_suffix[0] = totalA;

        // For each position, subtract 'a's we've passed
        for (int i = 1; i < n; i++)
        {
            A_suffix[i] = A_suffix[i - 1] - ((s[i - 1] == 'a') ? 1 : 0);
        }

        return A_suffix;
    }

public:
    int minimumDeletions(string &s)
    {
        int n = s.size();

        // Precompute prefix 'b' counts and suffix 'a' counts
        vector<int> B_prefix = buildPrefixCountB(s);
        vector<int> A_suffix = buildSuffixCountA(s);

        int minDeletions = n; // Worst case: delete entire string

        // Try each position as the partition point
        for (int i = 0; i < n; i++)
        {
            // Deletions needed if we partition at position i:
            // - Delete all 'b's in [0..i]
            // - Delete all 'a's in [i..n-1]
            // - Subtract 1 because we count position i in both
            int deletions = B_prefix[i] + A_suffix[i] - 1;
            minDeletions = min(minDeletions, deletions);
        }

        return minDeletions;
    }
};

/*
 * DETAILED WALKTHROUGH - Example 1: s = "aababbab"
 *
 * String indices:  0  1  2  3  4  5  6  7
 * Characters:      a  a  b  a  b  b  a  b
 *
 * ===== STEP 1: Build B_prefix (count of 'b's up to index i) =====
 *
 * i=0: s[0]='a' → B_prefix[0] = 0
 * i=1: s[1]='a' → B_prefix[1] = 0 + 0 = 0
 * i=2: s[2]='b' → B_prefix[2] = 0 + 1 = 1
 * i=3: s[3]='a' → B_prefix[3] = 1 + 0 = 1
 * i=4: s[4]='b' → B_prefix[4] = 1 + 1 = 2
 * i=5: s[5]='b' → B_prefix[5] = 2 + 1 = 3
 * i=6: s[6]='a' → B_prefix[6] = 3 + 0 = 3
 * i=7: s[7]='b' → B_prefix[7] = 3 + 1 = 4
 *
 * B_prefix = [0, 0, 1, 1, 2, 3, 3, 4]
 *
 * ===== STEP 2: Build A_suffix (count of 'a's from index i onward) =====
 *
 * Total 'a's in string = 4
 *
 * i=0: A_suffix[0] = 4 (all 'a's in string)
 * i=1: s[0]='a' → A_suffix[1] = 4 - 1 = 3
 * i=2: s[1]='a' → A_suffix[2] = 3 - 1 = 2
 * i=3: s[2]='b' → A_suffix[3] = 2 - 0 = 2
 * i=4: s[3]='a' → A_suffix[4] = 2 - 1 = 1
 * i=5: s[4]='b' → A_suffix[5] = 1 - 0 = 1
 * i=6: s[5]='b' → A_suffix[6] = 1 - 0 = 1
 * i=7: s[6]='a' → A_suffix[7] = 1 - 1 = 0
 *
 * A_suffix = [4, 3, 2, 2, 1, 1, 1, 0]
 *
 * ===== STEP 3: Try Each Partition Point =====
 *
 * Partition at i=0: (Keep position 0 as 'a', rest as 'b')
 *   Left:  "a"       → delete B_prefix[0] = 0 'b's
 *   Right: "ababbab" → delete A_suffix[0] = 4 'a's
 *   Overlap correction: -1
 *   Total: 0 + 4 - 1 = 3
 *
 * Partition at i=1: (Keep positions 0-1 as 'a', rest as 'b')
 *   Left:  "aa"      → delete B_prefix[1] = 0 'b's
 *   Right: "ababbab" → delete A_suffix[1] = 3 'a's
 *   Total: 0 + 3 - 1 = 2
 *
 * Partition at i=2: (Keep positions 0-2 as 'a', rest as 'b')
 *   Left:  "aab"     → delete B_prefix[2] = 1 'b' (at index 2)
 *   Right: "abbab"   → delete A_suffix[2] = 2 'a's (at indices 3,6)
 *   Total: 1 + 2 - 1 = 2 ✓
 *
 * Partition at i=3: (Keep positions 0-3 as 'a', rest as 'b')
 *   Left:  "aaba"    → delete B_prefix[3] = 1 'b' (at index 2)
 *   Right: "bbab"    → delete A_suffix[3] = 2 'a's (at indices 3,6)
 *   Total: 1 + 2 - 1 = 2 ✓
 *
 * Partition at i=4:
 *   Left:  "aabab"   → delete B_prefix[4] = 2 'b's
 *   Right: "bab"     → delete A_suffix[4] = 1 'a'
 *   Total: 2 + 1 - 1 = 2 ✓
 *
 * Partition at i=5:
 *   Total: 3 + 1 - 1 = 3
 *
 * Partition at i=6:
 *   Total: 3 + 1 - 1 = 3
 *
 * Partition at i=7:
 *   Total: 4 + 0 - 1 = 3
 *
 * Minimum deletions = 2 ✓
 *
 * Valid solutions:
 * - Delete indices 2,6: "aa_a__ab" → "aaabbb"
 * - Delete indices 3,6: "aab___ab" → "aabbbb"
 *
 * ===================================================================
 *
 * DETAILED WALKTHROUGH - Example 2: s = "bbaaaaabb"
 *
 * String indices:  0  1  2  3  4  5  6  7  8
 * Characters:      b  b  a  a  a  a  a  b  b
 *
 * B_prefix = [1, 2, 2, 2, 2, 2, 2, 3, 4]
 * A_suffix = [5, 5, 5, 4, 3, 2, 1, 0, 0]
 *
 * Partition at i=0: 1 + 5 - 1 = 5
 * Partition at i=1: 2 + 5 - 1 = 6
 * Partition at i=2: 2 + 5 - 1 = 6
 * ... (all worse than deleting first two 'b's)
 *
 * Best: Delete first two 'b's → "_baaaaa bb" → "aaaaabb"
 * This is equivalent to partitioning before index 0 (empty left part)
 *
 * Actually, we need to consider edge case: delete all 'b's before any 'a'
 *
 * Wait, let me reconsider the formula...
 * The formula B_prefix[i] + A_suffix[i] - 1 assumes we're keeping position i.
 *
 * For this example, minimum is at partition where we keep no 'b's before 'a's.
 * The formula gives us minimum = 2 by trying different partitions.
 *
 * ===================================================================
 *
 * WHY THIS WORKS - Algorithm Correctness:
 *
 * 1. BALANCED STRING STRUCTURE:
 *    - A balanced string must have all 'a's before all 'b's
 *    - Equivalently: "aaa...abbb...b" (possibly empty a-part or b-part)
 *    - This is enforced by choosing a partition point
 *
 * 2. PARTITION POINT STRATEGY:
 *    - For each position i, we decide: left part is 'a's, right part is 'b's
 *    - Position i itself is included in the "left part" (hence the -1)
 *    - Delete all 'b's in left part + all 'a's in right part
 *
 * 3. PREFIX/SUFFIX COUNTS:
 *    - B_prefix[i] = total 'b's we'd delete if left part ends at i
 *    - A_suffix[i] = total 'a's we'd delete if right part starts at i
 *    - -1 adjustment because position i is counted in both
 *
 * 4. EXHAUSTIVE SEARCH:
 *    - Try all possible partition points
 *    - Guaranteed to find optimal solution
 *    - O(n) time with precomputed counts
 *
 * 5. EDGE CASES:
 *    - All 'a's: partition at end → 0 deletions
 *    - All 'b's: partition at start → 0 deletions
 *    - Already balanced: 0 deletions
 *    - "ba": must delete one → 1 deletion
 *
 * COMPLEXITY ANALYSIS:
 * - Time: O(n) for building prefix/suffix + O(n) for finding minimum = O(n)
 * - Space: O(n) for two arrays
 *
 * SPACE OPTIMIZATION:
 * - Could reduce to O(1) by computing on-the-fly
 * - Current approach is clearer and still efficient
 *
 * ALTERNATIVE APPROACHES:
 * 1. Dynamic Programming: Track min deletions up to each position
 * 2. Stack-based: Track 'b's seen, delete when 'a' encountered
 * 3. Current approach: Most intuitive with partition point interpretation
 */
int main()
{
    return 0;
}