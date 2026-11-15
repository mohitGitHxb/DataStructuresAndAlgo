#include <bits/stdc++.h>
using namespace std;
class Solution
{
private:
    /*
     * PROBLEM UNDERSTANDING:
     * - Robots at positions with bullets that can travel distance[i]
     * - Each robot fires ONE bullet, either left OR right
     * - Bullet destroys all walls in range but stops at other robots
     * - Goal: Maximum unique walls destroyed
     *
     * KEY INSIGHT - Dynamic Programming with Constraint Handling:
     *
     * OBSERVATION 1: Robot Ordering Matters
     * - Sort robots by position (left to right)
     * - A robot's bullet can't pass through robots to its left/right
     * - This creates range constraints for each robot
     *
     * OBSERVATION 2: Previous Direction Affects Current Range
     * - If previous robot shot RIGHT, it blocks current robot's LEFT shot 
     * - Current robot's left range must start AFTER previous robot's right end
     *
     * OBSERVATION 3: Each Robot Has Two Choices
     * - Shoot left: destroy walls in left range
     * - Shoot right: destroy walls in right range
     * - DP explores both choices
     *
     * APPROACH:
     * 1. Sort robots by position
     * 2. For each robot, calculate valid shooting ranges:
     *    - Left range: [max(pos - dist, leftLimit), pos]
     *    - Right range: [pos, min(pos + dist, rightLimit)]
     *    - Limits prevent bullets from crossing other robots
     * 3. Use DP: for each robot, try both directions
     * 4. Track previous direction to adjust constraints
     *
     * STATE: dp[i][prevDir] = max walls destroyed from robot i onward
     *        prevDir: 0=left, 1=right (direction previous robot shot)
     *
     * EXAMPLE: robots=[10,2], distance=[5,1], walls=[5,2,7]
     *
     * After sorting: robots=[2,10], distance=[1,5]
     *
     * Robot 0 at pos=2, dist=1:
     *   Left range: [1, 2] → can hit wall at 2
     *   Right range: [2, 9] (blocked by robot at 10)
     *
     * Robot 1 at pos=10, dist=5:
     *   Left range: [5, 10] → can hit walls at 5, 7
     *   Right range: [10, ∞]
     *
     * Optimal: Robot 0 shoots left (hits 2), Robot 1 shoots left (hits 5,7)
     * Total: 3 walls ✓
     *
     * TIME: O(n*log(w) + n*log(n) + w*log(w))
     * SPACE: O(n) for DP table
     */

    using RobotInfo = pair<int, int>; // {position, distance}
    using Range = pair<int, int>;     // {leftBound, rightBound}

    // DP table: dp[robotIndex][previousDirection]
    // previousDirection: 0=left, 1=right
    vector<vector<int>> dp;

    /**
     * Counts walls in a given range using binary search
     *
     * @param walls - sorted array of wall positions
     * @param leftBound - start of range (inclusive)
     * @param rightBound - end of range (inclusive)
     * @return number of walls in [leftBound, rightBound]
     */
    int countWallsInRange(const vector<int> &walls, int leftBound, int rightBound)
    {
        // Find first wall >= leftBound
        auto leftIter = lower_bound(walls.begin(), walls.end(), leftBound);

        // Find first wall > rightBound
        auto rightIter = upper_bound(walls.begin(), walls.end(), rightBound);

        // Count = difference in positions
        return rightIter - leftIter;
    }

    /**
     * Calculates valid shooting ranges for each robot
     * Ranges are constrained by adjacent robots (bullets can't pass through)
     *
     * @param sortedRobots - robots sorted by position
     * @return vector of {leftRange, rightRange} for each robot
     */
    vector<Range> calculateShootingRanges(const vector<RobotInfo> &sortedRobots)
    {
        int n = sortedRobots.size();
        vector<Range> ranges(n);

        for (int i = 0; i < n; i++)
        {
            int position = sortedRobots[i].first;
            int maxDistance = sortedRobots[i].second;

            // Left boundary: can't shoot past previous robot
            int leftLimit = (i == 0) ? 1 : sortedRobots[i - 1].first + 1;

            // Right boundary: can't shoot past next robot
            int rightLimit = (i == n - 1) ? 1e9 : sortedRobots[i + 1].first - 1;

            // Actual range considering distance constraint
            int leftBound = max(position - maxDistance, leftLimit);
            int rightBound = min(position + maxDistance, rightLimit);

            ranges[i] = {leftBound, rightBound};
        }

        return ranges;
    }

    /**
     * Recursive DP to find maximum walls destroyed
     *
     * @param walls - sorted array of wall positions
     * @param sortedRobots - robots sorted by position
     * @param ranges - valid shooting ranges for each robot
     * @param robotIndex - current robot being considered
     * @param prevDirection - direction previous robot shot (0=left, 1=right)
     * @return maximum walls that can be destroyed from this robot onward
     */
    int solveDP(const vector<int> &walls,
                const vector<RobotInfo> &sortedRobots,
                const vector<Range> &ranges,
                int robotIndex,
                int prevDirection)
    {
        // Base case: processed all robots
        if (robotIndex == sortedRobots.size())
        {
            return 0;
        }

        // Return memoized result
        if (dp[robotIndex][prevDirection] != -1)
        {
            return dp[robotIndex][prevDirection];
        }

        int robotPosition = sortedRobots[robotIndex].first;
        int leftRangeStart = ranges[robotIndex].first;
        int rightRangeEnd = ranges[robotIndex].second;

        // CONSTRAINT: If previous robot shot right, it blocks current robot's left shot
        // Current robot's left shot must start AFTER previous robot's right end
        if (prevDirection == 1 && robotIndex > 0)
        {
            // Previous robot shot right, ending at ranges[robotIndex-1].second
            // Current robot's left shot must start after that
            leftRangeStart = max(leftRangeStart, ranges[robotIndex - 1].second + 1);
        }

        // CHOICE 1: Shoot left
        // Count walls in [leftRangeStart, robotPosition]
        int wallsIfShootLeft = countWallsInRange(walls, leftRangeStart, robotPosition) + solveDP(walls, sortedRobots, ranges, robotIndex + 1, 0);

        // CHOICE 2: Shoot right
        // Count walls in [robotPosition, rightRangeEnd]
        int wallsIfShootRight = countWallsInRange(walls, robotPosition, rightRangeEnd) + solveDP(walls, sortedRobots, ranges, robotIndex + 1, 1);

        // Store and return best choice
        return dp[robotIndex][prevDirection] = max(wallsIfShootLeft, wallsIfShootRight);
    }

public:
    int maxWalls(vector<int> &robots, vector<int> &distance, vector<int> &walls)
    {
        int n = robots.size();

        // Combine robot positions with their distances
        vector<RobotInfo> robotsWithDistance(n);
        for (int i = 0; i < n; i++)
        {
            robotsWithDistance[i] = {robots[i], distance[i]};
        }

        // Sort robots by position (left to right)
        sort(robotsWithDistance.begin(), robotsWithDistance.end());

        // Sort walls for binary search
        sort(walls.begin(), walls.end());

        // Calculate valid shooting ranges for each robot
        vector<Range> shootingRanges = calculateShootingRanges(robotsWithDistance);

        // Initialize DP table: dp[robotIndex][previousDirection]
        dp.assign(n + 1, vector<int>(2, -1));

        // Start DP from first robot with no previous direction constraint
        // prevDirection=0 (left) is used as initial state (doesn't affect first robot)
        return solveDP(walls, robotsWithDistance, shootingRanges, 0, 0);
    }
};

/*
 * DETAILED WALKTHROUGH - Example 2: robots=[10,2], distance=[5,1], walls=[5,2,7]
 *
 * ===== STEP 1: Sort and Prepare =====
 *
 * After sorting robots by position:
 *   Robot 0: position=2, distance=1
 *   Robot 1: position=10, distance=5
 *
 * Sorted walls: [2, 5, 7]
 *
 * ===== STEP 2: Calculate Shooting Ranges =====
 *
 * Robot 0 (pos=2, dist=1):
 *   leftLimit = 1 (no robot to the left)
 *   rightLimit = 10 - 1 = 9 (robot 1 is at 10)
 *   leftBound = max(2-1, 1) = 1
 *   rightBound = min(2+1, 9) = 3
 *   Range: [1, 3]
 *
 * Robot 1 (pos=10, dist=5):
 *   leftLimit = 2 + 1 = 3 (robot 0 is at 2)
 *   rightLimit = 1e9 (no robot to the right)
 *   leftBound = max(10-5, 3) = 5
 *   rightBound = min(10+5, 1e9) = 15
 *   Range: [5, 15]
 *
 * ===== STEP 3: DP Execution =====
 *
 * Call: solveDP(walls, robots, ranges, 0, 0)
 *
 * --- Robot 0, prevDirection=0 (left) ---
 *
 * leftRangeStart = 1 (no adjustment needed since prev shot left)
 *
 * Choice 1: Shoot left
 *   Range: [1, 2]
 *   Walls in range: binary search finds wall at position 2
 *   Count: 1 wall
 *   Recursive call: solveDP(..., 1, 0) [next robot, prev=left]
 *
 * Choice 2: Shoot right
 *   Range: [2, 3]
 *   Walls in range: binary search finds wall at position 2
 *   Count: 1 wall
 *   Recursive call: solveDP(..., 1, 1) [next robot, prev=right]
 *
 * --- Robot 1, prevDirection=0 (Robot 0 shot left) ---
 *
 * leftRangeStart = 5 (no adjustment, previous robot shot left)
 *
 * Choice 1: Shoot left
 *   Range: [5, 10]
 *   Walls in range: binary search finds walls at 5, 7
 *   Count: 2 walls
 *   Recursive: base case, return 0
 *   Total: 2
 *
 * Choice 2: Shoot right
 *   Range: [10, 15]
 *   Walls in range: none
 *   Count: 0
 *   Total: 0
 *
 * Best for Robot 1 (prev=left): max(2, 0) = 2
 *
 * --- Robot 1, prevDirection=1 (Robot 0 shot right) ---
 *
 * leftRangeStart = max(5, ranges[0].second + 1) = max(5, 3+1) = 5
 * (Previous robot shot right up to position 3, so left shot still valid from 5)
 *
 * Same calculations as above: best = 2
 *
 * --- Back to Robot 0 ---
 *
 * Shoot left: 1 + 2 = 3 ✓
 * Shoot right: 1 + 2 = 3 ✓
 *
 * Final answer: 3
 *
 * ===================================================================
 *
 * DETAILED WALKTHROUGH - Example 3: robots=[1,2], distance=[100,1], walls=[10]
 *
 * After sorting: Robot 0 (pos=1, dist=100), Robot 1 (pos=2, dist=1)
 *
 * Ranges:
 *   Robot 0: [1, 1] (right is limited by robot 1 at position 2)
 *   Robot 1: [2, 3]
 *
 * Robot 0 can shoot:
 *   Left: range [1, 1] → no walls
 *   Right: range [1, 1] → no walls (blocked by robot 1 immediately)
 *
 * Robot 1 can shoot:
 *   Left: range [2, 2] → no walls
 *   Right: range [2, 3] → no walls
 *
 * Answer: 0 ✓
 *
 * ===================================================================
 *
 * WHY THIS WORKS - Algorithm Correctness:
 *
 * 1. SORTING ROBOTS:
 *    - Processing left-to-right ensures we handle blocking correctly
 *    - Each robot's range is constrained by neighbors
 *
 * 2. RANGE CALCULATION:
 *    - leftLimit/rightLimit prevent bullets crossing robots
 *    - Accounts for physical constraints of the problem
 *
 * 3. PREVIOUS DIRECTION CONSTRAINT:
 *    - If robot i shoots right, its bullet ends at ranges[i].second
 *    - Robot i+1's left shot must start AFTER ranges[i].second
 *    - This prevents double-counting walls
 *
 * 4. BINARY SEARCH FOR WALLS:
 *    - O(log w) per query instead of O(w)
 *    - Critical for efficiency with many walls
 *
 * 5. DP MEMOIZATION:
 *    - Avoids recomputing same subproblems
 *    - State space: n robots × 2 directions = O(n)
 *
 * COMPLEXITY ANALYSIS:
 * - Sorting robots: O(n log n)
 * - Sorting walls: O(w log w)
 * - Range calculation: O(n)
 * - DP: O(n) states × O(log w) per state = O(n log w)
 * - Total: O(n log n + w log w + n log w)
 * - Space: O(n) for DP table
 */

int main()
{
    return 0;
}