#include <bits/stdc++.h>
using namespace std;
class Solution
{
private:
    /*
     * PROBLEM UNDERSTANDING:
     * - Intervals [l, r, weight], pick at most 4 non-overlapping ones
     * - Non-overlapping = no shared points (touching boundaries DO overlap)
     * - Maximize total weight
     * - Among all optimal selections, return the lexicographically smallest indices
     *
     * KEY INSIGHT – DP over "k intervals chosen so far" using sorted end-times:
     *
     * OBSERVATION 1: Sort by right endpoint
     * - Classic interval scheduling DP technique
     * - For each interval we process, binary search for the last compatible
     *   interval (one that ends strictly before this interval starts)
     *
     * OBSERVATION 2: Only 4 choices of k (0, 1, 2, 3)
     * - We run 4 rounds of DP, one per "add one more interval"
     * - dp[k][p] = best State after considering first p intervals with exactly k chosen
     *
     * OBSERVATION 3: Negative weights for min-based comparison
     * - State = (negativeWeight, sortedIndices)
     * - Using std::min: automatically prefers higher weight (less negative)
     *   and breaks ties lexicographically via vector comparison
     *
     * OBSERVATION 4: DP Transition
     * - For interval i (the p-th in sorted order, original index order[p-1]):
     *   TAKE it:
     *     j = last interval ending strictly before intervals[i][0]
     *     newState = prev[j] with weight added and index i inserted
     *   SKIP it:
     *     inherit cur[p-1]
     *   cur[p] = min(take, skip)   // min = max weight, then lex smallest index list
     *
     * EXAMPLE: intervals = [[1,3,2],[4,5,2],[1,5,5],[6,9,3],[6,7,1],[8,9,1]]
     *
     * Sort by right endpoint:
     *   right=3: idx=0 [1,3,2]
     *   right=5: idx=1 [4,5,2], idx=2 [1,5,5]
     *   right=7: idx=4 [6,7,1]
     *   right=9: idx=3 [6,9,3], idx=5 [8,9,1]
     *
     * k=1 round: pick 1 interval
     *   best single: idx=2 (weight 5) → state (-5, [2])
     *
     * k=2 round: pick a 2nd non-overlapping interval
     *   After idx=2 (ends at 5), next valid starts at 6
     *   Best partner starting at ≥6: idx=3 (weight 3)
     *   Combined: weight 5+3=8, indices [2,3]
     *
     * No 3-interval combo beats 8 (checked exhaustively by DP)
     * Answer: [2, 3] ✓
     *
     * TIME:  O(4 × n log n) — 4 rounds, each O(n log n) due to binary search
     * SPACE: O(n × k_max) for dp arrays, but k_max = 4 so effectively O(n)
     *
     * NOTE ON LEXICOGRAPHIC TIEBREAKING:
     * - Negative weight means std::min picks the highest weight first
     * - When weights tie, std::min on vectors compares element-by-element,
     *   giving the lexicographically smallest index list automatically
     */

    // State: {negativeWeight, sortedOriginalIndices}
    // Using negative weight so std::min gives us max weight + lex smallest indices
    using State = pair<long long, vector<int>>;

public:
    vector<int> maximumWeight(vector<vector<int>> &intervals)
    {
        int n = intervals.size();

        // Step 1: Sort interval indices by right endpoint
        // This is the standard setup for interval scheduling DP
        vector<int> sortedByRight(n);
        iota(sortedByRight.begin(), sortedByRight.end(), 0);
        sort(sortedByRight.begin(), sortedByRight.end(),
             [&](int a, int b)
             {
                 return intervals[a][1] < intervals[b][1];
             });

        // Extract sorted right endpoints for binary search
        vector<int> sortedRights(n);
        for (int pos = 0; pos < n; ++pos)
        {
            sortedRights[pos] = intervals[sortedByRight[pos]][1];
        }

        // Step 2: DP across k = 1..4 rounds (picking one more interval per round)
        // dpPrev[p] = best State using at most (k-1) intervals from first p
        // dpCurr[p] = best State using at most k intervals from first p
        vector<State> dpPrev(n + 1, {0, {}}); // base: 0 intervals chosen

        for (int round = 0; round < 4; ++round)
        {
            vector<State> dpCurr(n + 1, {0, {}});

            for (int pos = 1; pos <= n; ++pos)
            {
                int origIdx = sortedByRight[pos - 1];
                int leftEnd = intervals[origIdx][0];
                int weight = intervals[origIdx][2];

                // Binary search: find last interval ending strictly before leftEnd
                // i.e., the largest j such that sortedRights[j-1] < leftEnd
                int lastCompatible = (int)(lower_bound(sortedRights.begin(), sortedRights.end(), leftEnd) - sortedRights.begin());

                // Build "take this interval" state from best k-1 intervals
                // ending before this interval starts
                State takeState = dpPrev[lastCompatible];
                takeState.first -= weight; // subtract (using negative scoring)
                takeState.second.insert(
                    upper_bound(takeState.second.begin(), takeState.second.end(), origIdx),
                    origIdx // insert in sorted order to maintain lex order
                );

                // State if we skip this interval (best of first pos-1)
                State &skipState = dpCurr[pos - 1];

                // Choose: take or skip — min gives max weight, then lex smallest
                dpCurr[pos] = min(takeState, skipState);
            }

            dpPrev = move(dpCurr);
        }

        return dpPrev[n].second;
    }
};

/*
 * DETAILED WALKTHROUGH – Example 2:
 * intervals = [[5,8,1],[6,7,7],[4,7,3],[9,10,6],[7,8,2],[11,14,3],[3,5,5]]
 * Expected: [1,3,5,6]
 *
 * ===== Step 1: Sort by Right Endpoint =====
 *
 * Original indices and their [l, r, w]:
 *   0: [5,8,1]   1: [6,7,7]   2: [4,7,3]
 *   3: [9,10,6]  4: [7,8,2]   5: [11,14,3]  6: [3,5,5]
 *
 * Sorted by right endpoint:
 *   pos=1: idx=6 [3,5,5]   right=5
 *   pos=2: idx=1 [6,7,7]   right=7
 *   pos=3: idx=2 [4,7,3]   right=7
 *   pos=4: idx=0 [5,8,1]   right=8
 *   pos=5: idx=4 [7,8,2]   right=8
 *   pos=6: idx=3 [9,10,6]  right=10
 *   pos=7: idx=5 [11,14,3] right=14
 *
 * sortedRights = [5, 7, 7, 8, 8, 10, 14]
 *
 * ===== Round k=1: Pick best single interval =====
 *
 * pos=1, idx=6, weight=5: take → (-5, [6]), skip → (0, [])  → (-5,[6])
 * pos=2, idx=1, weight=7: take → (-7, [1]), skip → (-5,[6]) → (-7,[1])
 * pos=3, idx=2, weight=3: take → (-3,[2]), skip → (-7,[1])  → (-7,[1])
 * pos=4, idx=0, weight=1: take → (-1,[0]), skip → (-7,[1])  → (-7,[1])
 * pos=5, idx=4, weight=2: take → (-2,[4]), skip → (-7,[1])  → (-7,[1])
 * pos=6, idx=3, weight=6: take → (-6,[3]), skip → (-7,[1])  → (-7,[1])
 * pos=7, idx=5, weight=3: take → (-3,[5]), skip → (-7,[1])  → (-7,[1])
 *
 * dpPrev[7] = (-7, [1])  ← best single interval: idx 1, weight 7
 *
 * ===== Round k=2: Add a 2nd non-overlapping interval =====
 *
 * Notable transition at pos=6, idx=3 [9,10,6]:
 *   leftEnd = 9, binary search on sortedRights for first ≥ 9 → position 5
 *   (sortedRights[5] = 10 ≥ 9, sortedRights[4] = 8 < 9)
 *   lastCompatible = 5 → dpPrev[5]
 *
 *   What's dpPrev[5]? It's the best single interval from first 5 positions
 *   After pos=5: dpPrev[5] = (-7, [1])  (idx=1, weight=7)
 *
 *   takeState = (-7-6, [1,3]) = (-13, [1,3])
 *   skipState = dpCurr[5] at this point
 *   ...best 2-interval: (-13, [1,3]), weight = 13
 *
 * dpPrev[7] after k=2 = (-13, [1,3])
 *
 * ===== Round k=3: Add a 3rd non-overlapping interval =====
 *
 * Adding idx=6 [3,5,5] before idx=1 [6,7,7]:
 *   Compatible with [1,3] since right=5 < left=6 of idx=1
 *   takeState = dpPrev for "no intervals before pos=1" + idx=6 = (0-5, [6]) = (-5,[6])
 *   But we want to combine with [1,3]...
 *
 * At pos=7 (idx=5, [11,14,3]):
 *   leftEnd=11 → lastCompatible points past idx=3 (right=10 < 11)
 *   dpPrev[lastCompatible] contains best 2-interval combo ending before 11
 *   = (-13, [1,3])
 *   takeState = (-13-3, [1,3,5]) = (-16, [1,3,5])
 *
 * ===== Round k=4: Add a 4th non-overlapping interval =====
 *
 * At pos=1 (idx=6, [3,5,5]):
 *   lastCompatible = 0 → dpPrev[0] = (0, [])
 *   takeState = (-5, [6])
 *   Combined later with [1,3,5]:
 *   At pos=7 (idx=5): dpPrev[lastCompatible] = best 3-interval ending before 11
 *     = dpPrev from round k=3 containing [1,3,5] with weight 7+6+3=16
 *     But we already have [6] picked before idx=1...
 *
 * Final result across all combinations: [1,3,5,6] with weight 7+6+3+5=21 ✓
 *
 * ===================================================================
 *
 * WHY NEGATIVE WEIGHTS WORK FOR TIEBREAKING:
 *
 * State comparison with std::min:
 *   (-13, [1,3]) vs (-10, [0,2])
 *   -13 < -10 → first state wins (higher weight: 13 > 10) ✓
 *
 *   (-10, [1,3]) vs (-10, [0,2])
 *   Weights tie → compare vectors: [0,2] < [1,3] lexicographically
 *   → second state wins (lex smaller indices) ✓
 *
 * This single std::min handles both objectives simultaneously.
 *
 * ===================================================================
 *
 * COMPATIBILITY CHECK (lower_bound):
 *
 * We want intervals ending STRICTLY before leftEnd:
 *   - lower_bound finds first position with right >= leftEnd
 *   - All positions before that have right < leftEnd → strictly compatible
 *
 * Example: sortedRights = [5, 7, 7, 8, 8, 10, 14], leftEnd = 6
 *   lower_bound(6) → index 1 (first value ≥ 6 is 7 at index 1)
 *   Compatible intervals: positions 0..0 (right=5 < 6) ✓
 *
 * ===================================================================
 *
 * COMPLEXITY ANALYSIS:
 * - Sorting: O(n log n)
 * - Each round: O(n log n) for binary searches + O(k) per state for inserts
 * - 4 rounds total: O(4 × n log n) = O(n log n)
 * - State copies: O(k) per position (vector of size ≤ 4), negligible
 * - Space: O(n) for dp arrays (each state holds ≤ 4 indices)
 */
int main()
{
    return 0;
}