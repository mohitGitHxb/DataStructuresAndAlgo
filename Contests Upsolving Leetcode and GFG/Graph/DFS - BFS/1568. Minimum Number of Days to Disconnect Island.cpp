#include <bits/stdc++.h>
using namespace std;
struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
#define ll long long
#define deb(x) cout << #x << "=" << x << endl
void fast_read()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

class Solution
{
private:
    /*
You are given an m x n binary grid grid where 1 represents land and 0 represents water. An island is a maximal 4-directionally (horizontal or vertical) connected group of 1's.

The grid is said to be connected if we have exactly one island, otherwise is said disconnected.

In one day, we are allowed to change any single land cell (1) into a water cell (0).

Return the minimum number of days to disconnect the grid.



Example 1:

Input: grid = [[0,1,1,0],[0,1,1,0],[0,0,0,0]]

Output: 2
Explanation: We need at least 2 days to get a disconnected grid.
Change land grid[1][1] and grid[0][2] to water and get 2 disconnected island.

Example 2:

Input: grid = [[1,1]]
Output: 2
Explanation: Grid of full water is also disconnected ([[1,1]] -> [[0,0]]), 0 islands.


     */
public:
/* 
@ Intuition:
The binary grid can initially be in one of three states:

    No islands (all cells are water).
    One island.
    More than one island.

We only need to modify the grid in the second case, aiming to reach either the first or third state with minimal changes.

A brute force approach would involve flipping each land cell one by one to achieve the desired conditions. However, this could generate up to 230 states, which which will not satisfy the problem constraints.

To reduce this complexity, we can identify a pattern. The most effective way to split an island into two parts is to find the thinnest cross-section and change those cells to water. In a binary grid, even for uniform shapes like squares or circles, the thinnest cross-section comprises at most 2 squares.
&- Cut through diagonal of length 2 --


* First, we should determine if the grid already satisfies the conditions (zero or more than one island). If so, we can immediately return 0.

To check if we can meet the conditions in 1 step, we systematically flip each island cell to water and evaluate the resulting configuration. We iterate over each cell in the grid, temporarily changing it to water, and use a countIslands function to determine the number of islands in the modified grid. When we encounter a land cell, we use the flood-fill algorithm to count the entire island. The total number of flood-fill calls indicates the number of islands.

If removing one land cell does not achieve the goal, the only remaining option is to return 2.


 */
    const int mod = 1e9 + 7;
    vector<pair<int, int>> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int numberOfIslands(vector<vector<int>> &grid)
    {
        queue<pair<int, int>> q;
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<bool>> vis(n, vector<bool>(m, 0));
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (!vis[i][j] && grid[i][j] == 1)
                {
                    q.push({i, j});
                    while (!q.empty())
                    {
                        int r = q.front().first;
                        int c = q.front().second;
                        q.pop();
                        vis[r][c] = 1;
                        for (auto &it : dir)
                        {
                            int nr = r + it.first;
                            int nc = c + it.second;
                            if (nr >= 0 && nr < n && nc >= 0 && nc < m && !vis[nr][nc] && grid[nr][nc] == 1)
                            {
                                q.push({nr, nc});
                                vis[nr][nc] = 1;
                            }
                        }
                    }
                    ans++;
                }
            }
        }

        return ans;
    }
    int minDays(vector<vector<int>> &grid)
    {
        if (numberOfIslands(grid) > 1 || numberOfIslands(grid) == 0)
        {
            return 0;
        }
        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[0].size(); j++)
            {
                if (grid[i][j] == 1)
                {
                    grid[i][j] = 0;
                    if (numberOfIslands(grid) > 1 || numberOfIslands(grid) == 0)
                    {
                        return 1;
                    }
                    grid[i][j] = 1;
                }
            }
        }
        return 2;
    }
};
