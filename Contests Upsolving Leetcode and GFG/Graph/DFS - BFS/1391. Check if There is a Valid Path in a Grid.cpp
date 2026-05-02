#include <bits/stdc++.h>
using namespace std;
class Solution
{
private:
    /*
     * PROBLEM UNDERSTANDING:
     * - Grid where each cell is a street with specific connectivity
     * - Street types:
     *   1: Left ↔ Right (horizontal)
     *   2: Up ↔ Down (vertical)
     *   3: Left ↔ Down (L-shape, opening right-up)
     *   4: Right ↔ Down (L-shape, opening left-up)
     *   5: Left ↔ Up (L-shape, opening right-down)
     *   6: Right ↔ Up (L-shape, opening left-down)
     * - Goal: Find if path exists from (0,0) to (m-1, n-1) following streets
     *
     * KEY INSIGHT - Bidirectional Connection Validation:
     *
     * OBSERVATION 1: Connection Must Be Mutual
     * - To move from cell A to cell B, both must connect to each other
     * - Example: If A connects right and B connects left → valid
     * - Example: If A connects right but B connects down → invalid
     *
     * OBSERVATION 2: Street Type Determines Exits
     * - Each street type has exactly 2 exits (directions)
     * - Type 1: exits LEFT and RIGHT
     * - Type 2: exits UP and DOWN
     * - Type 3: exits LEFT and DOWN
     * - Type 4: exits RIGHT and DOWN
     * - Type 5: exits LEFT and UP
     * - Type 6: exits RIGHT and UP
     *
     * OBSERVATION 3: Complementary Connections
     * - If we exit RIGHT, neighbor must have LEFT exit
     * - If we exit DOWN, neighbor must have UP exit
     * - Mapping:
     *   RIGHT (→) requires neighbor to have LEFT (←)
     *   LEFT (←) requires neighbor to have RIGHT (→)
     *   DOWN (↓) requires neighbor to have UP (↑)
     *   UP (↑) requires neighbor to have DOWN (↓)
     *
     * APPROACH:
     * 1. Use DFS from (0,0)
     * 2. For each cell, check its street type to find valid exits
     * 3. For each exit direction, verify neighbor has complementary connection
     * 4. Continue DFS until reaching (m-1, n-1) or exhausting paths
     *
     * EXAMPLE: grid = [[2,4,3],[6,5,2]]
     *
     * Start at (0,0): type 2 (UP ↔ DOWN)
     *   Can go DOWN to (1,0)
     * At (1,0): type 6 (RIGHT ↔ UP)
     *   Can go UP to (0,0) [already visited]
     *   Can go RIGHT to (1,1)
     * At (1,1): type 5 (LEFT ↔ UP)
     *   Can go LEFT to (1,0) [already visited]
     *   Can go UP to (0,1)
     * At (0,1): type 4 (RIGHT ↔ DOWN)
     *   Can go DOWN to (1,1) [already visited]
     *   Can go RIGHT to (0,2)
     * At (0,2): type 3 (LEFT ↔ DOWN)
     *   Can go DOWN to (1,2)
     * At (1,2): type 2 (UP ↔ DOWN)
     *   Reached destination ✓
     *
     * TIME: O(m × n)
     * SPACE: O(m × n) for visited array and recursion stack
     */

    // Street type definitions with their exit directions
    struct StreetType
    {
        bool hasLeft, hasRight, hasUp, hasDown;
    };

    // Mapping of street types to their connections
    const StreetType streetConnections[7] = {
        {},                         // 0: unused
        {true, true, false, false}, // 1: LEFT ↔ RIGHT
        {false, false, true, true}, // 2: UP ↔ DOWN
        {true, false, false, true}, // 3: LEFT ↔ DOWN
        {false, true, false, true}, // 4: RIGHT ↔ DOWN
        {true, false, true, false}, // 5: LEFT ↔ UP
        {false, true, true, false}  // 6: RIGHT ↔ UP
    };

    /**
     * Checks if we can move from current cell to neighbor cell
     * Both cells must have compatible connections
     *
     * @param currentRow, currentCol - current position
     * @param neighborRow, neighborCol - neighbor position to check
     * @param grid - the street grid
     * @param visited - tracks visited cells
     * @return true if movement is valid and neighbor not visited
     */
    bool canMoveTo(int currentRow, int currentCol,
                   int neighborRow, int neighborCol,
                   const vector<vector<int>> &grid,
                   const vector<vector<bool>> &visited)
    {
        int rows = grid.size();
        int cols = grid[0].size();

        // Check bounds
        if (neighborRow < 0 || neighborRow >= rows ||
            neighborCol < 0 || neighborCol >= cols)
        {
            return false;
        }

        // Check if already visited
        if (visited[neighborRow][neighborCol])
        {
            return false;
        }

        int currentStreet = grid[currentRow][currentCol];
        int neighborStreet = grid[neighborRow][neighborCol];

        // Determine direction of movement
        int deltaRow = neighborRow - currentRow;
        int deltaCol = neighborCol - currentCol;

        // Check if current street has exit in this direction
        // AND neighbor street has entrance from this direction
        if (deltaRow == -1)
        { // Moving UP
            return streetConnections[currentStreet].hasUp &&
                   streetConnections[neighborStreet].hasDown;
        }
        else if (deltaRow == 1)
        { // Moving DOWN
            return streetConnections[currentStreet].hasDown &&
                   streetConnections[neighborStreet].hasUp;
        }
        else if (deltaCol == -1)
        { // Moving LEFT
            return streetConnections[currentStreet].hasLeft &&
                   streetConnections[neighborStreet].hasRight;
        }
        else if (deltaCol == 1)
        { // Moving RIGHT
            return streetConnections[currentStreet].hasRight &&
                   streetConnections[neighborStreet].hasLeft;
        }

        return false;
    }

    /**
     * DFS to find path from current position to bottom-right corner
     *
     * @param row, col - current position
     * @param grid - the street grid
     * @param visited - tracks visited cells
     * @return true if path exists to destination
     */
    bool findPath(int row, int col,
                  const vector<vector<int>> &grid,
                  vector<vector<bool>> &visited)
    {
        int rows = grid.size();
        int cols = grid[0].size();

        // Base case: reached destination
        if (row == rows - 1 && col == cols - 1)
        {
            return true;
        }

        // Mark current cell as visited
        visited[row][col] = true;

        // Try all four directions
        // UP
        if (canMoveTo(row, col, row - 1, col, grid, visited))
        {
            if (findPath(row - 1, col, grid, visited))
            {
                return true;
            }
        }

        // DOWN
        if (canMoveTo(row, col, row + 1, col, grid, visited))
        {
            if (findPath(row + 1, col, grid, visited))
            {
                return true;
            }
        }

        // LEFT
        if (canMoveTo(row, col, row, col - 1, grid, visited))
        {
            if (findPath(row, col - 1, grid, visited))
            {
                return true;
            }
        }

        // RIGHT
        if (canMoveTo(row, col, row, col + 1, grid, visited))
        {
            if (findPath(row, col + 1, grid, visited))
            {
                return true;
            }
        }

        return false;
    }

public:
    bool hasValidPath(vector<vector<int>> &grid)
    {
        int rows = grid.size();
        int cols = grid[0].size();

        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        return findPath(0, 0, grid, visited);
    }
};

/*
 * STREET TYPE VISUALIZATION:
 *
 * Type 1: ←→  (horizontal)
 * Type 2: ↑↓  (vertical)
 * Type 3: ←↓  (L-shape, opens to upper-right)
 * Type 4: →↓  (L-shape, opens to upper-left)
 * Type 5: ←↑  (L-shape, opens to lower-right)
 * Type 6: →↑  (L-shape, opens to lower-left)
 *
 * CONNECTION RULES:
 * - To move RIGHT: current must have →, neighbor must have ←
 * - To move LEFT: current must have ←, neighbor must have →
 * - To move DOWN: current must have ↓, neighbor must have ↑
 * - To move UP: current must have ↑, neighbor must have ↓
 *
 * ===================================================================
 *
 * DETAILED WALKTHROUGH - Example 1: grid = [[2,4,3],[6,5,2]]
 *
 * Grid visualization:
 *   (0,0)  (0,1)  (0,2)
 *     2      4      3
 *     ↑↓    →↓    ←↓
 *
 *   (1,0)  (1,1)  (1,2)
 *     6      5      2
 *     →↑    ←↑     ↑↓
 *
 * DFS Trace:
 *
 * Start: (0,0), type 2 (↑↓)
 *   Try UP: out of bounds ✗
 *   Try DOWN: (1,0) type 6 (→↑)
 *     Current has ↓, neighbor has ↑ ✓
 *     Move to (1,0)
 *
 * At (0,1), type 6 (→↑)
 *   Try UP: (0,0) visited ✗
 *   Try RIGHT: (1,1) type 5 (←↑)
 *     Current has →, neighbor has ← ✓
 *     Move to (1,1)
 *
 * At (1,1), type 5 (←↑)
 *   Try LEFT: (1,0) visited ✗
 *   Try UP: (0,1) type 4 (→↓)
 *     Current has ↑, neighbor has ↓ ✓
 *     Move to (0,1)
 *
 * At (0,1), type 4 (→↓)
 *   Try DOWN: (1,1) visited ✗
 *   Try RIGHT: (0,2) type 3 (←↓)
 *     Current has →, neighbor has ← ✓
 *     Move to (0,2)
 *
 * At (0,2), type 3 (←↓)
 *   Try LEFT: (0,1) visited ✗
 *   Try DOWN: (1,2) type 2 (↑↓)
 *     Current has ↓, neighbor has ↑ ✓
 *     Move to (1,2)
 *
 * At (1,2): Destination reached! ✓
 * Return true
 *
 * ===================================================================
 *
 * DETAILED WALKTHROUGH - Example 2: grid = [[1,2,1],[1,2,1]]
 *
 * Grid visualization:
 *   (0,0)  (0,1)  (0,2)
 *     1      2      1
 *    ←→     ↑↓    ←→
 *
 *   (1,0)  (1,1)  (1,2)
 *     1      2      1
 *    ←→     ↑↓    ←→
 *
 * Start: (0,0), type 1 (←→)
 *   Try LEFT: out of bounds ✗
 *   Try RIGHT: (0,1) type 2 (↑↓)
 *     Current has →, but neighbor doesn't have ← ✗
 *     (Neighbor only has ↑↓, no horizontal connections)
 *   Try UP: out of bounds ✗
 *   Try DOWN: (1,0) type 1 (←→)
 *     Current doesn't have ↓ ✗
 *
 * No valid moves from (0,0)
 * Return false ✓
 *
 * ===================================================================
 *
 * WHY THIS WORKS - Algorithm Correctness:
 *
 * 1. BIDIRECTIONAL CONNECTION CHECK:
 *    - Both cells must agree on the connection
 *    - Current must have exit in direction
 *    - Neighbor must have entrance from that direction
 *    - Prevents illegal moves through non-connecting streets
 *
 * 2. STREET TYPE MAPPING:
 *    - Precomputed table of connections for each type
 *    - O(1) lookup for validation
 *    - Clear and maintainable structure
 *
 * 3. DFS EXPLORATION:
 *    - Systematically tries all valid paths
 *    - Visited tracking prevents cycles
 *    - Early termination when destination reached
 *
 * 4. DIRECTION INDEPENDENCE:
 *    - Checks all four directions uniformly
 *    - Delta calculation determines movement direction
 *    - Symmetric validation logic
 *
 * 5. COMPLETENESS:
 *    - Explores all reachable cells
 *    - Guaranteed to find path if it exists
 *    - Returns false only when all paths exhausted
 *
 * COMPLEXITY ANALYSIS:
 * - Time: O(m × n) - visit each cell at most once
 * - Space: O(m × n) - visited array + recursion stack
 *
 * EDGE CASES:
 * - Single cell (1×1): always true (already at destination)
 * - Start/end have incompatible street types: false
 * - Isolated regions: false if destination unreachable
 */
int main()
{
    return 0;
}