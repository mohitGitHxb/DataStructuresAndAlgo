#include <bits/stdc++.h>
using namespace std;
class Solution {
private:
    /*
     * PROBLEM UNDERSTANDING:
     * - Grid with values 0, 1, or 2
     * - Move only right or down from (0,0) to (m-1, n-1)
     * - Each cell has score and cost:
     *   - 0: score=0, cost=0
     *   - 1: score=1, cost=1
     *   - 2: score=2, cost=1 (special: more score for same cost!)
     * - Goal: Maximum score with total cost ≤ k
     * 
     * KEY INSIGHT - Dynamic Programming with Budget Constraint:
     * 
     * OBSERVATION 1: Cell value 2 is optimal
     * - Gives 2 score for only 1 cost
     * - Better efficiency than value 1
     * - Should prioritize paths through 2's when possible
     * 
     * OBSERVATION 2: State Needs Budget Tracking
     * - dp[row][col][budget] = max score reaching (row, col) with budget remaining
     * - Budget decreases by cell cost as we move
     * - Must ensure budget never goes negative
     * 
     * OBSERVATION 3: Top-Down DP with Pruning
     * - If cost exceeds remaining budget, path is invalid
     * - Early termination prevents exploring impossible paths
     * - Memoization prevents redundant calculations
     * 
     * APPROACH:
     * 1. Use top-down DP with state (row, col, remainingBudget)
     * 2. For each cell, calculate its cost
     * 3. Try moving right and down (if budget allows)
     * 4. Return maximum score achievable
     * 5. If destination unreachable within budget, return -1
     * 
     * EXAMPLE: grid = [[0,1],[2,0]], k = 1
     * 
     * Path exploration:
     * (0,0) val=0: score=0, cost=0, budget=1
     *   → Try RIGHT to (0,1) val=1: cost=1, budget=0
     *       Can't continue (budget exhausted before destination)
     *   → Try DOWN to (1,0) val=2: score=2, cost=1, budget=0
     *       → Try RIGHT to (1,1) val=0: score=0, cost=0, budget=0
     *           Reached destination! Total score: 0+2+0=2 ✓
     * 
     * Answer: 2
     * 
     * TIME: O(m × n × k)
     * SPACE: O(m × n × k)
     */
    
    // Sentinel value for uncomputed states
    static constexpr int UNCOMPUTED = -10000;
    
    // Sentinel value for impossible paths
    static constexpr int IMPOSSIBLE = -1000;
    
    /**
     * Calculates the cost of entering a cell
     * 
     * @param row, col - cell position
     * @param grid - the grid
     * @return cost: 0 for value 0, 1 for values 1 or 2
     */
    int getCellCost(int row, int col, const vector<vector<int>>& grid) {
        int value = grid[row][col];
        // Values 1 and 2 both cost 1
        // Value 0 costs 0
        return (value == 2) ? 1 : value;
    }
    
    /**
     * Recursive DP to find maximum score from current position
     * 
     * @param row, col - current position
     * @param grid - the grid
     * @param remainingBudget - remaining cost budget
     * @param rows, cols - grid dimensions
     * @param dp - memoization table
     * @return maximum score achievable from this state, or IMPOSSIBLE if unreachable
     */
    int findMaxScore(int row, int col,
                    const vector<vector<int>>& grid,
                    int remainingBudget,
                    int rows, int cols,
                    vector<vector<vector<int>>>& dp) {
        // Out of bounds check
        if (row >= rows || col >= cols) {
            return IMPOSSIBLE;
        }
        
        int cellCost = getCellCost(row, col, grid);
        
        // Budget exceeded - cannot visit this cell
        if (cellCost > remainingBudget) {
            return IMPOSSIBLE;
        }
        
        // Reached destination successfully
        if (row == rows - 1 && col == cols - 1) {
            return grid[row][col];  // Return cell's score
        }
        
        // Return memoized result
        if (dp[row][col][remainingBudget] != UNCOMPUTED) {
            return dp[row][col][remainingBudget];
        }
        
        int cellScore = grid[row][col];
        int budgetAfterThisCell = remainingBudget - cellCost;
        
        // Try moving right
        int scoreIfGoRight = findMaxScore(row, col + 1, grid, 
                                         budgetAfterThisCell, rows, cols, dp);
        
        // Try moving down
        int scoreIfGoDown = findMaxScore(row + 1, col, grid, 
                                        budgetAfterThisCell, rows, cols, dp);
        
        // Take best path and add current cell's score
        int maxFutureScore = max(scoreIfGoRight, scoreIfGoDown);
        
        // Store and return result
        return dp[row][col][remainingBudget] = cellScore + maxFutureScore;
    }

public:
    int maxPathScore(vector<vector<int>>& grid, int k) {
        int rows = grid.size();
        int cols = grid[0].size();
        
        // Initialize DP table with UNCOMPUTED
        vector<vector<vector<int>>> dp(
            rows, 
            vector<vector<int>>(cols, vector<int>(k + 1, UNCOMPUTED))
        );
        
        int result = findMaxScore(0, 0, grid, k, rows, cols, dp);
        
        // If result is negative (impossible), return -1
        return (result < 0) ? -1 : result;
    }
};

/*
 * DETAILED WALKTHROUGH - Example 1: grid = [[0,1],[2,0]], k = 1
 * 
 * Grid visualization:
 *   (0,0)  (0,1)
 *     0      1
 *   
 *   (1,0)  (1,1)
 *     2      0
 * 
 * ===== DFS Exploration =====
 * 
 * Call: findMaxScore(0, 0, grid, k=1, ...)
 * 
 * At (0,0), value=0:
 *   cellCost = 0
 *   cellScore = 0
 *   budgetAfter = 1 - 0 = 1
 *   
 *   Try RIGHT: findMaxScore(0, 1, grid, budget=1)
 *   Try DOWN: findMaxScore(1, 0, grid, budget=1)
 * 
 * --- Exploring RIGHT path: (0,1) ---
 * At (0,1), value=1:
 *   cellCost = 1
 *   cellScore = 1
 *   budgetAfter = 1 - 1 = 0
 *   
 *   Try RIGHT: out of bounds → IMPOSSIBLE
 *   Try DOWN: findMaxScore(1, 1, grid, budget=0)
 * 
 * At (1,1), value=0:
 *   cellCost = 0
 *   0 ≤ 0 ✓
 *   Reached destination!
 *   Return cellScore = 0
 * 
 * Back at (0,1):
 *   maxFutureScore = max(IMPOSSIBLE, 0) = 0
 *   Return cellScore + maxFutureScore = 1 + 0 = 1
 * 
 * --- Exploring DOWN path: (1,0) ---
 * At (1,0), value=2:
 *   cellCost = 1 (value 2 costs 1)
 *   cellScore = 2
 *   budgetAfter = 1 - 1 = 0
 *   
 *   Try RIGHT: findMaxScore(1, 1, grid, budget=0)
 *   Try DOWN: out of bounds → IMPOSSIBLE
 * 
 * At (1,1), value=0:
 *   cellCost = 0
 *   Reached destination!
 *   Return cellScore = 0
 * 
 * Back at (1,0):
 *   maxFutureScore = max(0, IMPOSSIBLE) = 0
 *   Return cellScore + maxFutureScore = 2 + 0 = 2
 * 
 * --- Back at (0,0) ---
 *   scoreIfGoRight = 1
 *   scoreIfGoDown = 2
 *   maxFutureScore = max(1, 2) = 2
 *   Return cellScore + maxFutureScore = 0 + 2 = 2 ✓
 * 
 * Final answer: 2
 * 
 * ===================================================================
 * 
 * DETAILED WALKTHROUGH - Example 2: grid = [[0,1],[1,2]], k = 1
 * 
 * Grid visualization:
 *   (0,0)  (0,1)
 *     0      1
 *   
 *   (1,0)  (1,1)
 *     1      2
 * 
 * At (0,0), value=0:
 *   budgetAfter = 1
 *   
 * Try RIGHT to (0,1), value=1:
 *   cellCost = 1
 *   budgetAfter = 1 - 1 = 0
 *   
 *   Try RIGHT: out of bounds
 *   Try DOWN to (1,1), value=2:
 *     cellCost = 1
 *     1 > 0 → Budget exceeded! ✗
 *     Return IMPOSSIBLE
 *   
 *   maxFutureScore = max(IMPOSSIBLE, IMPOSSIBLE) = IMPOSSIBLE
 *   Return IMPOSSIBLE
 * 
 * Try DOWN to (1,0), value=1:
 *   cellCost = 1
 *   budgetAfter = 1 - 1 = 0
 *   
 *   Try RIGHT to (1,1), value=2:
 *     cellCost = 1
 *     1 > 0 → Budget exceeded! ✗
 *     Return IMPOSSIBLE
 *   
 *   Try DOWN: out of bounds
 *   
 *   maxFutureScore = IMPOSSIBLE
 *   Return IMPOSSIBLE
 * 
 * Back at (0,0):
 *   maxFutureScore = max(IMPOSSIBLE, IMPOSSIBLE) = IMPOSSIBLE
 *   Return IMPOSSIBLE
 * 
 * Final answer: -1 ✓
 * 
 * ===================================================================
 * 
 * WHY THIS WORKS - Algorithm Correctness:
 * 
 * 1. STATE SPACE COMPLETENESS:
 *    - (row, col, budget) captures all relevant information
 *    - Different budgets at same position lead to different outcomes
 *    - Memoization based on all three dimensions
 * 
 * 2. OPTIMAL SUBSTRUCTURE:
 *    - Best score from (r,c) with budget k depends on
 *      best scores from (r+1,c) and (r,c+1) with reduced budget
 *    - Local optimal choices combine to global optimum
 * 
 * 3. BUDGET CONSTRAINT HANDLING:
 *    - Check cellCost ≤ remainingBudget before visiting
 *    - Prevents invalid paths from being considered
 *    - IMPOSSIBLE value propagates back to indicate no valid path
 * 
 * 4. SCORE VS COST DISTINCTION:
 *    - Score: value of cell (0, 1, or 2)
 *    - Cost: budget consumed (0 or 1)
 *    - Value 2 is special: score=2, cost=1 (efficiency!)
 * 
 * 5. NEGATIVE RESULT HANDLING:
 *    - IMPOSSIBLE propagates through invalid paths
 *    - Final check: result < 0 → return -1
 *    - Correctly identifies when no valid path exists
 * 
 * COMPLEXITY ANALYSIS:
 * - States: O(m × n × k)
 * - Per state: O(1) computation
 * - Total time: O(m × n × k)
 * - Space: O(m × n × k) for DP table + O(m + n) recursion stack
 * 
 * OPTIMIZATION OPPORTUNITIES:
 * - Could use bottom-up DP to avoid recursion overhead
 * - Space optimization: only need previous row/column
 * - Current approach is clear and efficient enough
 * 
 * EDGE CASES:
 * - Single cell (1×1): return grid[0][0] if cost ≤ k, else -1
 * - k=0: only possible if all cells are 0
 * - Grid full of 0's: always possible, score = 0
 * - Grid full of 2's: maximize score if budget allows
 */

int main()
{
    return 0;
}