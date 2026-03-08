#include <bits/stdc++.h>
using namespace std;
class Solution
{
private:
    /*
     * PROBLEM UNDERSTANDING:
     * - Given binary string s
     * - Operation 1: Rotate left (move first char to end)
     * - Operation 2: Flip any bit (0→1 or 1→0)
     * - Goal: Minimum flips to make alternating (after any rotations)
     *
     * KEY INSIGHT - Sliding Window on Doubled String:
     *
     * OBSERVATION 1: Rotation as Substring
     * - Any rotation of s can be viewed as a substring of s+s
     * - Example: s = "abc" → s+s = "abcabc"
     *   - Rotation 0: "abc" (substring [0..2])
     *   - Rotation 1: "bca" (substring [1..3])
     *   - Rotation 2: "cab" (substring [2..4])
     *
     * OBSERVATION 2: Two Alternating Patterns
     * - Pattern 1: "010101..." (starts with '0')
     * - Pattern 2: "101010..." (starts with '1')
     * - Must check both and take minimum
     *
     * APPROACH:
     * 1. Double the string: s+s
     * 2. Use sliding window of size n
     * 3. For each window position, count mismatches with both patterns
     * 4. Return minimum across all rotations and both patterns
     *
     * EXAMPLE: s = "111000"
     *
     * Doubled: "111000111000"
     *
     * Window at position 0-5: "111000"
     *   Pattern 1 "010101": mismatches at positions 0,1,3,4 → 4 flips
     *   Pattern 2 "101010": mismatches at positions 2,5 → 2 flips ✓
     *
     * Window at position 1-6: "110001"
     *   Pattern 1 "010101": 3 flips
     *   Pattern 2 "101010": 3 flips
     *
     * Window at position 2-7: "100011"
     *   Pattern 1 "010101": 2 flips ✓
     *   Pattern 2 "101010": 4 flips
     *
     * Minimum = 2 ✓
     *
     * TIME: O(n) - single pass with sliding window
     * SPACE: O(n) - for doubled string
     */

    /**
     * Calculates mismatches between string and alternating pattern
     *
     * @param s - input string
     * @param startChar - starting character of alternating pattern ('0' or '1')
     * @return number of positions that don't match the pattern
     */
    int countMismatchesWithPattern(const string &s, char startChar)
    {
        int mismatches = 0;

        for (int i = 0; i < s.size(); i++)
        {
            // Expected character alternates based on position
            char expected = (i % 2 == 0) ? startChar : (startChar == '0' ? '1' : '0');

            if (s[i] != expected)
            {
                mismatches++;
            }
        }

        return mismatches;
    }

public:
    int minFlips(string s)
    {
        int n = s.size();

        // Double the string to simulate all rotations
        string doubled = s + s;

        int minFlipsNeeded = INT_MAX;

        // Track mismatches with both patterns using sliding window
        int mismatchPattern1 = 0; // Pattern starting with '0': "010101..."
        int mismatchPattern2 = 0; // Pattern starting with '1': "101010..."

        // Slide window of size n across doubled string
        for (int i = 0; i < doubled.size(); i++)
        {
            // Expected characters at position i for both patterns
            char expectedPattern1 = (i % 2 == 0) ? '0' : '1';
            char expectedPattern2 = (i % 2 == 0) ? '1' : '0';

            // Add current character to window (increment mismatches if needed)
            if (doubled[i] != expectedPattern1)
            {
                mismatchPattern1++;
            }
            if (doubled[i] != expectedPattern2)
            {
                mismatchPattern2++;
            }

            // Remove character that's leaving the window
            if (i >= n)
            {
                int exitIndex = i - n;

                // Expected characters at exit position for both patterns
                char exitExpectedPattern1 = (exitIndex % 2 == 0) ? '0' : '1';
                char exitExpectedPattern2 = (exitIndex % 2 == 0) ? '1' : '0';

                // Remove from mismatch count if it was a mismatch
                if (doubled[exitIndex] != exitExpectedPattern1)
                {
                    mismatchPattern1--;
                }
                if (doubled[exitIndex] != exitExpectedPattern2)
                {
                    mismatchPattern2--;
                }
            }

            // Once we have a full window (size n), check this rotation
            if (i >= n - 1)
            {
                int flipsForThisRotation = min(mismatchPattern1, mismatchPattern2);
                minFlipsNeeded = min(minFlipsNeeded, flipsForThisRotation);
            }
        }

        return minFlipsNeeded;
    }
};

/*
 * DETAILED WALKTHROUGH - Example 1: s = "111000"
 *
 * Original string:  "111000"
 * Doubled string:   "111000111000"
 * Window size: n = 6
 *
 * We'll track two patterns:
 * Pattern 1 (starts with '0'): "010101"
 * Pattern 2 (starts with '1'): "101010"
 *
 * ===== Sliding Window Process =====
 *
 * --- Position i=0: Window = "1" ---
 * Expected Pattern 1[0] = '0', actual = '1' → mismatch1++
 * Expected Pattern 2[0] = '1', actual = '1' → match
 * mismatchPattern1 = 1, mismatchPattern2 = 0
 *
 * --- Position i=1: Window = "11" ---
 * Expected Pattern 1[1] = '1', actual = '1' → match
 * Expected Pattern 2[1] = '0', actual = '1' → mismatch2++
 * mismatchPattern1 = 1, mismatchPattern2 = 1
 *
 * --- Position i=2: Window = "111" ---
 * Expected Pattern 1[2] = '0', actual = '1' → mismatch1++
 * Expected Pattern 2[2] = '1', actual = '1' → match
 * mismatchPattern1 = 2, mismatchPattern2 = 1
 *
 * --- Position i=3: Window = "1110" ---
 * Expected Pattern 1[3] = '1', actual = '0' → mismatch1++
 * Expected Pattern 2[3] = '0', actual = '0' → match
 * mismatchPattern1 = 3, mismatchPattern2 = 1
 *
 * --- Position i=4: Window = "11100" ---
 * Expected Pattern 1[4] = '0', actual = '0' → match
 * Expected Pattern 2[4] = '1', actual = '0' → mismatch2++
 * mismatchPattern1 = 3, mismatchPattern2 = 2
 *
 * --- Position i=5: Window = "111000" (first complete window) ---
 * Expected Pattern 1[5] = '1', actual = '0' → mismatch1++
 * Expected Pattern 2[5] = '0', actual = '0' → match
 * mismatchPattern1 = 4, mismatchPattern2 = 2
 *
 * i >= n-1, so we have a complete rotation:
 * Rotation 0: "111000"
 *   vs Pattern 1 "010101": 4 mismatches
 *   vs Pattern 2 "101010": 2 mismatches
 * minFlipsNeeded = min(4, 2) = 2
 *
 * --- Position i=6: Window = "110001" (rotation 1) ---
 * Add doubled[6]='1':
 *   Expected Pattern 1[6] = '0', actual = '1' → mismatch1++
 *   Expected Pattern 2[6] = '1', actual = '1' → match
 * Remove doubled[0]='1':
 *   Expected Pattern 1[0] = '0', was '1' (mismatch) → mismatch1--
 *   Expected Pattern 2[0] = '1', was '1' (match) → no change
 * mismatchPattern1 = 4, mismatchPattern2 = 2
 *
 * Hmm, let me recalculate more carefully...
 *
 * Actually, the window "110001" should be checked against patterns
 * where position 0 of the window corresponds to pattern position 0.
 *
 * Let me restart with clearer tracking:
 *
 * Window "111000" (indices 0-5 of doubled):
 *   Position 0: '1' vs pattern1[0]='0' ✗, vs pattern2[0]='1' ✓
 *   Position 1: '1' vs pattern1[1]='1' ✓, vs pattern2[1]='0' ✗
 *   Position 2: '1' vs pattern1[2]='0' ✗, vs pattern2[2]='1' ✓
 *   Position 3: '0' vs pattern1[3]='1' ✗, vs pattern2[3]='0' ✓
 *   Position 4: '0' vs pattern1[4]='0' ✓, vs pattern2[4]='1' ✗
 *   Position 5: '0' vs pattern1[5]='1' ✗, vs pattern2[5]='0' ✓
 *   Pattern 1: 4 mismatches
 *   Pattern 2: 2 mismatches ✓
 *
 * Window "100011" (indices 2-7 of doubled):
 *   Corresponds to rotation by 2 positions
 *   Pattern 1 at index 2: "010101"
 *   Position 2: '1' vs '0' ✗
 *   Position 3: '0' vs '1' ✗
 *   Position 4: '0' vs '0' ✓
 *   Position 5: '0' vs '1' ✗
 *   Wait, this gets confusing...
 *
 * The key is: when we slide the window, the pattern also shifts!
 * Pattern expectations are based on absolute index i in doubled string.
 *
 * Final answer: 2 ✓
 *
 * ===================================================================
 *
 * DETAILED WALKTHROUGH - Example 2: s = "010"
 *
 * Original: "010"
 * Doubled: "010010"
 *
 * Window "010":
 *   Pattern 1 "010": 0 mismatches ✓
 *   Pattern 2 "101": 3 mismatches
 *
 * Answer: 0 ✓
 *
 * ===================================================================
 *
 * WHY THIS WORKS - Algorithm Correctness:
 *
 * 1. ROTATION SIMULATION:
 *    - Doubling string s → s+s contains all rotations as substrings
 *    - Window [i, i+n) in doubled string = rotation by i positions
 *    - Sliding window checks all n possible rotations
 *
 * 2. TWO PATTERN CHECKING:
 *    - Alternating string must match one of two patterns:
 *      "010101..." or "101010..."
 *    - We track mismatches with both simultaneously
 *    - Take minimum at each rotation
 *
 * 3. SLIDING WINDOW OPTIMIZATION:
 *    - Instead of recounting for each rotation: O(n²)
 *    - Use sliding window: add new char, remove old char: O(1) per step
 *    - Total: O(n) time
 *
 * 4. PATTERN POSITION INDEXING:
 *    - Pattern expectation based on absolute index i in doubled string
 *    - When window slides, pattern automatically shifts
 *    - This correctly simulates rotation effect
 *
 * 5. MINIMUM ACROSS BOTH PATTERNS:
 *    - For each rotation, we can choose which pattern to match
 *    - Always choose the one requiring fewer flips
 *    - min(pattern1_mismatches, pattern2_mismatches)
 *
 * COMPLEXITY ANALYSIS:
 * - Time: O(n) - single pass through doubled string
 * - Space: O(n) - for doubled string
 *
 * EDGE CASES:
 * - Already alternating: 0 flips
 * - Single character: 0 flips (trivially alternating)
 * - All same character: n/2 or (n+1)/2 flips needed
 */
int main()
{
    return 0;
}