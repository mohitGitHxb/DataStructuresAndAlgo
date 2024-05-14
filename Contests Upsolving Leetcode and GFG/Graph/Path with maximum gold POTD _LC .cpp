#include <vector>
#include <algorithm>
using namespace std;
/* 
In a gold mine grid of size m x n, each cell in this mine has an integer representing the amount of gold in that cell, 0 if it is empty.

Return the maximum amount of gold you can collect under the conditions:

    Every time you are located in a cell you will collect all the gold in that cell.
    From your position, you can walk one step to the left, right, up, or down.
    You can't visit the same cell more than once.
    Never visit a cell with 0 gold.
    You can start and stop collecting gold from any position in the grid that has some gold.

 

Example 1:

Input: grid = [[0,6,0],[5,8,7],[0,9,0]]
Output: 24
Explanation:
[[0,6,0],
 [5,8,7],
 [0,9,0]]
Path to get the maximum gold, 9 -> 8 -> 7.

Example 2:

Input: grid = [[1,0,7],[2,0,6],[3,4,5],[0,3,0],[9,0,20]]
Output: 28
Explanation:
[[1,0,7],
 [2,0,6],
 [3,4,5],
 [0,3,0],
 [9,0,20]]
Path to get the maximum gold, 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7.


 */
class Solution {
private:
    vector<pair<int, int>> dirs{{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    bool isValid(int nr, int nc, int n, int m, vector<vector<int>>& grid) {
        return nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] != 0;
    }

    int dfs(int r, int c, vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        int gold = grid[r][c];
        grid[r][c] = 0; // Mark as visited by setting to 0 (since we can't visit cells with 0 gold)
        int maxGold = 0;
        for (auto& [dr, dc] : dirs) {
            int nr = r + dr, nc = c + dc;
            if (isValid(nr, nc, n, m, grid)) {
                maxGold = max(maxGold, dfs(nr, nc, grid));
            }
        }
        grid[r][c] = gold; // Backtrack: restore the gold amount for future paths
        return gold + maxGold;
    }

public:
    int getMaximumGold(vector<vector<int>>& grid) {
        int ans = 0;
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                if (grid[i][j] != 0) {
                    ans = max(ans, dfs(i, j, grid));
                }
            }
        }
        return ans;
    }
};