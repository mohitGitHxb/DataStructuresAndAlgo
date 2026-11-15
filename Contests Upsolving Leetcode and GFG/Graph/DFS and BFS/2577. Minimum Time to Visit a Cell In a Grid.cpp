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
#define ull unsigned long long
#define deb(x) cout << #x << "=" << x << endl
static int init = []
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
}();

class Solution
{
private:
    /*
You are given a m x n matrix grid consisting of non-negative integers where grid[row][col] represents the minimum time required to be able to visit the cell (row, col), which means you can visit the cell (row, col) only when the time you visit it is greater than or equal to grid[row][col].

You are standing in the top-left cell of the matrix in the 0th second, and you must move to any adjacent cell in the four directions: up, down, left, and right. Each move you make takes 1 second.

Return the minimum time required in which you can visit the bottom-right cell of the matrix. If you cannot visit the bottom-right cell, then return -1.



Example 1:

Input: grid = [[0,1,3,2],[5,1,2,5],[4,3,8,6]]
Output: 7
Explanation: One of the paths that we can take is the following:
- at t = 0, we are on the cell (0,0).
- at t = 1, we move to the cell (0,1). It is possible because grid[0][1] <= 1.
- at t = 2, we move to the cell (1,1). It is possible because grid[1][1] <= 2.
- at t = 3, we move to the cell (1,2). It is possible because grid[1][2] <= 3.
- at t = 4, we move to the cell (1,1). It is possible because grid[1][1] <= 4.
- at t = 5, we move to the cell (1,2). It is possible because grid[1][2] <= 5.
- at t = 6, we move to the cell (1,3). It is possible because grid[1][3] <= 6.
- at t = 7, we move to the cell (2,3). It is possible because grid[2][3] <= 7.
The final time is 7. It can be shown that it is the minimum time possible.


    @Approach: 
    &- If we notice carefully, we can see that the time taken to visit each cell can easily be found using
    &- If the difference between the current time and cell is even then the no. of back and forth moves + 1
    &- Use Set or priority queue to store the time, row and column of the cell.
     */
public:
    const int mod = 1e9 + 7;
    const vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    inline constexpr bool inBounds(int r, int c, int n, int m) { return r >= 0 && r < n && c >= 0 && c < m; }
    int minimumTime(vector<vector<int>> &grid)
    {
        if (grid[0][1] > 1 && grid[1][0] > 1)
            return -1;
        int n = grid.size(), m = grid.front().size();
        vector<vector<bool>> vis(n, vector<bool>(m));
        set<tuple<int, int, int>> st;
        st.emplace(0, 0, 0);
        while (!st.empty())
        {
            auto [time, r, c] = *st.begin();
            st.erase(st.begin());
            if (r == n - 1 && c == m - 1)
                return time;
            if (vis[r][c])
                continue;
            vis[r][c] = true;
            for (auto &[dr, dc] : directions)
            {
                int nr = r + dr, nc = c + dc;
                if (inBounds(nr, nc, n, m) && !vis[nr][nc])
                {
                    int newTime = max(time + 1, grid[nr][nc] + ((grid[nr][nc] - time) % 2 == 0));
                    st.erase({grid[nr][nc], nr, nc});
                    st.insert({newTime, nr, nc});
                }
            }
        }
        return -1;
    }
};

int main(int argc, char const *argv[])
{
    Solution solution;
    return 0;
}
