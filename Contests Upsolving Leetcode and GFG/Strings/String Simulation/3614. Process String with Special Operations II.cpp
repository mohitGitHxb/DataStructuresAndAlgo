#include <bits/stdc++.h>
using namespace std;
class Solution
{
private:
    /*
     * PROBLEM UNDERSTANDING:
     * - Process string s left-to-right building result:
     *   - lowercase letter: append to result
     *   - '*': remove last character
     *   - '#': duplicate result (result += result)
     *   - '%': reverse result
     * - Find k-th character of final result
     *
     * KEY INSIGHT - Reverse Simulation (Work Backwards):
     *
     * OBSERVATION 1: Result can be astronomically large
     * - '#' doubles the length each time
     * - After just 60 '#' operations: length > 2^60
     * - Cannot build the actual result string
     *
     * OBSERVATION 2: Forward Pass to Get Final Length
     * - Simulate length changes without storing result
     * - Track final length after all operations
     * - If k >= final length → return '.'
     *
     * OBSERVATION 3: Reverse Pass to Find k-th Character
     * - Walk backwards through operations
     * - Undo each operation, adjusting target index k accordingly
     * - When we hit a letter that "would be" at position k: return it
     *
     * REVERSE OPERATION LOGIC:
     *
     * UNDO '*' (which removed a character):
     *   - Going backwards, this character was removed
     *   - So length was (ans + 1) before this operation
     *   - k stays same (the removed character is beyond k if k < ans)
     *
     * UNDO '#' (which doubled the string):
     *   - Before this, length was (ans / 2)
     *   - If k < ans/2: k was in the original first half (k stays)
     *   - If k >= ans/2: k was in the duplicated second half (k -= ans/2)
     *   - Either way: k points to same position in original string
     *
     * UNDO '%' (which reversed the string):
     *   - Before this, the string was in original order
     *   - After reversal, position k maps to position (ans - 1 - k)
     *   - But for even-length strings: careful with the offset
     *   - General formula: k = 2 * (ans/2) - k - (ans%2 == 0 ? 1 : 0)
     *     which simplifies to k = ans - 1 - k for normal case
     *
     * UNDO letter (which appended a character):
     *   - Before this, length was (ans - 1)
     *   - If (ans - 1) == k: this letter IS our target → return it
     *   - Otherwise: adjust ans and continue backwards
     *
     * EXAMPLE: s = "a#b%*", k = 1
     *
     * Forward pass:
     * 'a': len = 1
     * '#': len = 2
     * 'b': len = 3
     * '%': len = 3 (no change)
     * '*': len = 2
     * Final length = 2, k=1 is valid
     *
     * Reverse pass: ans = 2
     * '*' → undo: ans = 3 (restore removed char, k=1 < 3 unchanged)
     * '%' → undo: k = 2*(3/2) - 1 = 4-1 = 3... wait:
     *        mid = 3/2 = 1, ans%2 = 1 (odd)
     *        k = 2*1 - 1 = 1 (stays 1)
     *       ans stays 3
     * 'b' → undo: ans = 2, ans != k (2 != 1), continue
     * '#' → undo: mid = 2/2 = 1, k=1 >= 1 → k = 1-1 = 0, ans = 1
     * 'a' → undo: ans = 0, ans == k (0 == 0)? NO... wait
     *        ans-- = 0, if ans == k(0) → return 'a' ✓
     *
     * TIME: O(n)
     * SPACE: O(1)
     */

    /**
     * Forward pass: computes final length of result string
     *
     * @param s - input string
     * @return final length of result after all operations
     */
    long long computeFinalLength(const string &s)
    {
        long long length = 0;

        for (char ch : s)
        {
            if (ch == '*')
            {
                // Remove last character (if exists)
                if (length > 0)
                    length--;
            }
            else if (ch == '#')
            {
                // Duplicate: length doubles
                length *= 2;
            }
            else if (ch == '%')
            {
                // Reverse: length unchanged
                // (no-op for length tracking)
            }
            else
            {
                // Append lowercase letter
                length++;
            }
        }

        return length;
    }

public:
    char processStr(const string &s, long long k)
    {
        // Step 1: Compute final length of result string
        long long finalLength = computeFinalLength(s);

        // k out of bounds
        if (k >= finalLength)
            return '.';

        // Step 2: Walk backwards through s, adjusting k
        // ans = current length as we "undo" operations
        long long currentLength = finalLength;

        for (int i = s.length() - 1; i >= 0; i--)
        {
            char ch = s[i];

            if (ch == '*')
            {
                // UNDO '*': this removed a character, restore it
                // Length before was currentLength + 1
                currentLength++;
                // k is unaffected (removed char was at end, after our target)
            }
            else if (ch == '#')
            {
                // UNDO '#': this doubled the string
                // Before doubling, length was currentLength / 2
                long long halfLength = currentLength / 2;

                // k could be in first half or second half
                // Both halves are identical, so map to first half
                if (k >= halfLength)
                {
                    k -= halfLength; // k was in second half, map to first half
                }
                // else: k was already in first half, no change

                currentLength = halfLength;
            }
            else if (ch == '%')
            {
                // UNDO '%': this reversed the string
                // Before reversal, position k was at mirrored position
                // For string of length L: position k maps to (L-1-k)
                // But we use the formula accounting for odd/even length
                long long halfLength = currentLength / 2;
                k = 2 * halfLength - k - (currentLength % 2 == 0 ? 1 : 0);
                // Note: this simplifies to k = currentLength - 1 - k for all cases
                // currentLength is unchanged by reversal
            }
            else
            {
                // UNDO letter append: this added a character at position (currentLength - 1)
                currentLength--;

                // Check if the appended character is our target
                if (currentLength == k)
                {
                    return ch; // Found it!
                }
                // else: our target was placed before this character
            }
        }

        return '.'; // Should not reach here for valid input
    }
};

/*
 * DETAILED WALKTHROUGH - Example 1: s = "a#b%*", k = 1
 *
 * ===== Forward Pass =====
 *
 * 'a': length = 0+1 = 1    (result = "a")
 * '#': length = 1*2 = 2    (result = "aa")
 * 'b': length = 2+1 = 3    (result = "aab")
 * '%': length = 3           (result = "baa")
 * '*': length = 3-1 = 2    (result = "ba")
 *
 * finalLength = 2, k = 1 < 2 → valid
 *
 * ===== Reverse Pass: currentLength = 2, k = 1 =====
 *
 * i=4, ch='*' (UNDO remove):
 *   currentLength = 2+1 = 3
 *   k = 1 (unchanged)
 *
 * i=3, ch='%' (UNDO reverse):
 *   halfLength = 3/2 = 1
 *   k = 2*1 - 1 - 0 = 2-1 = 1
 *   (3 is odd, so no -1 adjustment)
 *   Actually: k = 3-1-1 = 1 (same)
 *   currentLength = 3 (unchanged)
 *
 * i=2, ch='b' (UNDO append):
 *   currentLength = 3-1 = 2
 *   currentLength == k? 2 == 1? NO
 *   Continue
 *
 * i=1, ch='#' (UNDO duplicate):
 *   halfLength = 2/2 = 1
 *   k = 1 >= 1? YES → k = 1-1 = 0
 *   currentLength = 1
 *
 * i=0, ch='a' (UNDO append):
 *   currentLength = 1-1 = 0
 *   currentLength == k? 0 == 0? YES → return 'a' ✓
 *
 * ===================================================================
 *
 * DETAILED WALKTHROUGH - Example 2: s = "cd%#*#", k = 3
 *
 * ===== Forward Pass =====
 * 'c': length = 1    (result = "c")
 * 'd': length = 2    (result = "cd")
 * '%': length = 2    (result = "dc")
 * '#': length = 4    (result = "dcdc")
 * '*': length = 3    (result = "dcd")
 * '#': length = 6    (result = "dcddcd")
 *
 * finalLength = 6, k = 3 < 6 → valid
 *
 * ===== Reverse Pass: currentLength = 6, k = 3 =====
 *
 * i=5, ch='#' (UNDO duplicate):
 *   halfLength = 6/2 = 3
 *   k = 3 >= 3? YES → k = 3-3 = 0
 *   currentLength = 3
 *
 * i=4, ch='*' (UNDO remove):
 *   currentLength = 3+1 = 4
 *   k = 0 (unchanged)
 *
 * i=3, ch='#' (UNDO duplicate):
 *   halfLength = 4/2 = 2
 *   k = 0 >= 2? NO
 *   k = 0 (unchanged)
 *   currentLength = 2
 *
 * i=2, ch='%' (UNDO reverse):
 *   k = 2-1-0 = 1
 *   currentLength = 2 (unchanged)
 *
 * i=1, ch='d' (UNDO append):
 *   currentLength = 2-1 = 1
 *   currentLength == k? 1 == 1? YES → return 'd' ✓
 *
 * ===================================================================
 *
 * UNDO '%' FORMULA DERIVATION:
 *
 * For string of length L, reversal maps position k to position (L-1-k).
 * Going backwards (undoing reversal), we need the SAME mapping:
 *
 * If reversed string has position k,
 * original position was (L-1-k).
 *
 * Formula breakdown:
 *   For odd L: k = 2*(L/2) - k     = L-1-k  ✓  (since L/2 = (L-1)/2 for odd L)
 *   For even L: k = 2*(L/2) - k - 1 = L-1-k  ✓  (adjustment for even)
 *
 * Both simplify to k = currentLength - 1 - k
 *
 * ===================================================================
 *
 * WHY THIS WORKS:
 *
 * 1. FORWARD PASS JUSTIFICATION:
 *    - Only tracks length, not content
 *    - Sufficient to determine if k is in bounds
 *
 * 2. REVERSE PASS CORRECTNESS:
 *    - Each operation is perfectly invertible
 *    - We maintain: "target character is at position k in string of length currentLength"
 *    - Each undo operation preserves this invariant
 *
 * 3. TERMINATION:
 *    - When we undo a letter append at position k, we've found our target
 *    - The letter that was appended IS the k-th character
 *
 * COMPLEXITY ANALYSIS:
 * - Forward pass: O(n)
 * - Reverse pass: O(n)
 * - Total: O(n)
 * - Space: O(1) extra (no string built)
 */

int main()
{
    return 0;
}