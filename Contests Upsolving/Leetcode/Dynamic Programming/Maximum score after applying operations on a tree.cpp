#include <bits/stdc++.h>
using namespace std;
/*
This code aims to find the maximum score you can obtain after performing operations on a tree while keeping it healthy. The health of a tree is defined such that the sum of values on the path from the root to any leaf node is different from zero.

Here's a step-by-step breakdown:

1. **Function Definition**:
   - The function `maximumScoreAfterOperations` takes the input of edges (representing the tree structure) and values (representing values associated with each node).
   - It initializes the adjacency list `g` and a 2D array `dp` to store intermediate results.

2. **DFS Function**:
   - The `dfs` function is a depth-first search that calculates the maximum score starting from a given node.
   - It considers two possibilities: whether the current node is taken (`isPossibleToTake = true`) or not taken (`isPossibleToTake = false`).
   - The base case is when a leaf node is reached (having only one edge and not being the root).

3. **Initialization**:
   - The function `maximumScoreAfterOperations` initializes the adjacency list `g` based on the input edges.
   - It initializes the `dp` array to store previously calculated results, initialized with -1.

4. **DFS Recursive Calls**:
   - The function then calls `dfs` starting from the root (node 0) with the initial score being zero and `isPossibleToTake` set to false.

5. **Result**:
   - The result is the maximum score calculated from the DFS traversal.

**Time Complexity**:
   - The time complexity is determined by the DFS traversal, which is O(N), where N is the number of nodes in the tree.

**Space Complexity**:
   - The space complexity is O(N), where N is the number of nodes. This includes the adjacency list `g` and the memoization array `dp`.

**Hint**:
   - The code uses DFS to traverse the tree and memoization to avoid redundant calculations.
   - The `dfs` function explores two possibilities: taking the current node or not taking it, and it recursively explores the children of the current node.
   - The memoization array `dp` helps optimize the solution by storing already calculated results.

 */

class Solution
{
public:
    vector<vector<int>> g;
    vector<vector<long long>> dp;
    long long dfs(int node, int par, bool isPossibleToTake, vector<int> &values)
    {
        if (g[node].size() == 1 && node != 0)
        {
            return (isPossibleToTake) ? values[node] : 0;
        }
        if (dp[node][isPossibleToTake] != -1)
            return dp[node][isPossibleToTake];
        // not-take
        long long notTake = 0;
        for (auto &it : g[node])
        {
            if (par != it)
                notTake += dfs(it, node, true, values);
        }
        // take
        long long take = values.at(node);
        for (auto &it : g[node])
        {
            if (par != it)
                take += dfs(it, node, isPossibleToTake, values);
        }
        return dp[node][isPossibleToTake] = max(notTake, take);
    }

    long long maximumScoreAfterOperations(vector<vector<int>> &edges, vector<int> &values)
    {
        int n = values.size();
        g.resize(n);
        for (auto &e : edges)
        {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        dp.resize(n + 1, vector<long long>(2, -1));
        return dfs(0, -1, false, values);
    }
};
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        // write code here
    }
    return 0;
}