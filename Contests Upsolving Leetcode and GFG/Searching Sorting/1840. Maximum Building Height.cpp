#include <bits/stdc++.h>
using namespace std;

class Solution
{
private:
    /*
     * PROBLEM UNDERSTANDING:
     * - n buildings labeled 1 to n
     * - Height constraints:
     *   1. All heights must be non-negative integers
     *   2. Building 1 must have height 0
     *   3. Adjacent buildings can differ in height by at most 1
     *   4. Some buildings have explicit max height restrictions
     * - Goal: maximize the height of the tallest building
     *
     * KEY INSIGHT - Three-Pass Approach:
     *
     * OBSERVATION 1: Constraint Propagation
     * - A restricted building at position p with max height h limits its neighbors
     * - Building at position q can have max height: h + |p - q| (triangle constraint)
     * - This propagates both leftward and rightward
     *
     * OBSERVATION 2: Peak Between Two Restrictions
     * - Between two restricted buildings L and R with heights hL and hR:
     *   - Left side rises at most 1 per step: height at pos x ≤ hL + (x - L)
     *   - Right side rises at most 1 per step: height at pos x ≤ hR + (R - x)
     * - Maximum peak between them:
     *   peak = (hL + hR + distance) / 2
     *   where distance = R - L
     *
     * VISUAL INTUITION:
     *
     *         peak
     *        /    \
     *       /      \
     * hL --/        \-- hR
     *  L              R
     *
     * Rise from left: peak = hL + d1
     * Rise from right: peak = hR + d2
     * Total: d1 + d2 = R - L = distance
     * So: 2*peak = hL + hR + distance
     *     peak = (hL + hR + distance) / 2
     *
     * APPROACH:
     * 1. Add boundary anchors: (1, 0) and (n, n-1) if no restriction on n
     * 2. Sort restrictions by building id
     * 3. Left-to-right pass: propagate constraints forward
     *    - restrict[i].maxH = min(restrict[i].maxH, restrict[i-1].maxH + distance)
     * 4. Right-to-left pass: propagate constraints backward
     *    - restrict[i].maxH = min(restrict[i].maxH, restrict[i+1].maxH + distance)
     * 5. For each adjacent pair of restrictions, compute the peak
     *
     * EXAMPLE: n = 10, restrictions = [[5,3],[2,5],[7,4],[10,3]]
     *
     * After adding anchors and sorting:
     * [(1,0), (2,5), (5,3), (7,4), (10,3)]
     *
     * Left-to-right pass (restrict forward propagation):
     * (1,0): unchanged
     * (2,5): min(5, 0+1) = 1
     * (5,3): min(3, 1+3) = 3
     * (7,4): min(4, 3+2) = 4 (wait: 3+2=5 > 4, so stays 4)
     *         Actually: min(4, 3+2) = min(4,5) = 4 ✓
     * (10,3): min(3, 4+3) = 3
     *
     * After L→R: [(1,0), (2,1), (5,3), (7,4), (10,3)]
     *
     * Right-to-left pass:
     * (10,3): unchanged
     * (7,4): min(4, 3+3) = 4 ✓
     * (5,3): min(3, 4+2) = 3 ✓
     * (2,1): min(1, 3+3) = 1 ✓
     * (1,0): min(0, 1+1) = 0 ✓
     *
     * Compute peaks:
     * Between (1,0) and (2,1): (0+1+1)/2 = 1
     * Between (2,1) and (5,3): (1+3+3)/2 = 3
     * Between (5,3) and (7,4): (3+4+2)/2 = 4
     * Between (7,4) and (10,3): (4+3+3)/2 = 5 ← maximum!
     *
     * Answer: 5 ✓
     *
     * TIME:  O(k log k) — sorting dominates (k = restrictions.size())
     * SPACE: O(1) — sorts in-place, only adds 2 entries
     */

    /**
     * Propagates constraints left-to-right
     * Each restriction is tightened by its left neighbor's constraint:
     *   maxHeight[i] = min(maxHeight[i], maxHeight[i-1] + distance)
     *
     * @param restrictions - sorted restriction list (modified in-place)
     */
    void propagateLeftToRight(vector<vector<int>> &restrictions)
    {
        int k = restrictions.size();
        for (int i = 1; i < k; i++)
        {
            int distance = restrictions[i][0] - restrictions[i - 1][0];
            restrictions[i][1] = min(restrictions[i][1],
                                     restrictions[i - 1][1] + distance);
        }
    }

    /**
     * Propagates constraints right-to-left
     * Each restriction is tightened by its right neighbor's constraint:
     *   maxHeight[i] = min(maxHeight[i], maxHeight[i+1] + distance)
     *
     * @param restrictions - sorted restriction list (modified in-place)
     */
    void propagateRightToLeft(vector<vector<int>> &restrictions)
    {
        int k = restrictions.size();
        for (int i = k - 2; i >= 0; i--)
        {
            int distance = restrictions[i + 1][0] - restrictions[i][0];
            restrictions[i][1] = min(restrictions[i][1],
                                     restrictions[i + 1][1] + distance);
        }
    }

    /**
     * Finds the tallest possible peak between adjacent restriction pairs
     *
     * For restrictions L (pos, hL) and R (pos, hR) with gap = R.pos - L.pos:
     *   peak = (hL + hR + gap) / 2
     *
     * This comes from: peak rises from both sides simultaneously,
     * so total rise = hL + hR + gap must cover both climbs.
     *
     * @param restrictions - fully propagated restriction list
     * @return maximum achievable peak height
     */
    long long computeMaxPeak(const vector<vector<int>> &restrictions)
    {
        long long maxPeak = 0;
        int k = restrictions.size();

        for (int i = 1; i < k; i++)
        {
            long long gap = restrictions[i][0] - restrictions[i - 1][0];
            long long leftHeight = restrictions[i - 1][1];
            long long rightHeight = restrictions[i][1];

            // Peak between two restricted points rises from both sides
            long long peak = (leftHeight + rightHeight + gap) / 2;
            maxPeak = max(maxPeak, peak);
        }

        return maxPeak;
    }

public:
    int maxBuilding(int n, vector<vector<int>> &restrictions)
    {
        // Step 1: Add boundary anchors
        // Building 1 is always 0 (problem constraint)
        restrictions.push_back({1, 0});

        // If building n has no restriction, it can rise as high as (n-1)
        // (starting from 0 at building 1, rising by 1 each step)
        if (restrictions.empty() || restrictions.back()[0] != n)
        {
            restrictions.push_back({n, n - 1});
        }

        // Step 2: Sort by building id
        sort(restrictions.begin(), restrictions.end());

        // Step 3: Propagate constraints in both directions
        propagateLeftToRight(restrictions);
        propagateRightToLeft(restrictions);

        // Step 4: Find maximum peak between each adjacent restriction pair
        return computeMaxPeak(restrictions);
    }
};

/*
 * DETAILED WALKTHROUGH - Example 1: n = 5, restrictions = [[2,1],[4,1]]
 *
 * ===== STEP 1: Add Anchors and Sort =====
 *
 * Add (1,0) and (5,4) [since n=5 has no restriction]:
 * → [(2,1), (4,1), (1,0), (5,4)]
 *
 * Sorted:
 * → [(1,0), (2,1), (4,1), (5,4)]
 *
 * ===== STEP 2: Left-to-Right Pass =====
 *
 * (1,0) → unchanged
 * (2,1) → min(1, 0+1) = min(1,1) = 1
 * (4,1) → min(1, 1+2) = min(1,3) = 1
 * (5,4) → min(4, 1+1) = min(4,2) = 2
 *
 * After L→R: [(1,0), (2,1), (4,1), (5,2)]
 *
 * ===== STEP 3: Right-to-Left Pass =====
 *
 * (5,2) → unchanged
 * (4,1) → min(1, 2+1) = min(1,3) = 1
 * (2,1) → min(1, 1+2) = min(1,3) = 1
 * (1,0) → min(0, 1+1) = min(0,2) = 0
 *
 * After R→L: [(1,0), (2,1), (4,1), (5,2)]
 *
 * ===== STEP 4: Compute Peaks =====
 *
 * Between (1,0) and (2,1):
 *   gap=1, peak = (0+1+1)/2 = 1
 *
 * Between (2,1) and (4,1):
 *   gap=2, peak = (1+1+2)/2 = 2 ← maximum!
 *
 *   Visualization:
 *       2
 *      / \
 *     1   1
 *     2   4
 *
 * Between (4,1) and (5,2):
 *   gap=1, peak = (1+2+1)/2 = 2
 *
 * Answer: 2 ✓
 *
 * ===================================================================
 *
 * CONSTRAINT PROPAGATION PROOF:
 *
 * WHY LEFT-TO-RIGHT?
 * If building L has max height hL and building R (L < R) has max height hR,
 * then: hR ≤ hL + (R - L)
 * Because you can only rise by 1 per step between L and R.
 *
 * WHY BOTH DIRECTIONS?
 * - L→R: ensures each restriction is not too tall given left constraints
 * - R→L: ensures each restriction is not too tall given right constraints
 * - Both together: each restriction is globally feasible
 *
 * PEAK FORMULA DERIVATION:
 * Between positions L (height hL) and R (height hR), gap = R - L
 * Let peak be at position P:
 *   Rise from left:  peak_h = hL + (P - L)
 *   Rise from right: peak_h = hR + (R - P)
 *
 * Set equal:
 *   hL + (P - L) = hR + (R - P)
 *   2P = hR - hL + R + L
 *
 * Peak height:
 *   peak_h = hL + P - L
 *           = hL + (hR - hL + R + L)/2 - L
 *           = (hL + hR + R - L) / 2
 *           = (hL + hR + gap) / 2  ✓
 */

int main()
{
    return 0;
}