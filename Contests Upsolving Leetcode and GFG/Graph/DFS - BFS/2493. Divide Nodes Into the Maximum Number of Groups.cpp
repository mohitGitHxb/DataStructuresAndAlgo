#include <bits/stdc++.h>
using namespace std;
/*

You are given a positive integer n representing the number of nodes in an undirected graph. The nodes are labeled from 1 to n.

You are also given a 2D integer array edges, where edges[i] = [ai, bi] indicates that there is a bidirectional edge between nodes ai and bi. Notice that the given graph may be disconnected.

Divide the nodes of the graph into m groups (1-indexed) such that:

    Each node in the graph belongs to exactly one group.
    For every pair of nodes in the graph that are connected by an edge [ai, bi], if ai belongs to the group with index x, and bi belongs to the group with index y, then |y - x| = 1.

Return the maximum number of groups (i.e., maximum m) into which you can divide the nodes. Return -1 if it is impossible to group the nodes with the given conditions.



Example 1:

Input: n = 6, edges = [[1,2],[1,4],[1,5],[2,6],[2,3],[4,6]]
Output: 4
Explanation: As shown in the image we:
- Add node 5 to the first group.
- Add node 1 to the second group.
- Add nodes 2 and 4 to the third group.
- Add nodes 3 and 6 to the fourth group.
We can see that every edge is satisfied.
It can be shown that that if we create a fifth group and move any node from the third or fourth group to it, at least on of the edges will not be satisfied.

Example 2:

Input: n = 3, edges = [[1,2],[2,3],[3,1]]
Output: -1
Explanation: If we add node 1 to the first group, node 2 to the second group, and node 3 to the third group to satisfy the first two edges, we can see that the third edge will not be satisfied.
It can be shown that no grouping is possible.


 */
class Solution
{
public:
    // function for checking whether a graph component is bipartite or not (for disconnected graph)
    bool bipartite(int src, vector<int> adj[], int color[])
    {
        queue<int> q;
        q.push(src);
        color[src] = 1;
        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            for (auto it : adj[node])
            {
                if (color[it] == -1)
                {
                    color[it] = 1 - color[node];
                    q.push(it);
                }
                else if (color[it] == color[node])
                    return false;
            }
        }
        return true;
    }

    // function for checking whether a graph is bipartite or not
    bool checkBipartite(int &n, vector<int> adj[])
    {
        int color[n + 1];
        memset(color, -1, sizeof color);
        for (int i = 1; i <= n; i++)
        {
            if (color[i] == -1)
            {
                if (!bipartite(i, adj, color))
                    return false;
            }
        }
        return true;
    }

    // function for finding distance of farthest node from the current node
    // To get the maximum number of groups
    int findFarthestDistBFS(int src, int n, vector<int> adj[])
    {
        vector<int> vis(n + 1, 0);
        int cnt = 0;
        queue<int> q;
        q.push(src);
        vis[src] = 1;

        while (!q.empty())
        {
            int sz = q.size();
            cnt++;

            for (int i = 0; i < sz; i++)
            {
                int node = q.front();
                q.pop();

                for (auto it : adj[node])
                {
                    if (!vis[it])
                    {
                        q.push(it);
                        vis[it] = 1;
                    }
                }
            }
        }
        return cnt;
    }

    // For finding maximum groups of multiple components of a graph
    int dfsForComponents(int node, vector<int> adj[], vector<int> &vist, vector<int> &dist)
    {
        vist[node] = 1;
        int maxi = dist[node];
        for (auto it : adj[node])
        {
            if (!vist[it])
            {
                maxi = max(maxi, dfsForComponents(it, adj, vist, dist));
            }
        }
        return maxi;
    }

    // Given function
    int magnificentSets(int n, vector<vector<int>> &edges)
    {
        // creating adjacency list
        vector<int> adj[n + 1];
        for (int i = 0; i < edges.size(); i++)
        {
            adj[edges[i][0]].push_back(edges[i][1]);
            adj[edges[i][1]].push_back(edges[i][0]);
        }

        // check whether a graph is bipartite or not
        if (!checkBipartite(n, adj))
            return -1;

        // calcuate farthest node from each node and store in dist vector
        vector<int> dist(n + 1, 0);
        for (int i = 1; i <= n; i++)
        {
            dist[i] = findFarthestDistBFS(i, n, adj);
        }

        // for multiple components, count maximum number of groups
        vector<int> vist(n + 1, 0);
        int maxi = 0;
        for (int i = 1; i <= n; i++)
        {
            if (vist[i] == 0)
            {
                maxi += dfsForComponents(i, adj, vist, dist);
            }
        }
        return maxi;
    }
};
int main()
{
    return 0;
}