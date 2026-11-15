#include <bits/stdc++.h>
using namespace std;
class Solution
{
private:
    /*
     * PROBLEM UNDERSTANDING:
     * - Grid with cells: 'S' (start), 'L' (litter), 'R' (reset), 'X' (wall), '.' (empty)
     * - Student starts at 'S' with full energy
     * - Each move to adjacent cell costs 1 energy
     * - 'R' cells restore energy to full (can be reused)
     * - Cannot move if energy reaches 0 (unless on 'R')
     * - Goal: Collect ALL litter with minimum moves, or -1 if impossible
     *
     * KEY INSIGHT – BFS with Bitmask State:
     *
     * OBSERVATION 1: State Must Track Remaining Energy
     * - Same (row, col) with different energy levels leads to different outcomes
     * - Must include energy in state to avoid wrong pruning
     *
     * OBSERVATION 2: Bitmask for Litter Collection
     * - At most 10 litter items (energy constraint bounds complexity)
     * - Track which litter has been collected as a bitmask
     * - Done when mask == (1 << litterCount) - 1 (all bits set)
     *
     * OBSERVATION 3: BFS Gives Shortest Path
     * - Each step costs 1 move, BFS guarantees minimum moves
     * - State: (row, col, remainingEnergy, collectedMask)
     *
     * STATE TRANSITIONS (from cell (r,c) to neighbor (nr,nc)):
     * 1. Out of bounds or 'X' → skip
     * 2. newEnergy = currentEnergy - 1
     * 3. If (nr,nc) == 'L': newMask |= (1 << litterId)
     * 4. If newMask == targetMask → found answer!
     * 5. If (nr,nc) == 'R': newEnergy = maxEnergy (restore)
     * 6. If newEnergy == 0 and not 'R': cannot stay → skip
     * 7. If not visited: enqueue
     *
     * CRITICAL ORDER: Check litter BEFORE checking energy refill
     * - A cell can't be both 'L' and 'R', so order doesn't matter there
     * - But we check for completion (mask == target) before updating energy
     * - This correctly handles landing on 'L' as the last piece
     *
     * EXAMPLE: classroom = ["LS","RL"], energy = 4
     *
     * Litter positions:
     *   (0,0) = 'L' → id 0 (bit 0)
     *   (1,1) = 'L' → id 1 (bit 1)
     * targetMask = 0b11 = 3
     *
     * BFS from (0,1), energy=4, mask=0:
     * Step 1: Move to (0,0)='L'
     *   newMask = 0b01 = 1 ≠ 3
     *   energy = 3
     * Step 2: Move to (1,0)='R'
     *   energy restored to 4
     * Step 3: Move to (1,1)='L'
     *   newMask = 0b11 = 3 == targetMask → return 3 ✓
     *
     * TIME:  O(M × N × energy × 2^L) where L = litter count
     * SPACE: O(M × N × energy × 2^L) for visited array
     */

    // Four cardinal directions: down, right, up, left
    const vector<pair<int, int>> DIRECTIONS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    // BFS state: (row, col, remainingEnergy, collectedMask, stepCount)
    using State = tuple<int, int, int, int, int>;

public:
    int minMoves(vector<string> &classroom, int energy)
    {
        const int ROWS = classroom.size();
        const int COLS = classroom.front().size();

        // Scan grid: find start and assign IDs to litter
        int startRow = -1, startCol = -1;
        int litterCount = 0;
        vector<vector<int>> litterId(ROWS, vector<int>(COLS, -1));

        for (int r = 0; r < ROWS; r++)
        {
            for (int c = 0; c < COLS; c++)
            {
                char cell = classroom[r][c];
                if (cell == 'S')
                {
                    startRow = r;
                    startCol = c;
                }
                else if (cell == 'L')
                {
                    litterId[r][c] = litterCount++;
                }
            }
        }

        // Edge case: no litter to collect
        if (litterCount == 0)
            return 0;

        // All litter collected when every bit is set
        int targetMask = (1 << litterCount) - 1;

        // Visited[r][c][energy][mask] = true if this state was already explored
        // Prevents re-processing states that can only lead to longer paths
        vector<vector<vector<vector<bool>>>> visited(
            ROWS,
            vector<vector<vector<bool>>>(
                COLS,
                vector<vector<bool>>(
                    energy + 1,
                    vector<bool>(1 << litterCount, false))));

        // BFS queue: (row, col, remainingEnergy, collectedMask, stepsTaken)
        queue<State> bfsQueue;
        bfsQueue.push({startRow, startCol, energy, 0, 0});
        visited[startRow][startCol][energy][0] = true;

        while (!bfsQueue.empty())
        {
            auto [row, col, currentEnergy, collectedMask, steps] = bfsQueue.front();
            bfsQueue.pop();

            for (auto &[dRow, dCol] : DIRECTIONS)
            {
                int nextRow = row + dRow;
                int nextCol = col + dCol;

                // Skip out-of-bounds and obstacles
                if (nextRow < 0 || nextRow >= ROWS ||
                    nextCol < 0 || nextCol >= COLS ||
                    classroom[nextRow][nextCol] == 'X')
                {
                    continue;
                }

                char nextCell = classroom[nextRow][nextCol];

                // Moving to this cell costs 1 energy
                int newEnergy = currentEnergy - 1;
                int newMask = collectedMask;

                // Collect litter if present
                if (nextCell == 'L')
                {
                    newMask |= (1 << litterId[nextRow][nextCol]);
                }

                // Check if all litter collected → found minimum!
                if (newMask == targetMask)
                {
                    return steps + 1;
                }

                // Reset energy if on a reset station
                if (nextCell == 'R')
                {
                    newEnergy = energy;
                }

                // Cannot move there if energy runs out (unless restored by 'R')
                if (newEnergy == 0 && nextCell != 'R')
                {
                    continue;
                }

                // Enqueue if not yet visited in this exact state
                if (!visited[nextRow][nextCol][newEnergy][newMask])
                {
                    visited[nextRow][nextCol][newEnergy][newMask] = true;
                    bfsQueue.push({nextRow, nextCol, newEnergy, newMask, steps + 1});
                }
            }
        }

        return -1; // All states exhausted, impossible
    }
};

/*
 * DETAILED WALKTHROUGH – Example 1: classroom = ["S.","XL"], energy = 2
 *
 * Grid:
 *   (0,0)S  (0,1).
 *   (1,0)X  (1,1)L
 *
 * Litter: (1,1) → id 0, targetMask = 0b1 = 1
 *
 * ===== BFS from (0,0), energy=2, mask=0 =====
 *
 * Step 0: State (0,0,2,0)
 *   Neighbors:
 *     DOWN (1,0) = 'X' → skip
 *     RIGHT (0,1) = '.' → newEnergy=1, newMask=0, enqueue
 *     UP out of bounds → skip
 *     LEFT out of bounds → skip
 *
 * Step 1: State (0,1,1,0)
 *   Neighbors:
 *     DOWN (1,1) = 'L' → newEnergy=0, newMask=1 == targetMask → return 2 ✓
 *
 * ===================================================================
 *
 * DETAILED WALKTHROUGH – Example 3: classroom = ["L.S","RXL"], energy = 3
 *
 * Grid:
 *   (0,0)L  (0,1).  (0,2)S
 *   (1,0)R  (1,1)X  (1,2)L
 *
 * Litter: (0,0) → id 0, (1,2) → id 1
 * targetMask = 0b11 = 3
 *
 * Problem: (1,2)='L' is isolated:
 *   - UP (0,2) = 'S' → can reach
 *   - LEFT (1,1) = 'X' → blocked
 *   - DOWN out of bounds → skip
 *   - RIGHT out of bounds → skip
 *
 * To reach (1,2) from (0,2), must come from UP.
 * But first need to collect (0,0)='L'.
 *
 * Path: S(0,2) → (0,1) → (0,0)[collect L1] → (1,0)[reset] → ???
 * From (1,0): can only go UP to (0,0)[already collected]
 *             or RIGHT is X
 *             Cannot reach (1,2)
 *
 * No valid path collects both → return -1 ✓
 *
 * ===================================================================
 *
 * WHY ENERGY IS PART OF STATE:
 *
 * Without energy in state, these two situations look the same:
 *
 *   Position (2,3), mask=0b01
 *   Case A: energy=1 → can only take 1 more step before dying
 *   Case B: energy=5 → can take 5 more steps
 *
 * Treating them as the same state would mark Case B as "visited"
 * when Case A is processed first, then skip it — potentially
 * missing the only path that can collect all litter.
 *
 * ===================================================================
 *
 * WHY CHECK LITTER BEFORE ENERGY REFILL:
 *
 * A cell can only be ONE type (L, R, S, X, .) — they're mutually exclusive.
 * But the order of operations matters conceptually:
 * 1. Move to cell (costs 1 energy)
 * 2. Collect litter if 'L'
 * 3. Restore energy if 'R'
 * 4. Check if stuck (energy == 0 and not 'R')
 *
 * ===================================================================
 *
 * COMPLEXITY ANALYSIS:
 * - States: M × N × energy × 2^L
 *   M, N ≤ 20, energy ≤ 10, L ≤ 10
 *   Worst case: 20 × 20 × 10 × 1024 ≈ 4M states
 * - Per state: O(4) directions
 * - Total: O(M × N × energy × 2^L)
 * - Space: same for visited array
 *
 * EDGE CASES:
 * - No litter: return 0 immediately
 * - Litter unreachable (surrounded by walls): return -1
 * - Energy too low to navigate between litter pieces: return -1
 * - Multiple 'R' cells: student can use any, revisit allowed
 */
int main()
{
    return 0;
}