#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL_TESTING
#include "../container_printer.hpp"
#endif
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
#define ll long long
#define ull unsigned long long
#define deb(x) cout << #x << "=" << x << endl
struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
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
static int init = []()
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
Given an m x n integer matrix heightMap representing the height of each unit cell in a 2D elevation map, return the volume of water it can trap after raining.



Example 1:

Input: heightMap = [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]
Output: 4
Explanation: After the rain, water is trapped between the blocks.
We have two small ponds 1 and 3 units trapped.
The total volume of water trapped is 4.

Example 2:

Input: heightMap = [[3,3,3,3,3],[3,2,2,2,3],[3,2,1,2,3],[3,2,2,2,3],[3,3,3,3,3]]


    Use a priority queue to store boundary cells, starting with the smallest height. Each entry in the queue is of the form {height, {row, col}}.
    Mark boundary cells as visited to avoid revisiting them.
    Process cells using BFS:
        For each cell popped from the queue, explore its four neighbors.
        If a neighbor is unvisited, calculate how much water it can trap (max(0, current_height - neighbor_height)).
        Add the neighbor to the queue with its updated height (max(current_height, neighbor_height)).
    Continue until all reachable cells are processed.

Complexity

    Time complexity: O(n.m.log(n.m))

    Space complexity: O(n.m)



     */
public:
    int trapRainWater(vector<vector<int>> &height)
    {
        int n = height.size();
        int m = height[0].size();

        // pair<int, pair<int, int>>
        //{height, {r, c}}
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

        vector<vector<int>> vis(n, vector<int>(m));

        // first and last column
        for (int i = 0; i < n; i++)
        {
            vis[i][0] = 1;
            vis[i][m - 1] = 1;
            pq.push({height[i][0], {i, 0}});
            pq.push({height[i][m - 1], {i, m - 1}});
        }
        // first and last row
        for (int i = 0; i < m; i++)
        {
            vis[0][i] = 1;
            vis[n - 1][i] = 1;
            pq.push({height[0][i], {0, i}});
            pq.push({height[n - 1][i], {n - 1, i}});
        }
        int ans = 0;
        while (!pq.empty())
        {
            int h = pq.top().first;
            int r = pq.top().second.first;
            int c = pq.top().second.second;
            pq.pop();

            int dr[] = {-1, 0, 1, 0};
            int dc[] = {0, -1, 0, 1};
            for (int i = 0; i < 4; i++)
            {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (nr >= 0 && nr < n && nc >= 0 && nc < m && !vis[nr][nc])
                {
                    ans += max(0, h - height[nr][nc]);
                    pq.push({max(h, height[nr][nc]), {nr, nc}});
                    vis[nr][nc] = 1;
                }
            }
        }
        return ans;
    }
};

#ifdef LOCAL_TESTING
int main()
{
    Solution obj;
    cout << "\nProgram Started\n\n";
    cout << obj.minimizeXor(4214, 5) << endl;
    return 0;
}
#endif