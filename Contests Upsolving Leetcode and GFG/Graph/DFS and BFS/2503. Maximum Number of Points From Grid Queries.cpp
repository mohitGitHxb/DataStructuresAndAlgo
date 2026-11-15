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
You are given an m x n integer matrix grid and an array queries of size k.

Find an array answer of size k such that for each integer queries[i] you start in the top left cell of the matrix and repeat the following process:

    If queries[i] is strictly greater than the value of the current cell that you are in, then you get one point if it is your first time visiting this cell, and you can move to any adjacent cell in all 4 directions: up, down, left, and right.
    Otherwise, you do not get any points, and you end this process.

After the process, answer[i] is the maximum number of points you can get. Note that for each query you are allowed to visit the same cell multiple times.

Return the resulting array answer.



Example 1:

Input: grid = [[1,2,3],[2,5,7],[3,5,1]], queries = [5,6,2]
Output: [5,8,1]
Explanation: The diagrams above show which cells we visit to get points for each query.


     */
public:
    const vector<pair<int, int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    void buildOfflineQueries(vector<pair<int, int>> &offlineQueries, vector<int> &queries, const int qs)
    {
        for (int i = 0; i < qs; i++)
        {
            offlineQueries.at(i) = {queries[i], i};
        }
        sort(offlineQueries.begin(), offlineQueries.end());
    }

    void runBfs(vector<vector<int>> &grid, vector<vector<bool>> &visited, const int target, int &cnt, set<tuple<int, int, int>> &st)
    {
        while (!st.empty() && get<0>(*st.begin()) < target)
        {
            auto [val, x, y] = *st.begin();
            st.erase(st.begin());
            cnt++;
            for (auto [dx, dy] : dirs)
            {
                const int nx = x + dx, ny = y + dy;
                if (nx < 0 || nx >= grid.size() || ny < 0 || ny >= grid.front().size() || visited[nx][ny])
                    continue;
                st.insert({grid[nx][ny], nx, ny});
                visited[nx][ny] = true;
            }
        }
    }

    vector<int> maxPoints(vector<vector<int>> &grid, vector<int> &queries)
    {
        const int n = grid.size(), m = grid.front().size(), qs = queries.size();
        vector<pair<int, int>> offlineQueries(qs); // queries in sorted order
        buildOfflineQueries(offlineQueries, queries, qs);

        // Run BFS for each query but since queries are sorted instead of running again and again from top left we can just extend our search from where we left.
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        set<tuple<int, int, int>> st;
        st.insert({grid[0][0], 0, 0});
        visited[0][0] = true;
        int cnt = 0;

        vector<int> results(qs);
        for (int i = 0; i < qs; i++)
        {
            auto [target, index] = offlineQueries[i];
            // This is the part where we extend our search from where we left
            runBfs(grid, visited, target, cnt, st);
            results[index] = cnt;
        }
        return results;
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