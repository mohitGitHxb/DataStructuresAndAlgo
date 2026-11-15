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
You are given an integer n. There is an undirected graph with n vertices, numbered from 0 to n - 1. You are given a 2D integer array edges where edges[i] = [ai, bi] denotes that there exists an undirected edge connecting vertices ai and bi.

Return the number of complete connected components of the graph.

A connected component is a subgraph of a graph in which there exists a path between any two vertices, and no vertex of the subgraph shares an edge with a vertex outside of the subgraph.

A connected component is said to be complete if there exists an edge between every pair of its vertices.



Example 1:

Input: n = 6, edges = [[0,1],[0,2],[1,2],[3,4]]
Output: 3
Explanation: From the picture above, one can see that all of the components of this graph are complete.

Example 2:

Input: n = 6, edges = [[0,1],[0,2],[1,2],[3,4],[3,5]]
Output: 1
Explanation: The component containing vertices 0, 1, and 2 is complete since there is an edge between every pair of two vertices. On the other hand, the component containing vertices 3, 4, and 5 is not complete since there is no edge between vertices 4 and 5. Thus, the number of complete components in this graph is 1.

     */
public:
    vector<bool> visited;
    vector<vector<int>> adj;
    void dfs(const int node, vector<int> &nodeList)
    {
        visited.at(node) = true;
        nodeList.push_back(node);
        for (auto &neighbour : adj.at(node))
        {
            if (!visited.at(neighbour))
                dfs(neighbour, nodeList);
        }
    }
    int countCompleteComponents(int n, vector<vector<int>> &edges)
    {
        this->adj.resize(n);
        this->visited.resize(n);
        for (auto &edge : edges)
        {
            const int u = edge.front(), v = edge.back();
            adj.at(u).push_back(v);
            adj.at(v).push_back(u);
        }

        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                vector<int> nodeList;
                dfs(i, nodeList);
                // now we have got all the nodes in the nodeList array for this component.
                // for each node in nodeList the number of edges must be size - 1 where size:component size.
                const int size = nodeList.size();
                ans += all_of(nodeList.begin(), nodeList.end(), [&](const int node)
                              { return size - 1 == adj.at(node).size(); });
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