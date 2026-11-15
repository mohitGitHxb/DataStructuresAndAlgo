#include <bits/stdc++.h>
using namespace std;
class Solution
{
private:
    /*
     * PROBLEM UNDERSTANDING:
     * - str1 contains 'T' and 'F' (length n)
     * - str2 is a pattern string (length m)
     * - Generate word of length n+m-1 where:
     *   - 'T' at position i → word[i..i+m-1] MUST equal str2
     *   - 'F' at position i → word[i..i+m-1] MUST NOT equal str2
     * - Return lexicographically smallest valid word, or "" if impossible
     *
     * KEY INSIGHT - Two-Pass Greedy Construction:
     *
     * PHASE 1: Process 'T' constraints (forced equality)
     * - For each 'T' at position i, force word[i..i+m-1] = str2
     * - If conflict detected (different character already set) → impossible
     * - Mark these positions as "fixed" (cannot be changed)
     *
     * PHASE 2: Fill remaining with lexicographically smallest ('a')
     * - Unfilled positions get 'a' and marked as "changeable"
     *
     * PHASE 3: Process 'F' constraints (forced inequality)
     * - For each 'F' at position i:
     *   - If word[i..i+m-1] == str2, must make it different
     *   - Change the LAST changeable character to 'b' (lexicographically smallest change)
     *   - If no changeable character exists → impossible
     *
     * EXAMPLE: str1 = "TFTF", str2 = "ab"
     *
     * Length = 4 + 2 - 1 = 5
     *
     * Phase 1 (Process 'T'):
     *   i=0: str1[0]='T' → word[0..1] = "ab"
     *   i=2: str1[2]='T' → word[2..3] = "ab"
     *   word = "ab?ab" (? = unfilled)
     *   After overlap resolution: "abab?"
     *
     * Phase 2 (Fill with 'a'):
     *   word = "ababa"
     *   changeable = [false, false, false, false, true]
     *
     * Phase 3 (Process 'F'):
     *   i=1: str1[1]='F', word[1..2] = "ba" ≠ "ab" ✓ (already different)
     *   i=3: str1[3]='F', word[3..4] = "ba" ≠ "ab" ✓ (already different)
     *
     * Result: "ababa" ✓
     *
     * TIME: O(n × m)
     * SPACE: O(n + m)
     */

    /**
     * Checks if a substring of word matches str2
     *
     * @param word - the generated word
     * @param str2 - the pattern to match
     * @param startIndex - starting position in word
     * @return true if word[startIndex..startIndex+m-1] == str2
     */
    bool substringMatches(const string &word, const string &str2, int startIndex)
    {
        for (int j = 0; j < str2.length(); j++)
        {
            if (word[startIndex + j] != str2[j])
            {
                return false;
            }
        }
        return true;
    }

public:
    string generateString(string str1, string str2)
    {
        int n = str1.length();
        int m = str2.length();
        int wordLength = n + m - 1;

        // Initialize word with placeholder characters
        string word(wordLength, '.');

        // Track which positions can be changed (not forced by 'T' constraints)
        vector<bool> isChangeable(wordLength, false);

        // ===== PHASE 1: Process 'T' Constraints (Forced Equality) =====
        // For each 'T', the substring MUST equal str2
        for (int i = 0; i < n; i++)
        {
            if (str1[i] == 'T')
            {
                // Force word[i..i+m-1] = str2
                for (int j = 0; j < m; j++)
                {
                    int pos = i + j;

                    // Check for conflict: different character already set
                    if (word[pos] != '.' && word[pos] != str2[j])
                    {
                        return ""; // Impossible: conflicting 'T' constraints
                    }

                    word[pos] = str2[j];
                    // These positions are fixed (cannot be changed later)
                }
            }
        }

        // ===== PHASE 2: Fill Remaining with Lexicographically Smallest =====
        // Unfilled positions get 'a' (smallest letter) and marked as changeable
        for (int i = 0; i < wordLength; i++)
        {
            if (word[i] == '.')
            {
                word[i] = 'a';
                isChangeable[i] = true;
            }
        }

        // ===== PHASE 3: Process 'F' Constraints (Forced Inequality) =====
        // For each 'F', the substring MUST NOT equal str2
        for (int i = 0; i < n; i++)
        {
            if (str1[i] == 'F')
            {
                // Check if current substring equals str2
                if (substringMatches(word, str2, i))
                {
                    // Need to make it different
                    // Change the LAST changeable character to 'b'
                    // (rightmost change keeps result lexicographically smallest)
                    bool madeChange = false;

                    for (int j = i + m - 1; j >= i; j--)
                    {
                        if (isChangeable[j])
                        {
                            word[j] = 'b'; // Change 'a' to 'b'
                            madeChange = true;
                            break;
                        }
                    }

                    // If no changeable position found, constraint cannot be satisfied
                    if (!madeChange)
                    {
                        return ""; // Impossible: 'F' constraint cannot be satisfied
                    }
                }
            }
        }

        return word;
    }
};

/*
 * DETAILED WALKTHROUGH - Example 1: str1 = "TFTF", str2 = "ab"
 *
 * n = 4, m = 2, wordLength = 5
 *
 * ===== PHASE 1: Process 'T' Constraints =====
 *
 * Initial word: "....."
 *
 * i=0: str1[0] = 'T'
 *   Force word[0..1] = "ab"
 *   word = "ab..."
 *
 * i=1: str1[1] = 'F' → skip
 *
 * i=2: str1[2] = 'T'
 *   Force word[2..3] = "ab"
 *   word[2] = '.' → set to 'a'
 *   word[3] = '.' → set to 'b'
 *   word = "abab."
 *
 * i=3: str1[3] = 'F' → skip
 *
 * After Phase 1: word = "abab."
 *
 * ===== PHASE 2: Fill Remaining with 'a' =====
 *
 * word[0] = 'a' (fixed)
 * word[1] = 'b' (fixed)
 * word[2] = 'a' (fixed)
 * word[3] = 'b' (fixed)
 * word[4] = '.' → set to 'a', isChangeable[4] = true
 *
 * After Phase 2: word = "ababa"
 * isChangeable = [false, false, false, false, true]
 *
 * ===== PHASE 3: Process 'F' Constraints =====
 *
 * i=0: str1[0] = 'T' → skip
 *
 * i=1: str1[1] = 'F'
 *   Check if word[1..2] = "ba" matches str2 = "ab"
 *   "ba" ≠ "ab" → already different, no change needed ✓
 *
 * i=2: str1[2] = 'T' → skip
 *
 * i=3: str1[3] = 'F'
 *   Check if word[3..4] = "ba" matches str2 = "ab"
 *   "ba" ≠ "ab" → already different, no change needed ✓
 *
 * Final word: "ababa" ✓
 *
 * ===================================================================
 *
 * DETAILED WALKTHROUGH - Example 2: str1 = "TFTF", str2 = "abc"
 *
 * n = 4, m = 3, wordLength = 6
 *
 * ===== PHASE 1: Process 'T' Constraints =====
 *
 * i=0: str1[0] = 'T'
 *   Force word[0..2] = "abc"
 *   word = "abc..."
 *
 * i=2: str1[2] = 'T'
 *   Force word[2..4] = "abc"
 *   word[2] = 'c' but need to set to 'a' → CONFLICT!
 *   Return "" ✓
 *
 * ===================================================================
 *
 * DETAILED WALKTHROUGH - Example 3: str1 = "F", str2 = "d"
 *
 * n = 1, m = 1, wordLength = 1
 *
 * ===== PHASE 1: No 'T' constraints =====
 * word = "."
 *
 * ===== PHASE 2: Fill with 'a' =====
 * word = "a"
 * isChangeable = [true]
 *
 * ===== PHASE 3: Process 'F' =====
 * i=0: str1[0] = 'F'
 *   word[0] = "a" vs str2 = "d"
 *   "a" ≠ "d" → already different ✓
 *
 * Final word: "a" ✓
 *
 * ===================================================================
 *
 * WHY THIS WORKS - Algorithm Correctness:
 *
 * 1. THREE-PHASE APPROACH:
 *    - Phase 1: Handle hard constraints ('T') first
 *    - Phase 2: Fill gaps greedily with smallest character
 *    - Phase 3: Adjust for 'F' constraints minimally
 *
 * 2. CONFLICT DETECTION (Phase 1):
 *    - If two 'T' constraints require different characters at same position
 *    - Example: str1="TT", str2="ab" → positions 1 needs both 'b' and 'a'
 *    - Detected when word[pos] already set to different character
 *
 * 3. LEXICOGRAPHICALLY SMALLEST STRATEGY:
 *    - Fill with 'a' (smallest letter) wherever possible
 *    - For 'F' constraints: change rightmost changeable position to 'b'
 *    - Rightmost change minimizes lexicographic impact
 *
 * 4. CHANGEABILITY TRACKING:
 *    - Positions set by 'T' constraints are fixed
 *    - Only positions filled with 'a' in Phase 2 can be changed
 *    - Prevents breaking 'T' constraints when satisfying 'F' constraints
 *
 * 5. IMPOSSIBILITY DETECTION:
 *    - Conflicting 'T' constraints → Phase 1
 *    - 'F' constraint with no changeable positions → Phase 3
 *    - Both cases return empty string
 *
 * COMPLEXITY ANALYSIS:
 * - Phase 1: O(n × m) - process each 'T', copy m characters
 * - Phase 2: O(n + m) - fill unfilled positions
 * - Phase 3: O(n × m) - process each 'F', check m characters
 * - Total: O(n × m)
 * - Space: O(n + m) for word and isChangeable arrays
 *
 * EDGE CASES:
 * - All 'T': word completely determined
 * - All 'F': fill with 'a', change last to 'b' for each overlapping 'F'
 * - str2 length 1: simpler but same logic applies
 * - Overlapping constraints: handled by conflict detection
 */
int main()
{
    return 0;
}