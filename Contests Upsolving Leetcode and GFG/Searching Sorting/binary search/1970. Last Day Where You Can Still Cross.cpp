#include <bits/stdc++.h>
using namespace std;
class Solution
{
private:
    /*
     * PROBLEM UNDERSTANDING:
     * - Grid starts as all land (0), cells become water (1) over time
     * - cells[i] = [row, col] means on day i, that cell floods
     * - Goal: Find the LAST day we can walk from top row to bottom row on land
     *
     * KEY INSIGHT - Binary Search on Days:
     *
     * MONOTONICITY: If we can't cross on day X, we can't cross on day X+1 either
     * (more water = harder to cross)
     *
     * This creates a pattern:
     * Day 0: Can cross ✓
     * Day 1: Can cross ✓
     * Day 2: Can cross ✓
     * Day 3: Cannot cross ✗
     * Day 4: Cannot cross ✗
     * ...
     *
     * We're looking for the LAST ✓ before the first ✗
     * → Perfect use case for binary search!
     *
     * APPROACH:
     * 1. Binary search on day number (0 to n-1)
     * 2. For each candidate day, simulate flooding up to that day
     * 3. Use BFS to check if path exists from top to bottom
     * 4. If path exists → try later day (search right)
     * 5. If no path → try earlier day (search left)
     *
     * EXAMPLE: row=2, col=2, cells=[[1,1],[2,1],[1,2],[2,2]]
     *
     * Day 0: Flood cell [1,1]
     * Grid:  [1, 0]    Can cross? YES (top-right to bottom-right)
     *        [0, 0]
     *
     * Day 1: Flood cell [2,1]
     * Grid:  [1, 0]    Can cross? YES (top-right to bottom-right)
     *        [1, 0]
     *
     * Day 2: Flood cell [1,2]
     * Grid:  [1, 1]    Can cross? NO (both top cells flooded)
     *        [1, 0]
     *
     * Answer: Last day we can cross = Day 1
     * But problem asks for "day number" starting from 1, so return 2
     *
     * TIME: O(n * row * col * log n) where n = cells.size()
     *       - Binary search: O(log n)
     *       - Each check: O(row * col) for BFS
     * SPACE: O(row * col) for grid and BFS queue
     */

    // Direction vectors for 4-directional movement (up, down, left, right)
    const int DIRECTIONS[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    /**
     * Checks if a path exists from top row to bottom row on given day
     * Simulates flooding up to the specified day, then runs BFS
     *
     * @param day - which day to simulate (0-indexed)
     * @param cells - list of cells that flood each day
     * @param numRows - number of rows in grid
     * @param numCols - number of columns in grid
     * @return true if we can walk from top to bottom on this day
     */
    bool canCrossOnDay(int day, const vector<vector<int>> &cells,
                       int numRows, int numCols)
    {
        // Build grid state after 'day' days of flooding
        // 0 = land (walkable), 1 = water (blocked)
        vector<vector<int>> grid(numRows, vector<int>(numCols, 0));

        // Flood all cells from day 0 to day 'day' (inclusive)
        for (int i = 0; i <= day; i++)
        {
            int row = cells[i][0] - 1; // Convert to 0-indexed
            int col = cells[i][1] - 1;
            grid[row][col] = 1; // Mark as water
        }

        // BFS from all land cells in the top row
        queue<pair<int, int>> bfsQueue;

        // Initialize: Add all accessible cells in top row
        for (int col = 0; col < numCols; col++)
        {
            if (grid[0][col] == 0)
            { // If land
                bfsQueue.push({0, col});
                grid[0][col] = 1; // Mark as visited (reuse grid for visited array)
            }
        }

        // BFS to find path to bottom row
        while (!bfsQueue.empty())
        {
            auto [currentRow, currentCol] = bfsQueue.front();
            bfsQueue.pop();

            // Success: Reached bottom row!
            if (currentRow == numRows - 1)
            {
                return true;
            }

            // Explore all 4 directions
            for (int dir = 0; dir < 4; dir++)
            {
                int newRow = currentRow + DIRECTIONS[dir][0];
                int newCol = currentCol + DIRECTIONS[dir][1];

                // Check if new position is valid and is land (not visited)
                if (newRow >= 0 && newRow < numRows &&
                    newCol >= 0 && newCol < numCols &&
                    grid[newRow][newCol] == 0)
                {

                    bfsQueue.push({newRow, newCol});
                    grid[newRow][newCol] = 1; // Mark as visited
                }
            }
        }

        // Couldn't reach bottom row
        return false;
    }

public:
    int latestDayToCross(int row, int col, vector<vector<int>> &cells)
    {
        int totalDays = cells.size();

        // Binary search on day index (0-indexed)
        int left = 0;
        int right = totalDays - 1;
        int latestDay = -1; // Latest day we can cross (0-indexed)

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (canCrossOnDay(mid, cells, row, col))
            {
                // We can cross on day 'mid' → try to find a later day
                latestDay = mid;
                left = mid + 1;
            }
            else
            {
                // Cannot cross on day 'mid' → try earlier days
                right = mid - 1;
            }
        }

        // Convert from 0-indexed to 1-indexed day number
        // latestDay is the index in cells array (0-indexed)
        // Answer is "day number" which is 1-indexed
        return latestDay + 1;
    }
};

/*
 * DETAILED WALKTHROUGH - Example 2: row=2, col=2, cells=[[1,1],[1,2],[2,1],[2,2]]
 *
 * We're searching for latest day (0-indexed) we can cross
 * Total days = 4 (indices 0, 1, 2, 3)
 *
 * ===== Binary Search Process =====
 *
 * Initial: left=0, right=3
 *
 * --- Iteration 1 ---
 * mid = 0 + (3-0)/2 = 1
 * Check day 1: Flood cells [1,1] and [1,2]
 * Grid after day 1:
 *   [1, 1]  ← Both top cells flooded!
 *   [0, 0]
 * BFS: Cannot start from top row (all water)
 * Result: CANNOT cross ✗
 * Update: right = 0
 *
 * --- Iteration 2 ---
 * left=0, right=0
 * mid = 0 + (0-0)/2 = 0
 * Check day 0: Flood cell [1,1] only
 * Grid after day 0:
 *   [1, 0]  ← Can start from (0,1)
 *   [0, 0]
 * BFS path: (0,1) → (1,1) → reached bottom!
 * Result: CAN cross ✓
 * Update: latestDay = 0, left = 1
 *
 * --- Exit ---
 * left=1 > right=0 → exit loop
 * latestDay = 0 (0-indexed)
 * Return: 0 + 1 = 1 ✓
 *
 * ===================================================================
 *
 * DETAILED WALKTHROUGH - Example 3: cells=[[1,2],[2,1],[3,3],[2,2],...]
 * row=3, col=3, totalDays=9
 *
 * Visual progression:
 *
 * Day 0: Flood [1,2]        Day 1: Flood [2,1]        Day 2: Flood [3,3]
 *   [0, 1, 0]                 [0, 1, 0]                 [0, 1, 0]
 *   [0, 0, 0]                 [1, 0, 0]                 [1, 0, 0]
 *   [0, 0, 0]                 [0, 0, 0]                 [0, 0, 1]
 *   Can cross ✓               Can cross ✓               Can cross ✓
 *
 * Day 3: Flood [2,2]
 *   [0, 1, 0]
 *   [1, 1, 0]  ← Middle blocked
 *   [0, 0, 1]
 *   Can cross ✓ (path: top-left → bottom-left)
 *
 * Day 4: Flood [1,1]
 *   [1, 1, 0]  ← Only (0,2) available in top
 *   [1, 1, 0]
 *   [0, 0, 1]
 *   Cannot cross ✗ (isolated)
 *
 * Binary search finds: latest crossable day = 3
 * Return: 3 + 1 = 4 ✓
 *
 * ===================================================================
 *
 * WHY THIS WORKS - Binary Search Validity:
 *
 * 1. MONOTONICITY PROPERTY:
 *    - If we can't cross on day X, we definitely can't cross on day X+1
 *    - More flooding only makes crossing harder, never easier
 *    - This creates the pattern: [✓✓✓✓✗✗✗✗] we need for binary search
 *
 * 2. SEARCH SPACE:
 *    - We search over day indices: 0 to (cells.size() - 1)
 *    - Each day represents a different grid state
 *    - We're finding the boundary between "can cross" and "cannot cross"
 *
 * 3. BFS CORRECTNESS:
 *    - Explores all reachable land cells from top row
 *    - Guarantees shortest path (though we only need any path)
 *    - Reusing grid for visited tracking saves space
 *
 * 4. INDEX CONVERSION:
 *    - cells array uses 1-indexed coordinates (cells[i] = [row, col])
 *    - We convert to 0-indexed for array access: row-1, col-1
 *    - Day indices are 0-indexed in our code
 *    - Final answer converts to 1-indexed day number: latestDay + 1
 *
 * 5. OPTIMIZATION OPPORTUNITIES:
 *    - Could use Union-Find for O(n * α(n)) solution
 *    - Could reverse the process (start from last day, work backwards)
 *    - Current approach is clear and efficient enough for constraints
 *
 * ALTERNATIVE APPROACHES:
 * - Union-Find: Connect top and bottom virtual nodes, find last day they're connected
 * - Reverse simulation: Start from all water, remove water day by day
 * - Current BFS + Binary Search: Most intuitive, good balance of simplicity and efficiency
 */
int main()
{
    return 0;
}