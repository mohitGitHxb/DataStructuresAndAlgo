#include <bits/stdc++.h>
using namespace std;
class Solution
{
private:
    /*
     * PROBLEM UNDERSTANDING:
     * - Robots at various positions need repair
     * - Factories at positions with capacity limits
     * - Each robot travels to exactly one factory
     * - Goal: Minimize total distance traveled by all robots
     *
     * KEY INSIGHT - Assignment Problem with DP:
     *
     * OBSERVATION 1: Greedy Sorting
     * - Sort both robots and factories by position
     * - Optimal assignment tends to match nearby robots to nearby factories
     * - This reduces crossing paths and backtracking
     *
     * OBSERVATION 2: Factory Expansion
     * - Factory at position P with limit L is equivalent to L separate slots at position P
     * - Example: factory=[5, 3] → three positions: [5, 5, 5]
     * - This simplifies problem to 1-to-1 assignment
     *
     * OBSERVATION 3: DP State
     * - dp[i][j] = minimum distance to assign robots[i..n-1] to factory_slots[j..m-1]
     * - For each robot, either assign to current slot or skip slot
     *
     * APPROACH:
     * 1. Sort robots and factories by position
     * 2. Expand factories into individual slots
     * 3. Use DP: for each robot, try assigning to each available slot
     * 4. Take minimum across all valid assignments
     *
     * EXAMPLE: robots=[0,4,6], factories=[[2,2],[6,2]]
     *
     * After sorting: robots=[0,4,6], factories=[[2,2],[6,2]]
     * Expanded slots: [2,2,6,6] (two slots at pos 2, two at pos 6)
     *
     * Optimal assignment:
     * - Robot 0 → slot 2: distance = |0-2| = 2
     * - Robot 4 → slot 2: distance = |4-2| = 2
     * - Robot 6 → slot 6: distance = |6-6| = 0
     * Total: 4 ✓
     *
     * STATE TRANSITIONS:
     * For robot i and slot j:
     * - ASSIGN: distance = |robots[i] - slots[j]| + dp[i+1][j+1]
     * - SKIP: dp[i][j+1] (skip this slot, try next one)
     * - Take minimum
     *
     * BASE CASES:
     * - All robots assigned (i >= n): cost = 0
     * - No slots left but robots remain (j >= m): cost = ∞ (invalid)
     *
     * TIME: O(n × m) where n=robots, m=total factory capacity
     * SPACE: O(n × m)
     */

    using ll = long long;

    // DP table: dp[robotIndex][slotIndex]
    vector<vector<ll>> dp;

    // Sentinel value for invalid/impossible states
    static constexpr ll IMPOSSIBLE = 1e18;

    /**
     * Recursive DP to find minimum total distance
     *
     * @param robotIndex - current robot being assigned
     * @param slotIndex - current factory slot being considered
     * @param robots - sorted array of robot positions
     * @param factorySlots - expanded array of factory slot positions
     * @return minimum distance to assign robots[robotIndex..n-1] to slots[slotIndex..m-1]
     */
    ll solveDP(int robotIndex,
               int slotIndex,
               const vector<int> &robots,
               const vector<int> &factorySlots)
    {
        // Base case 1: All robots assigned successfully
        if (robotIndex >= robots.size())
        {
            return 0;
        }

        // Base case 2: No more slots available but robots remain
        if (slotIndex >= factorySlots.size())
        {
            return IMPOSSIBLE; // Invalid assignment
        }

        // Return memoized result
        if (dp[robotIndex][slotIndex] != -1)
        {
            return dp[robotIndex][slotIndex];
        }

        // CHOICE 1: Assign current robot to current slot
        ll distanceIfAssign = abs(robots[robotIndex] - factorySlots[slotIndex]) +
                              solveDP(robotIndex + 1, slotIndex + 1, robots, factorySlots);

        // CHOICE 2: Skip current slot, try next slot for same robot
        ll distanceIfSkip = solveDP(robotIndex, slotIndex + 1, robots, factorySlots);

        // Take minimum of both choices
        return dp[robotIndex][slotIndex] = min(distanceIfAssign, distanceIfSkip);
    }

    /**
     * Expands factories into individual repair slots
     * Each factory with limit L becomes L slots at the same position
     *
     * @param factories - sorted array of [position, limit] pairs
     * @return flat array of slot positions
     */
    vector<int> expandFactorySlots(const vector<vector<int>> &factories)
    {
        vector<int> slots;

        for (const auto &factory : factories)
        {
            int position = factory[0];
            int capacity = factory[1];

            // Add 'capacity' slots at 'position'
            for (int i = 0; i < capacity; i++)
            {
                slots.push_back(position);
            }
        }

        return slots;
    }

public:
    long long minimumTotalDistance(vector<int> &robots, vector<vector<int>> &factories)
    {
        // Sort robots and factories by position
        sort(robots.begin(), robots.end());
        sort(factories.begin(), factories.end());

        // Expand factories into individual slots
        vector<int> factorySlots = expandFactorySlots(factories);

        // Initialize DP table
        int numRobots = robots.size();
        int numSlots = factorySlots.size();
        dp.assign(numRobots + 1, vector<ll>(numSlots + 1, -1));

        // Solve using DP
        return solveDP(0, 0, robots, factorySlots);
    }
};

/*
 * DETAILED WALKTHROUGH - Example 1: robots=[0,4,6], factories=[[2,2],[6,2]]
 *
 * ===== STEP 1: Sort and Expand =====
 *
 * Sorted robots: [0, 4, 6]
 * Sorted factories: [[2,2], [6,2]]
 *
 * Expand factories:
 *   Factory [2,2]: position=2, limit=2 → slots [2, 2]
 *   Factory [6,2]: position=6, limit=2 → slots [6, 6]
 *
 * Factory slots: [2, 2, 6, 6]
 *
 * ===== STEP 2: DP Execution =====
 *
 * Call: solveDP(0, 0, [0,4,6], [2,2,6,6])
 *
 * --- Robot 0 (pos=0), Slot 0 (pos=2) ---
 *
 * Choice 1: Assign robot 0 to slot 0
 *   Distance: |0-2| = 2
 *   Recurse: solveDP(1, 1, ...) [robot 1, slot 1]
 *
 * Choice 2: Skip slot 0
 *   Recurse: solveDP(0, 1, ...) [robot 0, slot 1]
 *
 * Let's explore Choice 1:
 *
 * --- Robot 1 (pos=4), Slot 1 (pos=2) ---
 * Call: solveDP(1, 1, ...)
 *
 * Choice 1: Assign robot 1 to slot 1
 *   Distance: |4-2| = 2
 *   Recurse: solveDP(2, 2, ...) [robot 2, slot 2]
 *
 * Choice 2: Skip slot 1
 *   Recurse: solveDP(1, 2, ...) [robot 1, slot 2]
 *
 * Exploring Choice 1:
 *
 * --- Robot 2 (pos=6), Slot 2 (pos=6) ---
 * Call: solveDP(2, 2, ...)
 *
 * Choice 1: Assign robot 2 to slot 2
 *   Distance: |6-6| = 0
 *   Recurse: solveDP(3, 3, ...) [all robots assigned]
 *   Base case: return 0
 *   Total from this choice: 0
 *
 * Choice 2: Skip slot 2
 *   Recurse: solveDP(2, 3, ...) [robot 2, slot 3]
 *   Robot 2 to slot 3 (pos=6): |6-6| = 0
 *   Also returns 0
 *
 * Both choices same: return 0
 *
 * --- Backtrack to Robot 1 ---
 *
 * Choice 1 result: 2 + 0 = 2
 *
 * Now explore Choice 2 (skip slot 1):
 *
 * --- Robot 1 (pos=4), Slot 2 (pos=6) ---
 * Call: solveDP(1, 2, ...)
 *
 * Choice 1: Assign robot 1 to slot 2
 *   Distance: |4-6| = 2
 *   Recurse: solveDP(2, 3, ...)
 *   Robot 2 to slot 3: |6-6| = 0
 *   Total: 2
 *
 * So skipping slot 1 also gives 2
 *
 * --- Backtrack to Robot 0 ---
 *
 * Choice 1 (assign to slot 0): 2 + 2 = 4 ✓
 *
 * Choice 2 (skip slot 0, try slot 1):
 *   Robot 0 to slot 1 (pos=2): |0-2| = 2
 *   Recurse: solveDP(1, 2, ...)
 *   From above, this gives 2
 *   Total: 2 + 2 = 4
 *
 * Both paths give 4
 *
 * Final answer: 4 ✓
 *
 * ===================================================================
 *
 * DETAILED WALKTHROUGH - Example 2: robots=[1,-1], factories=[[-2,1],[2,1]]
 *
 * ===== STEP 1: Sort and Expand =====
 *
 * Sorted robots: [-1, 1]
 * Sorted factories: [[-2,1], [2,1]]
 *
 * Expand factories:
 *   Factory [-2,1]: slot at position -2
 *   Factory [2,1]: slot at position 2
 *
 * Factory slots: [-2, 2]
 *
 * ===== STEP 2: DP Execution =====
 *
 * --- Robot 0 (pos=-1), Slot 0 (pos=-2) ---
 *
 * Choice 1: Assign robot 0 to slot 0
 *   Distance: |-1-(-2)| = 1
 *   Robot 1 to slot 1: |1-2| = 1
 *   Total: 1 + 1 = 2 ✓
 *
 * Choice 2: Skip slot 0
 *   Robot 0 to slot 1 (pos=2): |-1-2| = 3
 *   No slots left for robot 1
 *   Invalid
 *
 * Answer: 2 ✓
 *
 * ===================================================================
 *
 * WHY THIS WORKS - Algorithm Correctness:
 *
 * 1. SORTING OPTIMALITY:
 *    - Optimal assignment never has "crossings" when both sorted
 *    - If robot i goes to slot j and robot i+1 goes to slot j-1,
 *      we could swap and reduce distance (by triangle inequality)
 *    - Sorting enables greedy-like consideration of nearby pairs
 *
 * 2. FACTORY EXPANSION:
 *    - Transforms multi-capacity problem into 1-to-1 assignment
 *    - Preserves all valid assignments
 *    - Simplifies DP state representation
 *
 * 3. DP STATE SUFFICIENCY:
 *    - Only need to track: which robot, which slot
 *    - Past assignments don't affect future costs
 *    - Optimal substructure holds
 *
 * 4. SKIP CHOICE NECESSITY:
 *    - Not every slot must be used
 *    - Skipping allows finding best match for each robot
 *    - Example: might skip nearby slot for better overall assignment
 *
 * 5. BASE CASES:
 *    - All robots assigned → cost 0 (valid)
 *    - Robots left but no slots → impossible (return large value)
 *    - Min operation filters out impossible paths
 *
 * COMPLEXITY ANALYSIS:
 * - Sorting: O(n log n + f log f) where f = number of factories
 * - Expansion: O(total capacity) = O(m)
 * - DP states: O(n × m)
 * - Per state: O(1)
 * - Total: O(n log n + f log f + n × m)
 * - Space: O(n × m) for DP table
 *
 * EDGE CASES:
 * - Single robot, single factory: distance = |robot - factory|
 * - Robot at factory position: distance = 0
 * - More slots than robots: some slots unused (valid)
 * - Exact match (n robots, n slots): each robot to one slot
 */
int main()
{
    return 0;
}