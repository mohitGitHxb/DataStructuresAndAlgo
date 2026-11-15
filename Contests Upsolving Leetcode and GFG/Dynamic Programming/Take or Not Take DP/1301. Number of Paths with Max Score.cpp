#include <bits/stdc++.h>
using namespace std;
class Solution
{
private:
    /*
     * PROBLEM UNDERSTANDING:
     * - n×n board, start at bottom-right 'S', reach top-left 'E'
     * - Valid moves: UP, LEFT, DIAGONAL (up-left) only
     * - Cells: 'S' (start), 'E' (end), 'X' (obstacle), '1'-'9' (coins)
     * - Goal: Maximize sum of coins collected along path
     * - Return: [maxScore, numberOfPathsWithMaxScore] modulo 1e9+7
     *
     * KEY INSIGHT - Top-Down DP returning (score, pathCount) pairs:
     *
     * OBSERVATION 1: State Definition
     * - dp[i][j] = (bestScore, countOfBestPaths) from cell (i,j) to 'E'
     * - From (i,j), we can go to (i-1,j), (i,j-1), (i-1,j-1)
     * - Each valid successor gives a (score, count) pair
     *
     * OBSERVATION 2: Combining Successor Results
     * - After collecting from successor (i',j'), add current cell's coins
     * - If paths through (i',j') give score X, our contribution = X + coins(i,j)
     * - Among all three directions, we want the maximum score
     * - If multiple directions tie, their path counts ADD together
     *
     * OBSERVATION 3: Path Count Merging Logic
     * - Only add path counts from directions that achieve the MAXIMUM score
     * - Ties → accumulate counts
     * - Lower score → discard those paths entirely
     *
     * BASE CASES:
     * - Cell 'E': score=0, paths=1 (found one complete path)
     * - Cell 'X': score=0, paths=0 (dead end, no valid paths)
     * - Out of bounds: skip this direction
     *
     * EXAMPLE: board = ["E23","2X2","12S"]
     *
     * Grid (row 0 = top):
     *   Row 0: E 2 3
     *   Row 1: 2 X 2
     *   Row 2: 1 2 S
     *
     * Start: (2,2)='S', solve(2,2)
     *
     * solve(2,2): S → value 0
     *   UP → solve(1,2)='2':
     *     UP → solve(0,2)='3':
     *       UP → out of bounds
     *       LEFT → solve(0,1)='2':
     *         UP → out of bounds
     *         LEFT → solve(0,0)='E': return (0,1)
     *         DIAG → out of bounds
     *         Best: (0+2, 1) = (2, 1)
     *       DIAG → solve(-1,1) = out of bounds
     *       Best from (0,2): (2+3, 1) = (5, 1)
     *     LEFT → solve(1,1)='X': return (0,0) → skip
     *     DIAG → solve(0,1)='2': result (2,1) from above
     *       add coin 2 → (4,1)
     *     Best from (1,2): score 5 from UP, score 4 from DIAG → take UP
     *       (1,2) value: (5+2, 1) = (7, 1)
     *   LEFT → solve(2,1)='2':
     *     ... (blocked by X in column 1, can only go diag to (1,0))
     *     solve(1,0)='2': solve(0,0)='E' → (0,1), add 2 → (2,1)
     *     (2,1): best = (2+2, 1) = (4,1)
     *   DIAG → solve(1,1)='X': (0,0) → skip
     *
     * At (2,2): UP=(7,1), LEFT=(4,1), DIAG=invalid
     *   Best score = 7, paths = 1
     *
     * Answer: [7, 1] ✓
     *
     * TIME:  O(n²) — each cell computed once
     * SPACE: O(n²) — memoization table
     */

    int n;
    static const int MOD = 1e9 + 7;

    // Memoization: t[i][j] = {bestScore, pathCount}
    // (-1,-1) means uncomputed
    vector<vector<pair<int, int>>> memo;

    /**
     * Converts a board character to its coin value
     * 'S' is treated as 0 (start cell, no coins)
     * 'E' is treated as 0 (end cell, no coins — handled as base case)
     */
    int coinValue(char ch)
    {
        return (ch == 'S' || ch == 'E') ? 0 : ch - '0';
    }

    /**
     * Checks if position (i,j) is a valid, non-obstacle cell
     */
    bool isValid(int i, int j, const vector<string> &board)
    {
        return i >= 0 && i < n && j >= 0 && j < n && board[i][j] != 'X';
    }

    /**
     * Merges a candidate (candidateScore, candidatePaths) into
     * the running best (bestScore, bestPaths).
     *
     * Rules:
     *   - If candidateScore > bestScore → replace
     *   - If candidateScore == bestScore → accumulate paths
     *   - If candidateScore < bestScore → ignore
     */
    void mergeBest(int &bestScore, int &bestPaths,
                   int candidateScore, int candidatePaths)
    {
        if (candidatePaths == 0)
            return; // direction had no valid paths

        if (candidateScore > bestScore)
        {
            bestScore = candidateScore;
            bestPaths = candidatePaths;
        }
        else if (candidateScore == bestScore)
        {
            bestPaths = (bestPaths + candidatePaths) % MOD;
        }
        // candidateScore < bestScore → discard
    }

    /**
     * Recursive DP: returns (bestScore, pathCount) from cell (i,j) to 'E'
     *
     * @param i, j  - current cell
     * @param board - the game board
     * @return {maxCoinsCollectable, numberOfMaxPaths}
     */
    pair<int, int> solve(int i, int j, const vector<string> &board)
    {
        // Base case: reached 'E'
        if (board[i][j] == 'E')
            return {0, 1};

        // Base case: hit obstacle (shouldn't normally reach here due to isValid)
        if (board[i][j] == 'X')
            return {0, 0};

        // Return memoized result
        if (memo[i][j] != make_pair(-1, -1))
            return memo[i][j];

        int coins = coinValue(board[i][j]);

        // Try all three directions: UP, LEFT, DIAGONAL
        // Each direction: if valid, recurse, then add current cell's coins
        int bestScore = -1, bestPaths = 0;

        // Direction 1: Move UP
        if (isValid(i - 1, j, board))
        {
            auto [upScore, upPaths] = solve(i - 1, j, board);
            if (upPaths > 0)
            {
                mergeBest(bestScore, bestPaths, upScore + coins, upPaths);
            }
        }

        // Direction 2: Move LEFT
        if (isValid(i, j - 1, board))
        {
            auto [leftScore, leftPaths] = solve(i, j - 1, board);
            if (leftPaths > 0)
            {
                mergeBest(bestScore, bestPaths, leftScore + coins, leftPaths);
            }
        }

        // Direction 3: Move DIAGONAL (up-left)
        if (isValid(i - 1, j - 1, board))
        {
            auto [diagScore, diagPaths] = solve(i - 1, j - 1, board);
            if (diagPaths > 0)
            {
                mergeBest(bestScore, bestPaths, diagScore + coins, diagPaths);
            }
        }

        // If no valid direction reached 'E', return dead end
        if (bestScore == -1)
        {
            return memo[i][j] = {0, 0};
        }

        return memo[i][j] = {bestScore, bestPaths % MOD};
    }

public:
    vector<int> pathsWithMaxScore(vector<string> &board)
    {
        n = board.size();
        memo.assign(n, vector<pair<int, int>>(n, {-1, -1}));

        auto [maxScore, pathCount] = solve(n - 1, n - 1, board);

        // If no path exists to 'E', return [0, 0]
        if (pathCount == 0)
            return {0, 0};

        return {maxScore, pathCount};
    }
};

/*
 * DETAILED WALKTHROUGH - Example 2: board = ["E12","1X1","21S"]
 *
 * Grid (row 0 = top):
 *   (0,0)E  (0,1)1  (0,2)2
 *   (1,0)1  (1,1)X  (1,2)1
 *   (2,0)2  (2,1)1  (2,2)S
 *
 * Start: solve(2,2)='S', coins=0
 *
 * ─── solve(2,2) ────────────────────────────────────
 * UP → solve(1,2)='1'
 *   UP → solve(0,2)='2'
 *     UP → out of bounds
 *     LEFT → solve(0,1)='1'
 *       LEFT → solve(0,0)='E': return (0,1) ← base case
 *       add coin 1 → (1,1)
 *       memo[0][1] = (1,1)
 *     DIAG → out of bounds
 *     add coin 2: (1+2, 1) = (3, 1)
 *     memo[0][2] = (3,1)
 *   LEFT → solve(1,1)='X': return (0,0) → skip
 *   DIAG → solve(0,1): already computed → (1,1)
 *     add coin 1: (1+1, 1) = (2, 1)
 *   Best at (1,2): UP gives 3, DIAG gives 2 → best = (3+1, 1) = (4,1)
 *   memo[1][2] = (4,1)
 *
 * LEFT → solve(2,1)='1'
 *   UP → solve(1,1)='X' → skip
 *   LEFT → solve(2,0)='2'
 *     UP → solve(1,0)='1'
 *       UP → solve(0,0)='E': return (0,1)
 *       add coin 1 → (1,1)
 *       memo[1][0] = (1,1)
 *     LEFT → out of bounds
 *     DIAG → out of bounds
 *     add coin 2: (1+2,1) = (3,1)
 *     memo[2][0] = (3,1)
 *   DIAG → solve(1,0)='1': already computed → (1,1)
 *     add coin 1 → (2,1)
 *   Best at (2,1): LEFT gives 3, DIAG gives 2 → best = (3+1,1) = (4,1)
 *   memo[2][1] = (4,1)
 *
 * DIAG → solve(1,1)='X' → skip
 *
 * At (2,2): UP gives (4,1), LEFT gives (4,1), DIAG invalid
 *   Both tie at score 4 → bestPaths = 1+1 = 2
 *   coins(S) = 0, so final = (4, 2)
 *
 * Answer: [4, 2] ✓
 *
 * ===================================================================
 *
 * WHY THE MERGE LOGIC WORKS:
 *
 * When combining results from multiple directions:
 *
 * Score  Paths   Action
 * ─────  ─────   ──────────────────────────────────────────────────
 *  7       2     First candidate → becomes bestScore=7, bestPaths=2
 *  7       3     Tie! → bestPaths = 2+3 = 5
 *  5       4     Lower score → discard entirely
 *  9       1     Better! → bestScore=9, bestPaths=1 (reset)
 *
 * This ensures we only count paths that achieve the MAXIMUM score.
 *
 * ===================================================================
 *
 * COMPLEXITY ANALYSIS:
 * - States: O(n²) cells, each computed exactly once
 * - Per state: O(1) — check 3 directions, O(1) merges
 * - Total time: O(n²)
 * - Space: O(n²) for memo table + O(n) recursion stack depth
 *
 * EDGE CASES:
 * - 'E' and 'S' adjacent diagonally: direct path, score=0, paths=1
 * - All paths blocked by 'X': return [0,0]
 * - Multiple tied paths: count accumulates modulo 1e9+7
 * - Single cell board: not possible (n ≥ 2 by constraint)
 */
int main()
{
    return 0;
}