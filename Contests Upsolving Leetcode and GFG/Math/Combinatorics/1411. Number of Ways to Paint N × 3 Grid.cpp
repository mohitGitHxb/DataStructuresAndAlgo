#include <bits/stdc++.h>
using namespace std;
class Solution
{
private:
    /*
     * PROBLEM UNDERSTANDING:
     * - Grid of n rows × 3 columns
     * - Paint each cell with Red, Yellow, or Green
     * - Adjacent cells (horizontal or vertical) must have different colors
     * - Count total valid colorings modulo 10^9 + 7
     *
     * KEY INSIGHT - Pattern Recognition:
     *
     * Instead of thinking about individual cells, recognize that each row
     * must follow one of TWO patterns:
     *
     * PATTERN A (ABA): Two same colors with different middle
     *   Examples: RYR, RGR, YRY, YGY, GRG, GYG
     *   Count: 3 choices for outer color × 2 choices for middle = 6 patterns
     *
     * PATTERN B (ABC): All three different colors
     *   Examples: RYG, RGY, YRG, YGR, GRY, GYR
     *   Count: 3! = 6 patterns
     *
     * Total first row possibilities: 6 + 6 = 12 ✓
     *
     * TRANSITION RULES (Compatibility Between Rows):
     *
     * When placing row i+1 below row i, we must ensure no vertical conflicts.
     *
     * From ABA row (e.g., RYR):
     *   └→ Can form 3 ABA patterns below (e.g., YRY, YGY, GRG)
     *   └→ Can form 2 ABC patterns below (e.g., YRG, YGR)
     *
     * From ABC row (e.g., RYG):
     *   └→ Can form 2 ABA patterns below (e.g., YRY, GRG)
     *   └→ Can form 2 ABC patterns below (e.g., YRG, GYR)
     *
     * DP FORMULA:
     *   newABA = currentABA × 3 + currentABC × 2
     *   newABC = currentABA × 2 + currentABC × 2
     *
     * EXAMPLE VERIFICATION (n=1):
     * ABA: RYR, RGR, YRY, YGY, GRG, GYG = 6
     * ABC: RYG, RGY, YRG, YGR, GRY, GYR = 6
     * Total: 12 ✓
     *
     * EXAMPLE TRACE (n=2):
     * Row 1: ABA=6, ABC=6
     * Row 2: ABA = 6×3 + 6×2 = 30
     *        ABC = 6×2 + 6×2 = 24
     * Total: 54
     *
     * TIME: O(n)
     * SPACE: O(1)
     */

    static const int MOD = 1e9 + 7;

    /**
     * Calculates the number of valid ABA patterns that can follow a given row pattern
     *
     * From an ABA row: 3 valid ABA patterns
     *   Example: RYR → can place YRY, YGY, GRG below
     * From an ABC row: 2 valid ABA patterns
     *   Example: RYG → can place YRY, GRG below
     *
     * @param currentABA - number of ways to reach current row with ABA pattern
     * @param currentABC - number of ways to reach current row with ABC pattern
     * @return number of ways to form next row with ABA pattern
     */
    long long calculateNextABA(long long currentABA, long long currentABC)
    {
        return (currentABA * 3 + currentABC * 2) % MOD;
    }

    /**
     * Calculates the number of valid ABC patterns that can follow a given row pattern
     *
     * From an ABA row: 2 valid ABC patterns
     *   Example: RYR → can place YRG, YGR below
     * From an ABC row: 2 valid ABC patterns
     *   Example: RYG → can place YRG, GYR below
     *
     * @param currentABA - number of ways to reach current row with ABA pattern
     * @param currentABC - number of ways to reach current row with ABC pattern
     * @return number of ways to form next row with ABC pattern
     */
    long long calculateNextABC(long long currentABA, long long currentABC)
    {
        return (currentABA * 2 + currentABC * 2) % MOD;
    }

public:
    int numOfWays(int n)
    {
        // Base case: First row has 6 ABA patterns and 6 ABC patterns
        long long waysABA = 6; // Number of valid ABA patterns up to current row
        long long waysABC = 6; // Number of valid ABC patterns up to current row

        // Build solution row by row using DP
        for (int row = 2; row <= n; row++)
        {
            // Calculate valid patterns for next row based on current row
            long long nextABA = calculateNextABA(waysABA, waysABC);
            long long nextABC = calculateNextABC(waysABA, waysABC);

            // Update state for next iteration
            waysABA = nextABA;
            waysABC = nextABC;
        }

        // Total ways = all possible colorings ending with ABA + ending with ABC
        return (waysABA + waysABC) % MOD;
    }
};

/*
 * DETAILED WALKTHROUGH - Understanding Pattern Transitions
 *
 * ===== WHY ONLY 2 PATTERN TYPES? =====
 *
 * For a 1×3 row with constraint "adjacent cells must differ":
 *
 * Position:  [0] [1] [2]
 *
 * Constraints:
 * - cell[0] ≠ cell[1]
 * - cell[1] ≠ cell[2]
 *
 * Question: Does cell[0] = cell[2]?
 * - If YES → ABA pattern (e.g., Red Yellow Red)
 * - If NO  → ABC pattern (e.g., Red Yellow Green)
 *
 * These are the ONLY two possibilities!
 *
 * ===== COUNTING PATTERNS =====
 *
 * ABA Patterns (cell[0] = cell[2] ≠ cell[1]):
 *   RYR, RGR  ← outer=Red, middle=Yellow or Green
 *   YRY, YGY  ← outer=Yellow, middle=Red or Green
 *   GRG, GYG  ← outer=Green, middle=Red or Yellow
 *   Total: 3 × 2 = 6
 *
 * ABC Patterns (all different):
 *   RYG, RGY  ← start with Red
 *   YRG, YGR  ← start with Yellow
 *   GRY, GYR  ← start with Green
 *   Total: 3 × 2 × 1 = 6
 *
 * ===== TRANSITION RULES DERIVATION =====
 *
 * Consider current row pattern and next row pattern compatibility:
 *
 * Example 1: Current = ABA (RYR), Next = ABA
 *   Current:  R Y R
 *   Next:     ? ? ?
 *
 *   Constraints:
 *   - next[0] ≠ R (vertical)
 *   - next[1] ≠ Y (vertical)
 *   - next[2] ≠ R (vertical)
 *   - next[0] ≠ next[1] (horizontal)
 *   - next[1] ≠ next[2] (horizontal)
 *   - next[0] = next[2] (ABA pattern)
 *
 *   Valid combinations:
 *   1. YRY (outer=Y, middle=R)
 *   2. YGY (outer=Y, middle=G)
 *   3. GRG (outer=G, middle=R)
 *
 *   Count: 3 ✓
 *
 * Example 2: Current = ABA (RYR), Next = ABC
 *   Current:  R Y R
 *   Next:     ? ? ?
 *
 *   Must have: next[0] ≠ R, next[1] ≠ Y, next[2] ≠ R, all different
 *
 *   Valid combinations:
 *   1. YRG
 *   2. YGR
 *
 *   Count: 2 ✓
 *
 * Example 3: Current = ABC (RYG), Next = ABA
 *   Current:  R Y G
 *   Next:     ? ? ?
 *
 *   Must have: next[0] ≠ R, next[1] ≠ Y, next[2] ≠ G, outer same
 *
 *   Valid combinations:
 *   1. YRY
 *   2. GRG
 *
 *   Count: 2 ✓
 *
 * Example 4: Current = ABC (RYG), Next = ABC
 *   Current:  R Y G
 *   Next:     ? ? ?
 *
 *   Must have: next[0] ≠ R, next[1] ≠ Y, next[2] ≠ G, all different
 *
 *   Valid combinations:
 *   1. YRG (swap first two with current)
 *   2. GYR (cyclic rotation)
 *
 *   Count: 2 ✓
 *
 * ===== TRANSITION MATRIX =====
 *
 * Current → Next | ABA | ABC
 * ---------------+-----+----
 * ABA            |  3  |  2
 * ABC            |  2  |  2
 *
 * This gives us the recurrence:
 *   newABA = 3 × oldABA + 2 × oldABC
 *   newABC = 2 × oldABA + 2 × oldABC
 *
 * ===== EXAMPLE TRACE: n = 3 =====
 *
 * Row 1 (base):
 *   waysABA = 6
 *   waysABC = 6
 *
 * Row 2:
 *   nextABA = 3×6 + 2×6 = 18 + 12 = 30
 *   nextABC = 2×6 + 2×6 = 12 + 12 = 24
 *   Update: waysABA = 30, waysABC = 24
 *
 * Row 3:
 *   nextABA = 3×30 + 2×24 = 90 + 48 = 138
 *   nextABC = 2×30 + 2×24 = 60 + 48 = 108
 *   Update: waysABA = 138, waysABC = 108
 *
 * Total: (138 + 108) % MOD = 246
 *
 * ===================================================================
 *
 * WHY THIS WORKS - Algorithm Correctness:
 *
 * 1. PATTERN EXHAUSTIVENESS:
 *    - We've proven that ANY valid 1×3 coloring is either ABA or ABC
 *    - No other patterns exist under the constraint
 *
 * 2. TRANSITION COMPLETENESS:
 *    - We've verified all 4 transition cases (ABA→ABA, ABA→ABC, etc.)
 *    - The multipliers (3, 2, 2, 2) are exact counts
 *
 * 3. STATE SUFFICIENCY:
 *    - Only need to track ABA and ABC counts, not actual colors
 *    - Pattern type is sufficient for determining next row possibilities
 *
 * 4. MODULAR ARITHMETIC:
 *    - Applied at each step to prevent overflow
 *    - Maintains correctness: (a+b) mod m = ((a mod m) + (b mod m)) mod m
 *
 * 5. SPACE OPTIMIZATION:
 *    - Only current row state needed (not all previous rows)
 *    - O(1) space using two variables instead of array
 *
 * ALTERNATIVE APPROACHES:
 * - Backtracking: O(3^(3n)) - too slow
 * - Matrix exponentiation: O(log n) but more complex, overkill for this problem
 * - Current DP: O(n) time, O(1) space - optimal for this problem
 */
int main()
{
    return 0;
}