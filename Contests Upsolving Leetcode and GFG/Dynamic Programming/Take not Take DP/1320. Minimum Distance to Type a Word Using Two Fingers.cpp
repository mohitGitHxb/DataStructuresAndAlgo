#include <bits/stdc++.h>
using namespace std;
class Solution
{
private:
    /*
     * PROBLEM UNDERSTANDING:
     * - QWERTY keyboard laid out in 6 columns × 5 rows (letters A-Z)
     * - Two fingers can type
     * - Distance = Manhattan distance |x1-x2| + |y1-y2|
     * - First placement of each finger is free (cost 0)
     * - Goal: Minimum total distance to type word
     *
     * KEY INSIGHT - Dynamic Programming with Finger State:
     *
     * KEYBOARD LAYOUT:
     *   Col: 0  1  2  3  4  5
     * Row 0: A  B  C  D  E  F
     * Row 1: G  H  I  J  K  L
     * Row 2: M  N  O  P  Q  R
     * Row 3: S  T  U  V  W  X
     * Row 4: Y  Z
     *
     * POSITION ENCODING:
     * - Each letter maps to index 0-25 (A=0, B=1, ..., Z=25)
     * - Position = row * 6 + col
     * - Example: 'P' = 2*6 + 3 = 15
     *
     * STATE REPRESENTATION:
     * - dp[i][f1][f2] = min distance to type word[i..n-1]
     *   where finger1 is at position f1, finger2 at position f2
     * - Special value 26 = finger not yet used
     *
     * TRANSITIONS:
     * For typing word[i]:
     * 1. If no fingers used yet (f1=26, f2=26):
     *    - Place finger1 at word[i] for free
     *
     * 2. If only finger1 used (f2=26):
     *    - Option A: Place finger2 at word[i] for free
     *    - Option B: Move finger1 to word[i] (costs distance)
     *
     * 3. If both fingers used:
     *    - Option A: Move finger1 to word[i]
     *    - Option B: Move finger2 to word[i]
     *
     * EXAMPLE: word = "CAKE"
     *
     * Position: C=2, A=0, K=10, E=4
     *
     * Type 'C': finger1 → C (cost 0)
     *   State: f1=2, f2=26
     *
     * Type 'A': finger1 → A (cost |0-0| + |2-0| = 2)
     *   State: f1=0, f2=26
     *
     * Type 'K': finger2 → K (cost 0, first use)
     *   State: f1=0, f2=10
     *
     * Type 'E': finger2 → E (cost |0-0| + |10-4| = 1... wait)
     *   Actually: E is at position 4 = (0,4)
     *   K is at position 10 = (1,4)
     *   Distance = |0-1| + |4-4| = 1 ✓
     *
     * Total: 0 + 2 + 0 + 1 = 3 ✓
     *
     * TIME: O(n × 27 × 27) = O(n)
     * SPACE: O(n × 27 × 27) = O(n)
     */

    // Special value indicating finger not yet used
    static const int FINGER_UNUSED = 26;

    // DP table: dp[charIndex][finger1Pos][finger2Pos]
    int dp[301][27][27];

    /**
     * Converts letter position (0-25) to (row, col) coordinates
     *
     * Keyboard layout (6 columns):
     * A B C D E F  (row 0)
     * G H I J K L  (row 1)
     * M N O P Q R  (row 2)
     * S T U V W X  (row 3)
     * Y Z          (row 4)
     *
     * @param letterPos - position of letter (0=A, 1=B, ..., 25=Z)
     * @return {row, column} pair
     */
    pair<int, int> getCoordinates(int letterPos)
    {
        return {letterPos / 6, letterPos % 6};
    }

    /**
     * Calculates Manhattan distance between two letter positions
     *
     * @param pos1 - first letter position (0-25)
     * @param pos2 - second letter position (0-25)
     * @return Manhattan distance |x1-x2| + |y1-y2|
     */
    int getManhattanDistance(int pos1, int pos2)
    {
        auto [row1, col1] = getCoordinates(pos1);
        auto [row2, col2] = getCoordinates(pos2);
        return abs(row1 - row2) + abs(col1 - col2);
    }

    /**
     * Recursive DP to find minimum typing distance
     *
     * @param word - the word to type
     * @param charIndex - current character index being typed
     * @param finger1Pos - current position of finger 1 (0-25, or 26=unused)
     * @param finger2Pos - current position of finger 2 (0-25, or 26=unused)
     * @return minimum distance to type word[charIndex..n-1]
     */
    int solveDP(const string &word, int charIndex, int finger1Pos, int finger2Pos)
    {
        // Base case: typed all characters
        if (charIndex >= word.length())
        {
            return 0;
        }

        // Return memoized result
        if (dp[charIndex][finger1Pos][finger2Pos] != -1)
        {
            return dp[charIndex][finger1Pos][finger2Pos];
        }

        // Current character to type
        int targetPos = word[charIndex] - 'A';

        // CASE 1: No fingers used yet (both at position 26)
        if (finger1Pos == FINGER_UNUSED && finger2Pos == FINGER_UNUSED)
        {
            // Place finger1 at target position for free
            return dp[charIndex][finger1Pos][finger2Pos] =
                       solveDP(word, charIndex + 1, targetPos, finger2Pos);
        }

        // CASE 2: Only finger1 used, finger2 not yet placed
        if (finger2Pos == FINGER_UNUSED)
        {
            // Option A: Place finger2 at target (free, first use)
            int useFinger2 = solveDP(word, charIndex + 1, finger1Pos, targetPos);

            // Option B: Move finger1 to target (costs distance)
            int moveFinger1 = getManhattanDistance(finger1Pos, targetPos) +
                              solveDP(word, charIndex + 1, targetPos, finger2Pos);

            return dp[charIndex][finger1Pos][finger2Pos] = min(useFinger2, moveFinger1);
        }

        // CASE 3: Both fingers already in use
        // Option A: Move finger1 to target
        int moveFinger1 = getManhattanDistance(finger1Pos, targetPos) +
                          solveDP(word, charIndex + 1, targetPos, finger2Pos);

        // Option B: Move finger2 to target
        int moveFinger2 = getManhattanDistance(finger2Pos, targetPos) +
                          solveDP(word, charIndex + 1, finger1Pos, targetPos);

        return dp[charIndex][finger1Pos][finger2Pos] = min(moveFinger1, moveFinger2);
    }

public:
    int minimumDistance(string word)
    {
        // Initialize DP table with -1 (uncomputed)
        memset(dp, -1, sizeof(dp));

        // Start with both fingers unused (position 26)
        return solveDP(word, 0, FINGER_UNUSED, FINGER_UNUSED);
    }
};

/*
 * DETAILED WALKTHROUGH - Example 1: word = "CAKE"
 *
 * Letter positions:
 * C = 2  (row=0, col=2)
 * A = 0  (row=0, col=0)
 * K = 10 (row=1, col=4)
 * E = 4  (row=0, col=4)
 *
 * ===== Character 0: 'C' =====
 * Call: solveDP("CAKE", 0, 26, 26)
 *
 * CASE 1: No fingers used
 * Place finger1 at C (position 2)
 * Recurse: solveDP("CAKE", 1, 2, 26)
 *
 * ===== Character 1: 'A' =====
 * Call: solveDP("CAKE", 1, 2, 26)
 * State: finger1=C(2), finger2=unused
 * Target: A(0)
 *
 * CASE 2: Only finger1 used
 *
 * Option A: Place finger2 at A
 *   Cost: 0 (first use of finger2)
 *   Recurse: solveDP("CAKE", 2, 2, 0)
 *   [This path is suboptimal]
 *
 * Option B: Move finger1 from C to A
 *   Distance: |0-0| + |2-0| = 2
 *   Recurse: solveDP("CAKE", 2, 0, 26)
 *   Cost: 2 + result
 *
 * ===== Character 2: 'K' (continuing Option B) =====
 * Call: solveDP("CAKE", 2, 0, 26)
 * State: finger1=A(0), finger2=unused
 * Target: K(10)
 *
 * CASE 2: Only finger1 used
 *
 * Option A: Place finger2 at K
 *   Cost: 0 (first use of finger2)
 *   Recurse: solveDP("CAKE", 3, 0, 10)
 *   [This is the optimal path]
 *
 * Option B: Move finger1 from A to K
 *   Distance: |0-1| + |0-4| = 5
 *   [This is worse]
 *
 * Choose Option A: cost = 0
 *
 * ===== Character 3: 'E' =====
 * Call: solveDP("CAKE", 3, 0, 10)
 * State: finger1=A(0), finger2=K(10)
 * Target: E(4)
 *
 * CASE 3: Both fingers used
 *
 * Option A: Move finger1 from A(0) to E(4)
 *   Distance: |0-0| + |0-4| = 4
 *   Recurse: solveDP("CAKE", 4, 4, 10)
 *   Base case returns 0
 *   Cost: 4
 *
 * Option B: Move finger2 from K(10) to E(4)
 *   K = (row=1, col=4)
 *   E = (row=0, col=4)
 *   Distance: |1-0| + |4-4| = 1
 *   Recurse: solveDP("CAKE", 4, 0, 4)
 *   Base case returns 0
 *   Cost: 1 ✓
 *
 * Choose Option B: cost = 1
 *
 * ===== Total Cost Calculation =====
 *
 * Backtracking through recursion:
 * - Type 'C': 0 (finger1 placed)
 * - Type 'A': 2 (finger1 moved from C to A)
 * - Type 'K': 0 (finger2 placed)
 * - Type 'E': 1 (finger2 moved from K to E)
 *
 * Total: 0 + 2 + 0 + 1 = 3 ✓
 *
 * ===================================================================
 *
 * DETAILED WALKTHROUGH - Example 2: word = "HAPPY"
 *
 * Letter positions:
 * H = 7  (row=1, col=1)
 * A = 0  (row=0, col=0)
 * P = 15 (row=2, col=3)
 * P = 15 (row=2, col=3)
 * Y = 24 (row=4, col=0)
 *
 * Optimal sequence:
 * 1. Type 'H': finger1 → H (cost 0)
 * 2. Type 'A': finger1 → A, distance = |1-0| + |1-0| = 2
 * 3. Type 'P': finger2 → P (cost 0, first use)
 * 4. Type 'P': finger2 → P, distance = 0 (same position)
 * 5. Type 'Y': finger1 → Y, distance = |0-4| + |0-0| = 4
 *
 * Total: 0 + 2 + 0 + 0 + 4 = 6 ✓
 *
 * ===================================================================
 *
 * WHY THIS WORKS - Algorithm Correctness:
 *
 * 1. STATE SPACE COMPLETENESS:
 *    - dp[i][f1][f2] captures all relevant information
 *    - Position of both fingers + remaining word to type
 *    - No other factors affect optimal solution
 *
 * 2. OPTIMAL SUBSTRUCTURE:
 *    - Optimal solution for word[i..n] depends on optimal solutions for word[i+1..n]
 *    - Local choices (which finger to use) combine optimally
 *
 * 3. FIRST PLACEMENT IS FREE:
 *    - Value 26 represents unused finger
 *    - When finger transitions from 26 → any position, cost = 0
 *    - Correctly models "initial positions are free"
 *
 * 4. OVERLAPPING SUBPROBLEMS:
 *    - Same state (i, f1, f2) can be reached through different paths
 *    - Memoization prevents redundant computation
 *
 * 5. EXPLORATION OF ALL CHOICES:
 *    - At each step, try both fingers (when available)
 *    - Take minimum across all valid choices
 *    - Guarantees finding optimal solution
 *
 * COMPLEXITY ANALYSIS:
 * - States: n × 27 × 27 = O(n) since 27² is constant
 * - Per state: O(1) computation
 * - Total: O(n)
 * - Space: O(n) for DP table (729n integers)
 *
 * COORDINATE SYSTEM:
 * - Position encoding: letter - 'A' gives 0-25
 * - Grid: 6 columns × 5 rows (last row has only 2 letters)
 * - row = pos / 6, col = pos % 6
 * - Manhattan distance = |row1-row2| + |col1-col2|
 *
 * EDGE CASES:
 * - Single character: cost = 0 (place finger for free)
 * - Repeated characters: cost = 0 between repetitions
 * - All same character: total cost = 0
 */
int main()
{
    return 0;
}