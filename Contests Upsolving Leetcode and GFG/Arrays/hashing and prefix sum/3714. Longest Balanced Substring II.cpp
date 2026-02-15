#include <bits/stdc++.h>
using namespace std;
class Solution
{
private:
    /*
     * PROBLEM UNDERSTANDING:
     * - String contains only 'a', 'b', 'c'
     * - Balanced substring: all distinct characters appear equal times
     * - Goal: Find longest balanced substring
     *
     * KEY INSIGHT - Multiple Cases to Consider:
     *
     * CASE 1: Single character (e.g., "aaa", "bb")
     *   - Always balanced (only one distinct character)
     *   - Track longest consecutive sequence
     *
     * CASE 2: Two distinct characters (e.g., "aabb", "abba")
     *   - Balanced when count(char1) = count(char2)
     *   - Use difference tracking: diff = count(char1) - count(char2)
     *   - When diff = 0 or returns to previous diff value → balanced
     *
     * CASE 3: All three characters (e.g., "aabbcc", "abc")
     *   - Balanced when count(a) = count(b) = count(c)
     *   - Track two differences: (b-a) and (c-a)
     *   - When both return to previous state → balanced
     *
     * APPROACH:
     * 1. Check longest single-character sequence
     * 2. For each pair of characters, find longest balanced substring
     * 3. For all three characters, find longest balanced substring
     * 4. Return maximum across all cases
     *
     * EXAMPLE: s = "abbac"
     *
     * Case 1: Longest single = "bb" → length 2
     * Case 2 (a,b): "abba" → count(a)=2, count(b)=2 → length 4 ✓
     * Case 3 (a,b,c): No substring with all three equal
     *
     * Maximum = 4
     *
     * TIME: O(n) - linear scan with hash map
     * SPACE: O(n) - hash maps for tracking states
     */

    /**
     * Finds longest consecutive sequence of same character
     *
     * @param s - input string
     * @return length of longest single-character substring
     */
    int findLongestSingleCharacter(const string &s)
    {
        if (s.empty())
            return 0;

        int maxLength = 1;
        int currentLength = 1;

        for (int i = 1; i < s.size(); i++)
        {
            if (s[i] == s[i - 1])
            {
                currentLength++;
            }
            else
            {
                currentLength = 1;
            }
            maxLength = max(maxLength, currentLength);
        }

        return maxLength;
    }

    /**
     * Finds longest balanced substring containing exactly two specific characters
     * Uses difference tracking: when diff returns to a previous value, segment is balanced
     *
     * @param s - input string
     * @param char1 - first character to consider
     * @param char2 - second character to consider
     * @return length of longest balanced substring with these two characters
     */
    int findLongestTwoCharacters(const string &s, char char1, char char2)
    {
        // Map: difference → last index where this difference occurred
        unordered_map<int, int> diffToIndex;
        diffToIndex[0] = -1; // Base case: difference 0 before string starts

        int count1 = 0, count2 = 0;
        int maxLength = 0;

        for (int i = 0; i < s.size(); i++)
        {
            // If we encounter a character not in our pair, reset
            if (s[i] != char1 && s[i] != char2)
            {
                diffToIndex.clear();
                diffToIndex[0] = i; // Reset base: diff=0 at current position
                count1 = 0;
                count2 = 0;
                continue;
            }

            // Update counts
            if (s[i] == char1)
                count1++;
            if (s[i] == char2)
                count2++;

            // Calculate difference
            int diff = count1 - count2;

            // If we've seen this difference before, substring is balanced
            if (diffToIndex.find(diff) != diffToIndex.end())
            {
                int length = i - diffToIndex[diff];
                maxLength = max(maxLength, length);
            }
            else
            {
                // First time seeing this difference, record position
                diffToIndex[diff] = i;
            }
        }

        return maxLength;
    }

    /**
     * Finds longest balanced substring containing all three characters
     * Uses two-difference tracking: (b-a) and (c-a)
     * When both differences return to previous state, all three counts are equal
     *
     * @param s - input string
     * @return length of longest balanced substring with all three characters
     */
    int findLongestThreeCharacters(const string &s)
    {
        // Map: "diff1#diff2" → last index where this state occurred
        unordered_map<string, int> stateToIndex;
        stateToIndex["0#0"] = -1; // Base case: all counts equal at start

        int countA = 0, countB = 0, countC = 0;
        int maxLength = 0;

        for (int i = 0; i < s.size(); i++)
        {
            // Update counts
            if (s[i] == 'a')
                countA++;
            else if (s[i] == 'b')
                countB++;
            else
                countC++;

            // Create state key: (b-a)#(c-a)
            // If b-a = 0 and c-a = 0, then a = b = c (balanced!)
            string state = to_string(countB - countA) + "#" + to_string(countC - countA);

            // If we've seen this state before, substring between is balanced
            if (stateToIndex.find(state) != stateToIndex.end())
            {
                int length = i - stateToIndex[state];
                maxLength = max(maxLength, length);
            }
            else
            {
                // First time seeing this state, record position
                stateToIndex[state] = i;
            }
        }

        return maxLength;
    }

public:
    int longestBalanced(string s)
    {
        int maxLength = 0;

        // Case 1: Single character substrings
        int singleCharMax = findLongestSingleCharacter(s);
        maxLength = max(maxLength, singleCharMax);

        // Case 2: Two-character pairs
        vector<pair<char, char>> characterPairs = {
            {'a', 'b'},
            {'a', 'c'},
            {'b', 'c'}};

        for (const auto &[char1, char2] : characterPairs)
        {
            int twoCharMax = findLongestTwoCharacters(s, char1, char2);
            maxLength = max(maxLength, twoCharMax);
        }

        // Case 3: All three characters
        int threeCharMax = findLongestThreeCharacters(s);
        maxLength = max(maxLength, threeCharMax);

        return maxLength;
    }
};

/*
 * DETAILED WALKTHROUGH - Example 1: s = "abbac"
 *
 * String indices:  0  1  2  3  4
 * Characters:      a  b  b  a  c
 *
 * ===== CASE 1: Single Character =====
 *
 * i=1: s[1]='b' = s[0]='a'? No → currentLength = 1
 * i=2: s[2]='b' = s[1]='b'? Yes → currentLength = 2
 * i=3: s[3]='a' = s[2]='b'? No → currentLength = 1
 * i=4: s[4]='c' = s[3]='a'? No → currentLength = 1
 *
 * maxLength = 2 (substring "bb")
 *
 * ===== CASE 2: Pair (a,b) =====
 *
 * diffToIndex = {0: -1}
 *
 * i=0: s[0]='a' → countA=1, countB=0, diff=1
 *   diff not in map → diffToIndex = {0: -1, 1: 0}
 *
 * i=1: s[1]='b' → countA=1, countB=1, diff=0
 *   diff=0 in map at index -1
 *   length = 1 - (-1) = 2
 *   maxLength = 2
 *
 * i=2: s[2]='b' → countA=1, countB=2, diff=-1
 *   diff not in map → diffToIndex = {0: -1, 1: 0, -1: 2}
 *
 * i=3: s[3]='a' → countA=2, countB=2, diff=0
 *   diff=0 in map at index -1
 *   length = 3 - (-1) = 4 ✓
 *   maxLength = 4
 *
 * i=4: s[4]='c' → not 'a' or 'b', reset
 *
 * Pair (a,b) max = 4 (substring "abba")
 *
 * ===== CASE 2: Pair (a,c) =====
 *
 * i=0-3: Only 'a' and 'b', no 'c' yet
 * i=4: s[4]='c' → countA=1, countC=1, diff=0
 *   Substring "ac" → length 2
 *
 * Pair (a,c) max = 2
 *
 * ===== CASE 2: Pair (b,c) =====
 *
 * i=0: s[0]='a' → not in pair, reset
 * i=1-2: Only 'b', no 'c'
 * i=3: s[3]='a' → not in pair, reset
 * i=4: s[4]='c' → only 'c', no balanced pair
 *
 * Pair (b,c) max = 1
 *
 * ===== CASE 3: All Three Characters =====
 *
 * stateToIndex = {"0#0": -1}
 *
 * i=0: s[0]='a' → a=1,b=0,c=0, state="0-1#0-1"="-1#-1"
 * i=1: s[1]='b' → a=1,b=1,c=0, state="1-1#0-1"="0#-1"
 * i=2: s[2]='b' → a=1,b=2,c=0, state="2-1#0-1"="1#-1"
 * i=3: s[3]='a' → a=2,b=2,c=0, state="2-2#0-2"="0#-2"
 * i=4: s[4]='c' → a=2,b=2,c=1, state="2-2#1-2"="0#-1"
 *   state "0#-1" seen at index 1
 *   length = 4 - 1 = 3
 *   But substring "bbac" has b=2,a=1,c=1, not balanced!
 *
 * Wait, let me recalculate...
 * Actually, there's no substring with all three equal in "abbac"
 *
 * ===== FINAL ANSWER =====
 *
 * Maximum = max(2, 4, 2, 1, 0) = 4 ✓
 *
 * ===================================================================
 *
 * DETAILED WALKTHROUGH - Example 2: s = "aabcc"
 *
 * String indices:  0  1  2  3  4
 * Characters:      a  a  b  c  c
 *
 * ===== CASE 3: All Three Characters =====
 *
 * i=0: a=1,b=0,c=0 → state="-1#-1"
 * i=1: a=2,b=0,c=0 → state="-2#-2"
 * i=2: a=2,b=1,c=0 → state="-1#-2"
 * i=3: a=2,b=1,c=1 → state="-1#-1"
 *   Seen at index 0
 *   Substring s[1..3] = "abc" → a=1,b=1,c=1 ✓
 *   length = 3 - 0 = 3
 * i=4: a=2,b=1,c=2 → state="-1#0"
 *
 * Maximum = 3 ✓
 *
 * ===================================================================
 *
 * WHY THIS WORKS - Algorithm Correctness:
 *
 * 1. DIFFERENCE TRACKING (TWO CHARACTERS):
 *    - If count(a) - count(b) returns to previous value,
 *      the intermediate substring has equal a's and b's
 *    - Example: diff=1 at i=5, diff=1 at i=10
 *      → substring [6..10] has equal increments of both
 *
 * 2. TWO-DIFFERENCE TRACKING (THREE CHARACTERS):
 *    - Need two independent differences: (b-a) and (c-a)
 *    - If both return to same state → a, b, c are all equal
 *    - State key: "diff1#diff2" uniquely identifies count ratios
 *
 * 3. RESET ON INVALID CHARACTER:
 *    - For two-char case: third char breaks the pattern
 *    - Must reset state and start fresh
 *
 * 4. BASE CASE:
 *    - Initialize with state at index -1
 *    - Allows matching from start of string
 *    - diff=0 means equal counts from beginning
 *
 * 5. SINGLE CHARACTER CASE:
 *    - Any single character is trivially balanced
 *    - Must check separately as it's always valid
 *
 * COMPLEXITY ANALYSIS:
 * - Time: O(n) for each case × constant cases = O(n)
 * - Space: O(n) for hash maps (worst case all different states)
 *
 * WHY WE NEED ALL CASES:
 * - "aaa" → best is single char (3)
 * - "aabb" → best is two chars (4)
 * - "abc" → best is three chars (3)
 * - Must check all to find true maximum
 */
int main()
{
    return 0;
}